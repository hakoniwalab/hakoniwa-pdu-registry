#!/usr/bin/env python3
import argparse
import json
import os
import sys
import tempfile
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from generators.generate_hako_pdu_msgs.dependency_resolver import DependencyResolver
from generators.generate_hako_pdu_msgs.main import get_search_paths
from generators.generate_hako_pdu_msgs.ros_message_parser import find_ros_message_file


def read_required_ros_distro():
    version_file = REPO_ROOT / "ROS_VERSION.txt"
    try:
        return version_file.read_text(encoding="utf-8").strip()
    except FileNotFoundError as err:
        raise RuntimeError(f"Missing required ROS version file: {version_file}") from err


def guard_ros_distro():
    required = read_required_ros_distro()
    if required != "jazzy":
        raise RuntimeError(
            f"ROS_VERSION.txt must be 'jazzy' for type hash generation, got '{required}'."
        )

    actual = os.environ.get("ROS_DISTRO", "")
    if actual != required:
        actual_label = actual or "<unset>"
        raise RuntimeError(
            f"ROS_DISTRO must be '{required}' for type hash generation, got '{actual_label}'. "
            "Run this tool inside the Jazzy Docker image or source a ROS 2 Jazzy environment."
        )


def require_rosidl_type_description():
    try:
        import rosidl_generator_type_description as type_description
        from rosidl_generator_type_description import definition
    except ImportError as err:
        raise RuntimeError(
            "ROS 2 Jazzy rosidl_generator_type_description is required. "
            "Run this tool inside the ROS 2 Jazzy Docker image or source a Jazzy environment."
        ) from err

    try:
        from rosidl_adapter import convert_to_idl
    except ImportError as err:
        raise RuntimeError(
            "ROS 2 Jazzy rosidl_adapter is required. "
            "Run this tool inside the ROS 2 Jazzy Docker image or source a Jazzy environment."
        ) from err

    return type_description, definition, convert_to_idl


def ros_type_name(package_msg):
    package_name, message_name = package_msg.split("/", 1)
    return f"{package_name}/msg/{message_name}"


def package_message_from_type_name(type_name):
    parts = type_name.split("/")
    if len(parts) == 3 and parts[1] == "msg":
        return f"{parts[0]}/{parts[2]}"
    return type_name


def resolve_messages(ros_msgs_file, search_path_file, ros_root):
    project_root = Path.cwd()
    search_paths = get_search_paths(search_path_file, project_root, ros_root)

    with open(ros_msgs_file, "r", encoding="utf-8") as file:
        initial_messages = [line.strip() for line in file if line.strip()]

    resolver = DependencyResolver(search_paths)
    message_cache = resolver.get_all_dependencies(initial_messages)
    return search_paths, initial_messages, message_cache


def convert_messages_to_idl(message_cache, search_paths, tmp_dir, convert_to_idl, strict):
    converted = {}
    skipped = []
    for package_msg, msg_def in sorted(message_cache.items()):
        package_name = msg_def["package"]
        message_name = msg_def["message"]
        msg_file = find_ros_message_file(search_paths, package_name, message_name)
        if msg_file is None:
            raise RuntimeError(f"Could not find .msg file for {package_msg}")

        package_dir = msg_file.parent.parent
        interface_file = msg_file.relative_to(package_dir)
        package_output_dir = tmp_dir / "idl" / package_name
        try:
            idl_path = convert_to_idl(package_dir, package_name, interface_file, package_output_dir)
        except Exception as err:
            message = f"{package_msg}: {err}"
            if strict:
                raise RuntimeError(message) from err
            skipped.append(message)
            continue
        converted[package_msg] = {
            "msg_file": msg_file,
            "idl_root": package_output_dir,
            "idl_path": idl_path,
        }
    return converted, skipped


def build_type_description_map(converted, type_description, definition):
    individual_types = {}
    source_by_type_name = {}

    for package_msg, info in sorted(converted.items()):
        locator = definition.IdlLocator(
            str(info["idl_root"]),
            str(info["idl_path"].relative_to(info["idl_root"])),
        )
        idl_file = type_description.parse_idl_file(locator)
        for element in idl_file.content.elements:
            if isinstance(element, definition.Message):
                type_description.add_msg(element, individual_types)
                type_name = type_description.to_type_name(element.structure.namespaced_type)
                source_by_type_name[type_name] = str(info["msg_file"])

    serialized_type_lookup = {
        type_name: type_description.serialize_individual_type_description(
            individual_type.namespaced_type,
            individual_type.members,
        )
        for type_name, individual_type in individual_types.items()
    }
    return serialized_type_lookup, source_by_type_name


