#!/usr/bin/env python3
"""Generate a self-contained MCAP/Foxglove ros2msg schema bundle from ROS 2 .msg files.

This tool intentionally operates on source .msg files only. It does not import ROS 2
Python bindings and does not compile interface packages.
"""

from __future__ import annotations

import argparse
import os
import re
import sys
from pathlib import Path
from typing import Iterable

SEPARATOR = "=" * 80

PRIMITIVE_TYPES = {
    "bool",
    "byte",
    "char",
    "float32",
    "float64",
    "int8",
    "uint8",
    "int16",
    "uint16",
    "int32",
    "uint32",
    "int64",
    "uint64",
    "string",
    "wstring",
}

ARRAY_SUFFIX_RE = re.compile(r"\[[^\]]*\]$")
BOUNDED_STRING_RE = re.compile(r"^(?:w?string)(?:<=\d+)?$")


class BundleError(RuntimeError):
    """Raised when a message bundle cannot be resolved completely."""


def normalize_message_type(type_name: str, default_package: str | None = None) -> str | None:
    """Return canonical ``package/msg/Type`` or ``None`` for primitive types."""
    base = type_name.strip()
    while ARRAY_SUFFIX_RE.search(base):
        base = ARRAY_SUFFIX_RE.sub("", base)

    if base in PRIMITIVE_TYPES or BOUNDED_STRING_RE.fullmatch(base):
        return None

    parts = base.split("/")
    if len(parts) == 3 and parts[1] == "msg":
        package, _, message = parts
        if package and message:
            return f"{package}/msg/{message}"
    elif len(parts) == 2:
        package, message = parts
        if package and message:
            return f"{package}/msg/{message}"
    elif len(parts) == 1 and default_package:
        return f"{default_package}/msg/{base}"

    raise BundleError(f"Unsupported ROS 2 message type syntax: {type_name!r}")


def split_canonical_type(canonical_type: str) -> tuple[str, str]:
    parts = canonical_type.split("/")
    if len(parts) != 3 or parts[1] != "msg" or not parts[0] or not parts[2]:
        raise BundleError(f"Expected package/msg/Type, got: {canonical_type!r}")
    return parts[0], parts[2]


def bundle_resource_name(canonical_type: str) -> str:
    """Return the dependency name used by concatenated ros2msg schema text.

    ROS 2 field definitions refer to nested messages as ``package/Type``. Foxglove
    resolves dependency sections against those names, so dependency delimiters must
    use the same two-part form even though the top-level schema name may use
    ``package/msg/Type`` elsewhere in the transport metadata.
    """
    package, message = split_canonical_type(canonical_type)
    return f"{package}/{message}"


def find_message_file(search_paths: Iterable[Path], canonical_type: str) -> Path:
    package, message = split_canonical_type(canonical_type)
    checked: list[Path] = []

    for root in search_paths:
        candidate = root / package / "msg" / f"{message}.msg"
        checked.append(candidate)
        if candidate.is_file():
            return candidate

        # Also accept a package-share directory itself as a search path.
        if root.name == package:
            candidate = root / "msg" / f"{message}.msg"
            checked.append(candidate)
            if candidate.is_file():
                return candidate

    checked_text = "\n".join(f"  - {path}" for path in checked)
    raise BundleError(f"Could not resolve {canonical_type}. Checked:\n{checked_text}")


def iter_field_types(message_text: str) -> Iterable[str]:
    """Yield field type tokens from a ROS 2 .msg source definition."""
    for raw_line in message_text.splitlines():
        line = raw_line.split("#", 1)[0].strip()
        if not line or "=" in line:
            continue
        parts = line.split()
        if len(parts) >= 2:
            yield parts[0]


def resolve_bundle(
    top_level_type: str,
    search_paths: Iterable[Path],
) -> tuple[str, list[tuple[str, str]]]:
    """Resolve the top-level source plus all transitive .msg dependencies."""
    canonical_top = normalize_message_type(top_level_type)
    if canonical_top is None:
        raise BundleError("Top-level type must be a ROS 2 message type, not a primitive")

    resolved: dict[str, str] = {}
    visiting: set[str] = set()
    dependency_order: list[str] = []

    def visit(canonical_type: str, *, is_top_level: bool = False) -> None:
        if canonical_type in resolved:
            return
        if canonical_type in visiting:
            raise BundleError(f"Cyclic message dependency detected at {canonical_type}")

        visiting.add(canonical_type)
        package, _ = split_canonical_type(canonical_type)
        source_path = find_message_file(search_paths, canonical_type)
        try:
            source_text = source_path.read_text(encoding="utf-8")
        except UnicodeDecodeError as exc:
            raise BundleError(f"Message file is not UTF-8: {source_path}") from exc

        resolved[canonical_type] = source_text
        if not is_top_level:
            dependency_order.append(canonical_type)

        for field_type in iter_field_types(source_text):
            dependency = normalize_message_type(field_type, default_package=package)
            if dependency is not None:
                visit(dependency)

        visiting.remove(canonical_type)

    visit(canonical_top, is_top_level=True)
    return resolved[canonical_top], [
        (canonical_type, resolved[canonical_type]) for canonical_type in dependency_order
    ]


def render_bundle(top_level_text: str, dependencies: Iterable[tuple[str, str]]) -> str:
    chunks = [top_level_text.rstrip("\n")]
    for canonical_type, source_text in dependencies:
        chunks.extend(
            [
                SEPARATOR,
                f"MSG: {bundle_resource_name(canonical_type)}",
                source_text.rstrip("\n"),
            ]
        )
    return "\n".join(chunks) + "\n"


def read_search_path_file(path: Path) -> list[Path]:
    paths: list[Path] = []
    for raw_line in path.read_text(encoding="utf-8").splitlines():
        line = raw_line.strip()
        if not line or line.startswith("#"):
            continue
        paths.append(Path(os.path.expandvars(os.path.expanduser(line))))
    return paths


def default_search_paths() -> list[Path]:
    repo_root = Path(__file__).resolve().parents[1]
    paths = [repo_root / "idl"]
    ros_distro = os.environ.get("ROS_DISTRO")
    if ros_distro:
        paths.insert(0, Path(f"/opt/ros/{ros_distro}/share"))
    return paths


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Generate a self-contained MCAP/Foxglove ros2msg schema bundle "
            "directly from ROS 2 .msg source files."
        )
    )
    parser.add_argument(
        "message_type",
        help="Top-level message type, e.g. sensor_msgs/JointState or sensor_msgs/msg/JointState",
    )
    parser.add_argument("-o", "--output", required=True, help="Output bundle file")
    parser.add_argument(
        "--search-path",
        action="append",
        default=[],
        help="Message search root containing <package>/msg/<Type>.msg; repeatable",
    )
    parser.add_argument(
        "--search-path-file",
        help="Optional newline-separated message search roots",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()

    search_paths: list[Path] = []
    if args.search_path_file:
        search_paths.extend(read_search_path_file(Path(args.search_path_file)))
    search_paths.extend(Path(path) for path in args.search_path)
    if not search_paths:
        search_paths = default_search_paths()

    search_paths = [path.resolve() for path in search_paths]

    try:
        top_level_text, dependencies = resolve_bundle(args.message_type, search_paths)
        bundle = render_bundle(top_level_text, dependencies)
        output_path = Path(args.output)
        output_path.parent.mkdir(parents=True, exist_ok=True)
        output_path.write_text(bundle, encoding="utf-8")
    except (BundleError, OSError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 2

    print(
        f"generated {output_path} "
        f"(message={args.message_type}, dependencies={len(dependencies)})"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
