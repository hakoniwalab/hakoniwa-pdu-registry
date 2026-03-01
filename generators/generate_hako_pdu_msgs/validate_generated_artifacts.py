import importlib.util
import json
import re
import struct
import subprocess
import sys
from pathlib import Path


def parse_offset_entry_size(parts):
    entry_kind = parts[0]
    if entry_kind == "single":
        return int(parts[-2]), int(parts[-1])
    if entry_kind == "array":
        return int(parts[-3]), int(parts[-2])
    if entry_kind == "varray":
        return int(parts[-3]), 8
    raise ValueError(f"Unsupported offset entry kind: {entry_kind}")


def collect_expected_sizes(repo_root: Path):
    expected = {}
    offset_root = repo_root / "pdu" / "offset"
    for offset_file in sorted(offset_root.rglob("*.offset")):
        rel = offset_file.relative_to(offset_root)
        type_name = f"{rel.parent.name}/{offset_file.stem}"
        lines = [line.strip() for line in offset_file.read_text().splitlines() if line.strip()]
        if not lines:
            continue
        offset, size = parse_offset_entry_size(lines[-1].split(":"))
        expected[type_name] = (offset + size + 7) & ~7
    return expected


def collect_size_files(repo_root: Path):
    actual = {}
    size_root = repo_root / "pdu" / "pdu_size"
    for size_file in sorted(size_root.rglob("*.txt")):
        rel = size_file.relative_to(size_root)
        actual[f"{rel.parent.name}/{size_file.stem}"] = int(size_file.read_text().strip())
    return actual


def collect_python_registry(repo_root: Path):
    module_path = repo_root / "pdu" / "python" / "pdu_size.py"
    spec = importlib.util.spec_from_file_location("pdu_size_registry", module_path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return dict(module.PDU_SIZE)


def collect_javascript_registry(repo_root: Path):
    js_path = repo_root / "pdu" / "javascript" / "pdu_size.js"
    entries = {}
    pattern = re.compile(r'"([^"]+)":\s+(\d+),')
    for line in js_path.read_text().splitlines():
        match = pattern.search(line)
        if match:
            entries[match.group(1)] = int(match.group(2))
    return entries


def collect_c_registry(repo_root: Path):
    c_path = repo_root / "pdu" / "types" / "pdu_size_registry.c"
    entries = {}
    pattern = re.compile(r'\{\s+"([^"]+)",\s+(\d+)\s+\},')
    for line in c_path.read_text().splitlines():
        match = pattern.search(line)
        if match:
            entries[match.group(1)] = int(match.group(2))
    return entries


def validate_size_registries(repo_root: Path):
    expected = collect_expected_sizes(repo_root)
    size_files = collect_size_files(repo_root)
    python_registry = collect_python_registry(repo_root)
    javascript_registry = collect_javascript_registry(repo_root)
    c_registry = collect_c_registry(repo_root)

    mismatches = []
    for type_name, expected_size in sorted(expected.items()):
        actuals = {
            "size_file": size_files.get(type_name),
            "python": python_registry.get(type_name),
            "javascript": javascript_registry.get(type_name),
            "c": c_registry.get(type_name),
        }
        for source, actual_size in actuals.items():
            if actual_size != expected_size:
                mismatches.append((type_name, source, actual_size, expected_size))
    return mismatches


def validate_python_bool_array_roundtrip(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_GameControllerOperation import (
        pdu_to_py_GameControllerOperation,
        py_to_pdu_GameControllerOperation,
    )
    from pdu.python.hako_msgs.pdu_pytype_GameControllerOperation import (
        GameControllerOperation,
    )

    original_buttons = [True, False, True, True, False] * 3
    obj = GameControllerOperation()
    obj.axis = [0.5, -1.0, 2.0, -3.0, 4.0, -5.0]
    obj.button = original_buttons

    binary = py_to_pdu_GameControllerOperation(obj)
    expected_bytes = struct.pack("<15i", *[1 if value else 0 for value in original_buttons])
    button_bytes = bytes(binary[24 + 48:24 + 48 + 60])
    restored = pdu_to_py_GameControllerOperation(binary)
    restored_buttons = [bool(value) for value in restored.button]

    return {
        "total_size": len(binary),
        "button_bytes": button_bytes,
        "expected_bytes": expected_bytes,
        "restored_buttons": restored_buttons,
        "expected_buttons": original_buttons,
    }


def validate_javascript_bool_array_roundtrip(repo_root: Path):
    script = """
import { GameControllerOperation } from './pdu/javascript/hako_msgs/pdu_jstype_GameControllerOperation.js';
import { jsToPdu_GameControllerOperation, pduToJs_GameControllerOperation } from './pdu/javascript/hako_msgs/pdu_conv_GameControllerOperation.js';

const obj = new GameControllerOperation();
obj.axis = [0.5, -1.0, 2.0, -3.0, 4.0, -5.0];
obj.button = [true, false, true, true, false, true, false, true, true, false, true, false, true, true, false];

const buffer = jsToPdu_GameControllerOperation(obj);
const bytes = Array.from(new Uint8Array(buffer).slice(24 + 48, 24 + 48 + 60));
const restored = pduToJs_GameControllerOperation(buffer);

console.log(JSON.stringify({
  totalSize: buffer.byteLength,
  buttonBytes: bytes,
  restoredButtons: restored.button
}));
"""
    result = subprocess.run(
        ["node", "--input-type=module", "-e", script],
        cwd=repo_root,
        check=True,
        capture_output=True,
        text=True,
    )
    data = json.loads(result.stdout)
    expected_buttons = [True, False, True, True, False] * 3
    expected_bytes = list(struct.pack("<15i", *[1 if value else 0 for value in expected_buttons]))
    return {
        "total_size": data["totalSize"],
        "button_bytes": data["buttonBytes"],
        "expected_bytes": expected_bytes,
        "restored_buttons": data["restoredButtons"],
        "expected_buttons": expected_buttons,
    }


def main():
    repo_root = Path(__file__).resolve().parents[2]
    failures = []

    size_mismatches = validate_size_registries(repo_root)
    if size_mismatches:
        failures.append(f"size registry mismatches: {size_mismatches[:10]}")

    py_result = validate_python_bool_array_roundtrip(repo_root)
    if py_result["button_bytes"] != py_result["expected_bytes"]:
        failures.append("python bool[] serialization bytes do not match 4-byte bool layout")
    if py_result["restored_buttons"] != py_result["expected_buttons"]:
        failures.append("python bool[] roundtrip does not preserve values")

    js_result = validate_javascript_bool_array_roundtrip(repo_root)
    if js_result["button_bytes"] != js_result["expected_bytes"]:
        failures.append("javascript bool[] serialization bytes do not match 4-byte bool layout")
    if js_result["restored_buttons"] != js_result["expected_buttons"]:
        failures.append("javascript bool[] roundtrip does not preserve values")

    if failures:
        for failure in failures:
            print(f"FAIL: {failure}", file=sys.stderr)
        return 1

    print("OK: generated artifact validation passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
