#!/usr/bin/env python3
"""Fetch selected ROS message packages from an external Git source.

External repositories are temporary build inputs. Only selected ``msg/*.msg``
files and deterministic provenance metadata are written to the output tree.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import shutil
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Sequence

try:
    import yaml
except ModuleNotFoundError as exc:  # pragma: no cover - environment dependent
    raise SystemExit(
        "PyYAML is required by tools/fetch.py. Install tools/requirements-fetch.txt."
    ) from exc


PACKAGE_NAME_RE = re.compile(r"[A-Za-z][A-Za-z0-9_]*\Z")


class FetchError(RuntimeError):
    """A source manifest cannot be fetched safely or completely."""


@dataclass(frozen=True)
class GitSource:
    repository: str
    ref: str


@dataclass(frozen=True)
class SourceManifest:
    source: GitSource
    packages: tuple[str, ...]


@dataclass(frozen=True)
class PackageMetadata:
    name: str
    version: str | None
    licenses: tuple[str, ...]
    root: Path


def _require_mapping(value: Any, field: str) -> dict[str, Any]:
    if not isinstance(value, dict):
        raise FetchError(f"{field} must be a mapping")
    return value


def _require_string(value: Any, field: str) -> str:
    if not isinstance(value, str) or not value.strip():
        raise FetchError(f"{field} must be a non-empty string")
    return value.strip()


def load_source_manifest(path: Path) -> SourceManifest:
    try:
        raw = yaml.safe_load(path.read_text(encoding="utf-8"))
    except OSError as exc:
        raise FetchError(f"cannot read source manifest {path}: {exc}") from exc
    except yaml.YAMLError as exc:
        raise FetchError(f"invalid YAML in source manifest {path}: {exc}") from exc

    root = _require_mapping(raw, "manifest")
    unknown = set(root) - {"schema_version", "source", "packages"}
    if unknown:
        raise FetchError(f"unknown manifest fields: {', '.join(sorted(unknown))}")
    if root.get("schema_version") != 1:
        raise FetchError("schema_version must be 1")

    source_raw = _require_mapping(root.get("source"), "source")
    source_unknown = set(source_raw) - {"type", "repository", "ref"}
    if source_unknown:
        raise FetchError(f"unknown source fields: {', '.join(sorted(source_unknown))}")
    if source_raw.get("type") != "git":
        raise FetchError("source.type must be 'git'")
    source = GitSource(
        repository=_require_string(source_raw.get("repository"), "source.repository"),
        ref=_require_string(source_raw.get("ref"), "source.ref"),
    )

    packages_raw = root.get("packages")
    if not isinstance(packages_raw, list) or not packages_raw:
        raise FetchError("packages must be a non-empty list")
    packages: list[str] = []
    for index, value in enumerate(packages_raw):
        name = _require_string(value, f"packages[{index}]")
        if not PACKAGE_NAME_RE.fullmatch(name):
            raise FetchError(f"invalid ROS package name: {name!r}")
        if name in packages:
            raise FetchError(f"duplicate ROS package name: {name}")
        packages.append(name)
    return SourceManifest(source=source, packages=tuple(packages))


def _run_git(args: Sequence[str], *, cwd: Path | None = None) -> str:
    command = ["git", *args]
    try:
        result = subprocess.run(
            command,
            cwd=cwd,
            check=False,
            capture_output=True,
            text=True,
        )
    except OSError as exc:
        raise FetchError(f"cannot execute git: {exc}") from exc
    if result.returncode != 0:
        detail = result.stderr.strip() or result.stdout.strip() or "unknown git error"
        raise FetchError(f"{' '.join(command)} failed: {detail}")
    return result.stdout.strip()


def checkout_source(source: GitSource, checkout_dir: Path) -> str:
    _run_git(["init", "--quiet", str(checkout_dir)])
    _run_git(["remote", "add", "origin", source.repository], cwd=checkout_dir)
    _run_git(["fetch", "--quiet", "--depth", "1", "origin", source.ref], cwd=checkout_dir)
    _run_git(["checkout", "--quiet", "--detach", "FETCH_HEAD"], cwd=checkout_dir)
    commit = _run_git(["rev-parse", "HEAD"], cwd=checkout_dir)
    if not re.fullmatch(r"[0-9a-f]{40}", commit):
        raise FetchError(f"git returned an invalid commit SHA: {commit!r}")
    return commit


def _package_metadata(package_xml: Path) -> PackageMetadata:
    try:
        root = ET.parse(package_xml).getroot()
    except (OSError, ET.ParseError) as exc:
        raise FetchError(f"cannot parse ROS package metadata {package_xml}: {exc}") from exc

    name_node = root.find("name")
    if name_node is None or not (name_node.text or "").strip():
        raise FetchError(f"ROS package metadata has no name: {package_xml}")
    version_node = root.find("version")
    licenses = tuple(
        text
        for node in root.findall("license")
        if (text := (node.text or "").strip())
    )
    return PackageMetadata(
        name=(name_node.text or "").strip(),
        version=((version_node.text or "").strip() if version_node is not None else None),
        licenses=licenses,
        root=package_xml.parent,
    )


def discover_packages(checkout_dir: Path) -> dict[str, PackageMetadata]:
    discovered: dict[str, PackageMetadata] = {}
    for package_xml in sorted(checkout_dir.rglob("package.xml")):
        if ".git" in package_xml.parts:
            continue
        metadata = _package_metadata(package_xml)
        if metadata.name in discovered:
            raise FetchError(f"duplicate package {metadata.name!r} in source repository")
        discovered[metadata.name] = metadata
    return discovered


def _message_files(package: PackageMetadata) -> list[Path]:
    msg_dir = package.root / "msg"
    if not msg_dir.is_dir():
        raise FetchError(f"package {package.name!r} has no msg directory")
    files = sorted(msg_dir.glob("*.msg"), key=lambda path: path.name)
    if not files:
        raise FetchError(f"package {package.name!r} contains no .msg files")
    for path in files:
        if path.is_symlink() or not path.is_file():
            raise FetchError(f"refusing non-regular message source: {path}")
    return files


def _sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(65536), b""):
            digest.update(chunk)
    return digest.hexdigest()


def _remove_existing_package(target: Path) -> None:
    if not target.exists() and not target.is_symlink():
        return
    if target.is_symlink() or not target.is_dir():
        raise FetchError(f"refusing to clean non-directory package output: {target}")
    shutil.rmtree(target)


def write_package(
    *,
    package: PackageMetadata,
    checkout_dir: Path,
    output_dir: Path,
    source: GitSource,
    resolved_commit: str,
    replace: bool = False,
) -> Path:
    target = output_dir / package.name
    target_exists = target.exists() or target.is_symlink()
    if target_exists and not replace:
        raise FetchError(f"output already exists: {target}; use --clean to replace it")

    stage = Path(tempfile.mkdtemp(prefix=f".{package.name}.fetch-", dir=output_dir))
    try:
        output_msg_dir = stage / "msg"
        output_msg_dir.mkdir()
        file_records: list[dict[str, str]] = []
        for source_file in _message_files(package):
            destination = output_msg_dir / source_file.name
            shutil.copyfile(source_file, destination)
            file_records.append(
                {
                    "path": f"msg/{source_file.name}",
                    "sha256": _sha256(destination),
                }
            )

        source_path = package.root.relative_to(checkout_dir).as_posix() or "."
        provenance = {
            "schema_version": 1,
            "source": {
                "type": "git",
                "repository": source.repository,
                "requested_ref": source.ref,
                "resolved_commit": resolved_commit,
            },
            "package": {
                "name": package.name,
                "version": package.version,
                "source_path": source_path,
                "declared_licenses": list(package.licenses),
                "license_metadata_source": f"{source_path}/package.xml"
                if source_path != "."
                else "package.xml",
            },
            "files": file_records,
        }
        (stage / "source-manifest.json").write_text(
            json.dumps(provenance, indent=2, sort_keys=True) + "\n",
            encoding="utf-8",
        )
        if target_exists:
            _remove_existing_package(target)
        stage.replace(target)
    except Exception:
        if stage.exists():
            shutil.rmtree(stage)
        raise
    return target


def fetch_sources(*, sources: Path, output: Path, clean: bool = False) -> list[Path]:
    manifest = load_source_manifest(sources)
    output = output.expanduser().resolve()
    output.mkdir(parents=True, exist_ok=True)

    with tempfile.TemporaryDirectory(prefix="hakoniwa-pdu-fetch-") as temporary:
        checkout_dir = Path(temporary) / "source"
        resolved_commit = checkout_source(manifest.source, checkout_dir)
        available = discover_packages(checkout_dir)
        missing = [name for name in manifest.packages if name not in available]
        if missing:
            raise FetchError(
                "requested ROS package(s) not found: " + ", ".join(missing)
            )

        outputs = [
            write_package(
                package=available[name],
                checkout_dir=checkout_dir,
                output_dir=output,
                source=manifest.source,
                resolved_commit=resolved_commit,
                replace=clean,
            )
            for name in manifest.packages
        ]
    return outputs


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Fetch selected ROS msg packages into a generator input tree."
    )
    parser.add_argument("--sources", type=Path, required=True, help="Source YAML")
    parser.add_argument(
        "--output",
        type=Path,
        default=Path("output_msgs"),
        help="Output root (default: output_msgs)",
    )
    parser.add_argument(
        "--clean",
        action="store_true",
        help="Replace only package directories selected by the source YAML",
    )
    return parser


def main(argv: Sequence[str] | None = None) -> int:
    args = build_parser().parse_args(argv)
    try:
        outputs = fetch_sources(
            sources=args.sources.expanduser().resolve(),
            output=args.output,
            clean=args.clean,
        )
    except FetchError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    for output in outputs:
        print(f"fetched: {output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