def calculate_hash_records(type_names, serialized_type_lookup, source_by_type_name, type_description):
    records = {}
    hash_lookup = {}

    for type_name in sorted(serialized_type_lookup):
        full_description = type_description.extract_full_type_description(
            type_name,
            serialized_type_lookup,
        )
        hash_lookup[type_name] = type_description.calculate_type_hash(full_description)

    for type_name in sorted(type_names):
        full_description = type_description.extract_full_type_description(
            type_name,
            serialized_type_lookup,
        )
        dependency_hashes = []
        for referenced_type in full_description["referenced_type_descriptions"]:
            referenced_type_name = referenced_type["type_name"]
            dependency_hashes.append({
                "type_name": referenced_type_name,
                "package_message": package_message_from_type_name(referenced_type_name),
                "hash_string": hash_lookup[referenced_type_name],
            })

        hash_string = hash_lookup[type_name]
        records[type_name] = {
            "schema_version": 1,
            "ros_distro": os.environ.get("ROS_DISTRO", ""),
            "hash_algorithm": "RIHS01",
            "type_name": type_name,
            "package_message": package_message_from_type_name(type_name),
            "source_msg": source_by_type_name.get(type_name, ""),
            "hash_string": hash_string,
            "hash_value": hash_string.split("_", 1)[1] if "_" in hash_string else hash_string,
            "dependencies": dependency_hashes,
        }

    return records


def write_records(records, output_dir):
    written = []
    for type_name, record in sorted(records.items()):
        package_name, _, message_name = type_name.split("/")
        output_path = output_dir / package_name / f"{message_name}.json"
        output_path.parent.mkdir(parents=True, exist_ok=True)
        output_path.write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
        written.append(output_path)
    return written


def main():
    parser = argparse.ArgumentParser(
        description="Generate ROS 2 RIHS01 type hash metadata from .msg files."
    )
    parser.add_argument(
        "ros_msgs_file",
        nargs="?",
        default="config/ros_msgs.txt",
        help="Path to the file listing ROS messages to process.",
    )
    parser.add_argument(
        "--search-path-file",
        default="config/search_path.txt",
        help="Path to the search path file.",
    )
    parser.add_argument(
        "--output-dir",
        default="pdu/type_hash",
        help="Directory for generated type hash JSON files.",
    )
    parser.add_argument(
        "--ros-root",
        help="Optional root path of a ROS 2 installation for local testing.",
    )
    parser.add_argument(
        "--all-resolved",
        action="store_true",
        help="Write hashes for all resolved dependency messages, not only ros_msgs_file entries.",
    )
    parser.add_argument(
        "--strict",
        action="store_true",
        help="Fail when a message cannot be converted by ROS 2 rosidl_adapter.",
    )
    args = parser.parse_args()

    try:
        guard_ros_distro()
        type_description, definition, convert_to_idl = require_rosidl_type_description()
        search_paths, initial_messages, message_cache = resolve_messages(
            args.ros_msgs_file,
            args.search_path_file,
            args.ros_root,
        )

        with tempfile.TemporaryDirectory() as tmp:
            converted, skipped = convert_messages_to_idl(
                message_cache,
                search_paths,
                Path(tmp),
                convert_to_idl,
                args.strict,
            )
            serialized_type_lookup, source_by_type_name = build_type_description_map(
                converted,
                type_description,
                definition,
            )

            if args.all_resolved:
                target_type_names = set(serialized_type_lookup.keys())
            else:
                target_type_names = {
                    ros_type_name(msg.split("[", 1)[0])
                    for msg in initial_messages
                    if ros_type_name(msg.split("[", 1)[0]) in serialized_type_lookup
                }

            records = calculate_hash_records(
                target_type_names,
                serialized_type_lookup,
                source_by_type_name,
                type_description,
            )
            written = write_records(records, Path(args.output_dir))

        print(f"Generated {len(written)} ROS 2 type hash files under {args.output_dir}")
        if skipped:
            print(f"Skipped {len(skipped)} messages that ROS 2 rosidl_adapter could not convert:")
            for item in skipped:
                print(f"  - {item}")
    except Exception as err:
        print(f"Error: {err}", file=sys.stderr)
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
