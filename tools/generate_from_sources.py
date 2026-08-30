#!/usr/bin/env python3
"""Fetch external ROS messages and generate only a selected PDU subset."""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Sequence

from fetch import FetchError, fetch_sources, load_source_manifest


CONTAINER_ROOT = Path("/root/workspace/hakoniwa-pdu-registry")
MESSAGE_NAME_RE = re.compile(
    r"(?P<package>[A-Za-z][A-Za-z0-9_]*)/(?P<message>[A-Za-z][A-Za-z0-9_]*)\Z"
)


class GenerateError(RuntimeError):
    """Selected-message generation cannot be performed safely."""


def validate_messages(messages: Sequence[str]) -> tuple[str, ...]:
    selected: list[str] = []
    for value in messages:
        if not MESSAGE_NAME_RE.fullmatch(value):
            raise GenerateError(
                f"invalid message {value!r}; expected package/Message"
            )
        if value not in selected:
            selected.append(value)
    if not selected:
        raise GenerateError("at least one package/Message must be selected")
    return tuple(selected)


def validate_output_dir(repo_root: Path, value: Path) -> Path:
    if value.is_absolute():
        raise GenerateError("--output-dir must be relative to the repository root")
    resolved = (repo_root / value).resolve()
    try:
        resolved.relative_to(repo_root)
    except ValueError as exc:
        raise GenerateError("--output-dir must stay inside the repository") from exc
    return resolved


def container_path(repo_root: Path, host_path: Path) -> str:
    try:
        relative = host_path.resolve().relative_to(repo_root)
    except ValueError as exc:
        raise GenerateError(f"path is outside the repository: {host_path}") from exc
    return str(CONTAINER_ROOT / relative)


def write_generation_inputs(
    *,
    repo_root: Path,
    work_dir: Path,
    selected_messages: Sequence[str],
    fetched_root: Path,
) -> tuple[Path, Path]:
    message_list = work_dir / "selected-ros-msgs.txt"
    message_list.write_text("\n".join(selected_messages) + "\n", encoding="utf-8")

    base_search_path = repo_root / "config" / "search_path.txt"
    lines = [
        line.strip()
        for line in base_search_path.read_text(encoding="utf-8").splitlines()
        if line.strip()
    ]
    fetched_container_path = container_path(repo_root, fetched_root)
    if fetched_container_path not in lines:
        lines.append(fetched_container_path)
    search_path = work_dir / "search-path.txt"
    search_path.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return message_list, search_path


def run_generation(
    *,
    repo_root: Path,
    source_files: Sequence[Path],
    messages: Sequence[str],
    output_dir: Path,
    cdr_only: bool = False,
) -> None:
    selected = validate_messages(messages)
    generated_output = validate_output_dir(repo_root, output_dir)
    fetched_root = repo_root / "output_msgs"

    declared_packages: set[str] = set()
    for source_file in source_files:
        source_file = source_file.expanduser().resolve()
        manifest = load_source_manifest(source_file)
        declared_packages.update(manifest.packages)
        fetch_sources(sources=source_file, output=fetched_root, clean=True)

    requested_packages = {
        MESSAGE_NAME_RE.fullmatch(message).group("package")  # type: ignore[union-attr]
        for message in selected
    }
    missing_sources = sorted(requested_packages - declared_packages)
    if missing_sources:
        raise GenerateError(
            "selected external package(s) are not declared by --sources: "
            + ", ".join(missing_sources)
        )

    cache_root = repo_root / ".cache"
    cache_root.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(
        prefix="selected-pdu-generation-", dir=cache_root
    ) as temporary:
        work_dir = Path(temporary)
        message_list, search_path = write_generation_inputs(
            repo_root=repo_root,
            work_dir=work_dir,
            selected_messages=selected,
            fetched_root=fetched_root,
        )
        command = [
            "bash",
            str(repo_root / "docker" / "run.bash"),
            "python3",
            "-m",
            "generators.generate_hako_pdu_msgs.main",
            container_path(repo_root, message_list),
            "--search-path-file",
            container_path(repo_root, search_path),
            "--output-dir",
            container_path(repo_root, generated_output),
            "--template-dir",
            str(CONTAINER_ROOT / "template"),
            "--incremental",
        ]
        if cdr_only:
            command.append("--cdr")
        subprocess.run(command, cwd=repo_root, check=True)


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description=(
            "Fetch declared ROS packages and generate only explicitly selected "
            "package/Message PDUs plus their required dependencies."
        )
    )
    parser.add_argument(
        "--sources",
        type=Path,
        action="append",
        required=True,
        help="Source YAML (repeatable)",
    )
    parser.add_argument(
        "--output-dir",
        type=Path,
        default=Path("pdu"),
        help="Repository-relative generated output directory (default: pdu)",
    )
    parser.add_argument(
        "--cdr", action="store_true", help="Generate only CDR-related artifacts"
    )
    parser.add_argument("messages", nargs="+", help="Selected package/Message names")
    return parser


def main(argv: Sequence[str] | None = None) -> int:
    args = build_parser().parse_args(argv)
    repo_root = Path(__file__).resolve().parents[1]
    try:
        run_generation(
            repo_root=repo_root,
            source_files=args.sources,
            messages=args.messages,
            output_dir=args.output_dir,
            cdr_only=args.cdr,
        )
    except (FetchError, GenerateError, subprocess.CalledProcessError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    print("Generated selected PDU messages: " + ", ".join(validate_messages(args.messages)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
