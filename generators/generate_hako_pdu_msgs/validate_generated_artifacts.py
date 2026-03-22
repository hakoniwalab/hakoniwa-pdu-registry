import importlib.util
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import tempfile
import textwrap
from pathlib import Path

from .code_generator import CodeGenerator

CPP_ORACLE_BUILD_DIR = Path(tempfile.gettempdir()) / "hako-pdu-cpp-tests"


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


def validate_javascript_from_dict_roundtrip(repo_root: Path):
    script = """
import { GameControllerOperation } from './pdu/javascript/hako_msgs/pdu_jstype_GameControllerOperation.js';
import { SimpleStructVarray } from './pdu/javascript/hako_msgs/pdu_jstype_SimpleStructVarray.js';

const gameInput = {
  axis: [1.5, -2.25, 3.0],
  button: [true, false, true]
};
const gameObj = GameControllerOperation.fromDict(gameInput);
const gameJsonObj = GameControllerOperation.fromJSON(JSON.stringify(gameInput));

const structInput = {
  aaa: 7,
  fixed_str: ['alpha', 'beta'],
  varray_str: ['gamma', 'delta'],
  fixed_array: [
    { data: [1, 2], fixed_array: [3, 4], p_mem1: 5 },
    { data: [6], fixed_array: [7], p_mem1: 8 }
  ],
  data: [
    { data: [9], fixed_array: [10, 11], p_mem1: 12 }
  ]
};
const structObj = SimpleStructVarray.fromDict(structInput);
const structJsonObj = SimpleStructVarray.fromJSON(JSON.stringify(structInput));

console.log(JSON.stringify({
  gameAxis: gameObj.axis,
  gameButtons: gameObj.button,
  gameJsonAxis: gameJsonObj.axis,
  gameJsonButtons: gameJsonObj.button,
  fixedStr: structObj.fixed_str,
  varrayStr: structObj.varray_str,
  fixedArrayData0: structObj.fixed_array[0]?.data,
  dataArray0: structObj.data[0]?.fixed_array,
  fixedStrJson: structJsonObj.fixed_str,
  varrayStrJson: structJsonObj.varray_str,
  fixedArrayData0Json: structJsonObj.fixed_array[0]?.data,
  dataArray0Json: structJsonObj.data[0]?.fixed_array
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
    return {
        "game_axis": data["gameAxis"],
        "expected_game_axis": [1.5, -2.25, 3.0],
        "game_buttons": data["gameButtons"],
        "expected_game_buttons": [True, False, True],
        "game_json_axis": data["gameJsonAxis"],
        "game_json_buttons": data["gameJsonButtons"],
        "fixed_str": data["fixedStr"],
        "expected_fixed_str": ["alpha", "beta"],
        "varray_str": data["varrayStr"],
        "expected_varray_str": ["gamma", "delta"],
        "fixed_array_data0": data["fixedArrayData0"],
        "expected_fixed_array_data0": [1, 2],
        "data_array0": data["dataArray0"],
        "expected_data_array0": [10, 11],
        "fixed_str_json": data["fixedStrJson"],
        "varray_str_json": data["varrayStrJson"],
        "fixed_array_data0_json": data["fixedArrayData0Json"],
        "data_array0_json": data["dataArray0Json"],
    }


def ensure_godot_cpp_bridge(repo_root: Path):
    godot_cpp_root = Path(
        os.environ.get(
            "HAKO_GODOT_CPP_ROOT",
            "/Users/tmori/project/oss/godot-cpp",
        )
    )
    if not godot_cpp_root.exists():
        raise FileNotFoundError(f"godot-cpp root not found: {godot_cpp_root}")

    bridge_dir = repo_root / "tests" / "godot_cpp_smoke"
    subprocess.run(
        [
            "cmake",
            "-S",
            str(bridge_dir),
            "-B",
            str(bridge_dir / "build"),
        ],
        cwd=repo_root,
        env={**os.environ, "HAKO_GODOT_CPP_ROOT": str(godot_cpp_root)},
        check=True,
        capture_output=True,
        text=True,
    )
    subprocess.run(
        [
            "cmake",
            "--build",
            str(bridge_dir / "build"),
            "-j4",
        ],
        cwd=repo_root,
        env={**os.environ, "HAKO_GODOT_CPP_ROOT": str(godot_cpp_root)},
        check=True,
        capture_output=True,
        text=True,
    )
    return {
        "bridge_dir": bridge_dir,
        "library_path": bridge_dir / "bin" / "libhako_pdu_godot_smoke.dylib",
        "gdextension_path": bridge_dir / "hako_pdu_godot_smoke.gdextension",
    }


def run_godot_cpp_bridge_script(repo_root: Path, script_body: str):
    godot_bin = Path(
        os.environ.get(
            "HAKO_GODOT_BIN",
            "/Applications/Godot_mono.app/Contents/MacOS/Godot",
        )
    )
    if not godot_bin.exists():
        raise FileNotFoundError(f"Godot executable not found: {godot_bin}")

    bridge = ensure_godot_cpp_bridge(repo_root)
    with tempfile.TemporaryDirectory() as tmpdir:
        project_dir = Path(tmpdir)
        (project_dir / "project.godot").write_text(
            'config_version=5\n\n[application]\nconfig/name="hakoniwa-pdu-godot-cpp-validator"\n'
        )
        (project_dir / "hako_pdu_godot_smoke.gdextension").write_text(
            bridge["gdextension_path"].read_text()
        )
        (project_dir / "bin").mkdir()
        (project_dir / "bin" / "libhako_pdu_godot_smoke.dylib").write_bytes(
            bridge["library_path"].read_bytes()
        )
        (project_dir / "run_bridge.gd").write_text(script_body)
        return subprocess.run(
            [
                str(godot_bin),
                "--headless",
                "--path",
                str(project_dir),
                "--script",
                "res://run_bridge.gd",
            ],
            cwd=repo_root,
            env={**os.environ, "HOME": str(project_dir)},
            capture_output=True,
            text=True,
            check=True,
            timeout=30,
        )


def validate_godot_from_dict_roundtrip(repo_root: Path):
    godot_bin = Path(
        os.environ.get(
            "HAKO_GODOT_BIN",
            "/Applications/Godot_mono.app/Contents/MacOS/Godot",
        )
    )
    if not godot_bin.exists():
        return {
            "skipped": True,
            "reason": f"Godot executable not found: {godot_bin}",
        }

    generator = CodeGenerator(repo_root / "template")
    message_cache = {
        "builtin_interfaces/Time": {
            "package": "builtin_interfaces",
            "message": "Time",
            "fields": [
                {"name": "sec", "type": "int32"},
                {"name": "nanosec", "type": "uint32"},
            ],
        },
        "std_msgs/Header": {
            "package": "std_msgs",
            "message": "Header",
            "fields": [
                {"name": "stamp", "type": "builtin_interfaces/Time"},
                {"name": "frame_id", "type": "string"},
            ],
        },
        "geometry_msgs/Point": {
            "package": "geometry_msgs",
            "message": "Point",
            "fields": [
                {"name": "x", "type": "float64"},
                {"name": "y", "type": "float64"},
                {"name": "z", "type": "float64"},
            ],
        },
        "geometry_msgs/Vector3": {
            "package": "geometry_msgs",
            "message": "Vector3",
            "fields": [
                {"name": "x", "type": "float64"},
                {"name": "y", "type": "float64"},
                {"name": "z", "type": "float64"},
            ],
        },
        "hako_msgs/DisturbanceTemperature": {
            "package": "hako_msgs",
            "message": "DisturbanceTemperature",
            "fields": [{"name": "value", "type": "float64"}],
        },
        "hako_msgs/DisturbanceWind": {
            "package": "hako_msgs",
            "message": "DisturbanceWind",
            "fields": [{"name": "value", "type": "geometry_msgs/Vector3"}],
        },
        "hako_msgs/DisturbanceAtm": {
            "package": "hako_msgs",
            "message": "DisturbanceAtm",
            "fields": [{"name": "sea_level_atm", "type": "float64"}],
        },
        "hako_msgs/DisturbanceBoundary": {
            "package": "hako_msgs",
            "message": "DisturbanceBoundary",
            "fields": [
                {"name": "boundary_point", "type": "geometry_msgs/Point"},
                {"name": "boundary_normal", "type": "geometry_msgs/Vector3"},
            ],
        },
        "hako_msgs/DisturbanceUserCustom": {
            "package": "hako_msgs",
            "message": "DisturbanceUserCustom",
            "fields": [{"name": "data", "type": "float64[]"}],
        },
        "hako_msgs/Disturbance": {
            "package": "hako_msgs",
            "message": "Disturbance",
            "fields": [
                {"name": "d_temp", "type": "hako_msgs/DisturbanceTemperature"},
                {"name": "d_wind", "type": "hako_msgs/DisturbanceWind"},
                {"name": "d_atm", "type": "hako_msgs/DisturbanceAtm"},
                {"name": "d_boundary", "type": "hako_msgs/DisturbanceBoundary"},
                {"name": "d_user_custom", "type": "hako_msgs/DisturbanceUserCustom[]"},
            ],
        },
        "hako_msgs/SimpleVarray": {
            "package": "hako_msgs",
            "message": "SimpleVarray",
            "fields": [
                {"name": "data", "type": "int32[]"},
                {"name": "fixed_array", "type": "int32[2]"},
                {"name": "p_mem1", "type": "int32"},
            ],
        },
        "hako_msgs/SimpleStructVarray": {
            "package": "hako_msgs",
            "message": "SimpleStructVarray",
            "fields": [
                {"name": "aaa", "type": "int32"},
                {"name": "fixed_str", "type": "string[2]"},
                {"name": "varray_str", "type": "string[]"},
                {"name": "fixed_array", "type": "hako_msgs/SimpleVarray[5]"},
                {"name": "data", "type": "hako_msgs/SimpleVarray[]"},
            ],
        },
        "sensor_msgs/JointState": {
            "package": "sensor_msgs",
            "message": "JointState",
            "fields": [
                {"name": "header", "type": "std_msgs/Header"},
                {"name": "name", "type": "string[]"},
                {"name": "position", "type": "float64[]"},
                {"name": "velocity", "type": "float64[]"},
                {"name": "effort", "type": "float64[]"},
            ],
        },
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        project_dir = Path(tmpdir)
        generator.generate_all(message_cache, {}, project_dir)
        for name in ["types", "python", "javascript", "csharp", "csharp_v2", "godot_cpp_runtime"]:
            shutil.rmtree(project_dir / name)

        (project_dir / "project.godot").write_text(
            'config_version=5\n\n[application]\nconfig/name="hakoniwa-pdu-registry-godot-validator"\n'
        )
        (project_dir / "run_validator.gd").write_text(
            textwrap.dedent(
                """
                extends SceneTree

                const JointStateScript = preload("res://godot_gd/sensor_msgs/JointState.gd")
                const DisturbanceScript = preload("res://godot_gd/hako_msgs/Disturbance.gd")
                const SimpleStructVarrayScript = preload("res://godot_gd/hako_msgs/SimpleStructVarray.gd")

                func fail(message: String) -> void:
                    push_error(message)
                    quit(1)

                func expect_equal(actual, expected, label: String) -> void:
                    if actual != expected:
                        fail("%s: expected=%s actual=%s" % [label, str(expected), str(actual)])

                func make_joint_state_dict() -> Dictionary:
                    return {
                        "header": {"stamp": {"sec": 12, "nanosec": 34}, "frame_id": "base_link"},
                        "name": ["joint1", "joint2"],
                        "position": PackedFloat64Array([0.1, 0.2]),
                        "velocity": PackedFloat64Array([1.5]),
                        "effort": PackedFloat64Array()
                    }

                func make_disturbance_dict() -> Dictionary:
                    return {
                        "d_temp": {"value": 22.5},
                        "d_wind": {"value": {"x": 1.0, "y": 2.0, "z": 3.0}},
                        "d_atm": {"sea_level_atm": 1000.0},
                        "d_boundary": {
                            "boundary_point": {"x": 10.0, "y": 11.0, "z": 12.0},
                            "boundary_normal": {"x": 0.0, "y": 1.0, "z": 0.0}
                        },
                        "d_user_custom": [
                            {"data": PackedFloat64Array([1.25, 2.5])},
                            {"data": PackedFloat64Array([3.75])}
                        ]
                    }

                func make_simple_struct_varray_dict() -> Dictionary:
                    return {
                        "aaa": 7,
                        "fixed_str": ["alpha", "beta"],
                        "varray_str": ["x", "y", "z"],
                        "fixed_array": [
                            {"data": [1, 2], "fixed_array": [3, 4], "p_mem1": 5},
                            {"data": [], "fixed_array": [6, 7], "p_mem1": 8}
                        ],
                        "data": [
                            {"data": [9], "fixed_array": [10, 11], "p_mem1": 12}
                        ]
                    }

                func run_case(script_obj, input_dict: Dictionary, label: String) -> void:
                    var obj = script_obj.from_dict(input_dict)
                    var restored = obj.to_dict()
                    expect_equal(restored, input_dict, label)

                func _init() -> void:
                    run_case(JointStateScript, make_joint_state_dict(), "JointState roundtrip")
                    run_case(DisturbanceScript, make_disturbance_dict(), "Disturbance roundtrip")
                    run_case(SimpleStructVarrayScript, make_simple_struct_varray_dict(), "SimpleStructVarray roundtrip")
                    print("GODOT_VALIDATOR_OK")
                    quit(0)
                """
            ).lstrip()
        )

        result = subprocess.run(
            [
                str(godot_bin),
                "--headless",
                "--path",
                str(project_dir),
                "--script",
                "res://run_validator.gd",
            ],
            cwd=repo_root,
            env={**os.environ, "HOME": str(project_dir)},
            check=True,
            capture_output=True,
            text=True,
            timeout=30,
        )
        return {
            "skipped": False,
            "ok": "GODOT_VALIDATOR_OK" in (result.stdout + result.stderr),
            "stdout": result.stdout,
            "stderr": result.stderr,
        }


def validate_disturbance_user_custom_godot_cpp_oracle_interop(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_DisturbanceUserCustom import (
        pdu_to_py_DisturbanceUserCustom,
    )

    tools = ensure_cpp_oracle_tools(repo_root)
    expected = {"data": [1.25, 2.5]}

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "disturbance_user_custom_cpp.bin"
        godot_bin_path = tmpdir_path / "disturbance_user_custom_godot.bin"
        subprocess.run(
            [str(tools["disturbance_user_custom_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        decode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var file = FileAccess.open("{cpp_bin_path}", FileAccess.READ)
                if file == null:
                    fail("failed to open input binary")
                var restored = bridge.pdu_to_godot_disturbance_user_custom(file.get_buffer(file.get_length()))
                print(JSON.stringify({{"data": Array(restored["data"])}}, "", false))
                quit(0)
            """
        ).lstrip()
        decoded = run_godot_cpp_bridge_script(repo_root, decode_script)

        encode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_disturbance_user_custom({{"data": PackedFloat64Array([1.25, 2.5])}})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                quit(0)
            """
        ).lstrip()
        run_godot_cpp_bridge_script(repo_root, encode_script)

        godot_generated = pdu_to_py_DisturbanceUserCustom(bytearray(godot_bin_path.read_bytes()))
        if isinstance(godot_generated.data, list):
            godot_generated_data = godot_generated.data
        else:
            count = len(godot_generated.data) // 8
            godot_generated_data = list(struct.unpack(f"<{count}d", bytes(godot_generated.data)))

        return {
            "expected": expected,
            "cpp_to_godot": json.loads(decoded.stdout.strip().splitlines()[-1]),
            "godot_generated": {"data": godot_generated_data},
        }


def validate_game_controller_operation_godot_cpp_oracle_interop(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_GameControllerOperation import (
        pdu_to_py_GameControllerOperation,
    )

    tools = ensure_cpp_oracle_tools(repo_root)
    expected = {
        "axis": [0.5, -1.0, 2.0, -3.0, 4.0, -5.0],
        "button": [True, False, True, True, False, True, False, True, True, False, True, False, True, True, False],
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "game_controller_operation_cpp.bin"
        godot_bin_path = tmpdir_path / "game_controller_operation_godot.bin"
        subprocess.run(
            [str(tools["game_controller_operation_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        decode_script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var file = FileAccess.open("{cpp_bin_path}", FileAccess.READ)
                if file == null:
                    fail("failed to open input binary")
                var restored = bridge.pdu_to_godot_game_controller_operation(file.get_buffer(file.get_length()))
                print(JSON.stringify({{
                    "axis": Array(restored["axis"]),
                    "button": Array(restored["button"])
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        decoded = run_godot_cpp_bridge_script(repo_root, decode_script)

        encode_script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_game_controller_operation({json.dumps(expected)})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                quit(0)
            """
        ).lstrip()
        run_godot_cpp_bridge_script(repo_root, encode_script)

        godot_generated = pdu_to_py_GameControllerOperation(bytearray(godot_bin_path.read_bytes()))
        return {
            "expected": expected,
            "cpp_to_godot": json.loads(decoded.stdout.strip().splitlines()[-1]),
            "godot_generated": {
                "axis": list(godot_generated.axis),
                "button": [bool(value) for value in godot_generated.button],
            },
        }


def validate_disturbance_user_custom_godot_cpp_size_case(repo_root: Path, data_values):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_DisturbanceUserCustom import (
        pdu_to_py_DisturbanceUserCustom,
    )

    expected = {"data": list(data_values)}

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        godot_bin_path = tmpdir_path / "disturbance_user_custom_godot.bin"

        encode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_disturbance_user_custom({{"data": PackedFloat64Array({json.dumps(list(data_values))})}})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                var restored = bridge.pdu_to_godot_disturbance_user_custom(binary)
                print(JSON.stringify({{"data": Array(restored["data"])}}, "", false))
                quit(0)
            """
        ).lstrip()
        result = run_godot_cpp_bridge_script(repo_root, encode_script)
        godot_decoded = json.loads(result.stdout.strip().splitlines()[-1])

        py_generated = pdu_to_py_DisturbanceUserCustom(bytearray(godot_bin_path.read_bytes()))
        if isinstance(py_generated.data, list):
            python_decoded = py_generated.data
        else:
            count = len(py_generated.data) // 8
            python_decoded = list(struct.unpack(f"<{count}d", bytes(py_generated.data)))

        return {
            "expected": expected,
            "godot_decoded": godot_decoded,
            "python_decoded": {"data": python_decoded},
        }


def validate_joint_state_godot_cpp_oracle_interop(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.sensor_msgs.pdu_conv_JointState import pdu_to_py_JointState

    tools = ensure_cpp_oracle_tools(repo_root)
    expected = {
        "frame_id": "frame",
        "name": ["a", "b"],
        "position": [1.0, 2.0],
        "velocity": [3.0],
        "effort": [4.0],
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "joint_state_cpp.bin"
        godot_bin_path = tmpdir_path / "joint_state_godot.bin"
        subprocess.run(
            [str(tools["joint_state_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        decode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var file = FileAccess.open("{cpp_bin_path}", FileAccess.READ)
                if file == null:
                    fail("failed to open input binary")
                var restored = bridge.pdu_to_godot_joint_state(file.get_buffer(file.get_length()))
                print(JSON.stringify({{
                    "frame_id": restored["header"]["frame_id"],
                    "name": Array(restored["name"]),
                    "position": Array(restored["position"]),
                    "velocity": Array(restored["velocity"]),
                    "effort": Array(restored["effort"])
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        decoded = run_godot_cpp_bridge_script(repo_root, decode_script)

        encode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_joint_state({{
                    "header": {{"stamp": {{"sec": 0, "nanosec": 0}}, "frame_id": "frame"}},
                    "name": ["a", "b"],
                    "position": PackedFloat64Array([1.0, 2.0]),
                    "velocity": PackedFloat64Array([3.0]),
                    "effort": PackedFloat64Array([4.0])
                }})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                quit(0)
            """
        ).lstrip()
        run_godot_cpp_bridge_script(repo_root, encode_script)

        godot_generated = pdu_to_py_JointState(bytearray(godot_bin_path.read_bytes()))
        if isinstance(godot_generated.name, list):
            godot_generated_name = godot_generated.name
        else:
            godot_generated_name = []
            raw_name = bytes(godot_generated.name)
            for index in range(0, len(raw_name), 128):
                chunk = raw_name[index:index + 128]
                godot_generated_name.append(chunk.split(b"\0", 1)[0].decode("utf-8"))

        return {
            "expected": expected,
            "cpp_to_godot": json.loads(decoded.stdout.strip().splitlines()[-1]),
            "godot_generated": {
                "frame_id": godot_generated.header.frame_id,
                "name": godot_generated_name,
                "position": godot_generated.position if isinstance(godot_generated.position, list) else list(struct.unpack(f"<{len(godot_generated.position) // 8}d", bytes(godot_generated.position))),
                "velocity": godot_generated.velocity if isinstance(godot_generated.velocity, list) else list(struct.unpack(f"<{len(godot_generated.velocity) // 8}d", bytes(godot_generated.velocity))),
                "effort": godot_generated.effort if isinstance(godot_generated.effort, list) else list(struct.unpack(f"<{len(godot_generated.effort) // 8}d", bytes(godot_generated.effort))),
            },
        }


def validate_joint_state_godot_cpp_size_case(repo_root: Path, names, positions, velocities, efforts):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.sensor_msgs.pdu_conv_JointState import pdu_to_py_JointState

    expected = {
        "name": list(names),
        "position": list(positions),
        "velocity": list(velocities),
        "effort": list(efforts),
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        godot_bin_path = tmpdir_path / "joint_state_godot.bin"

        encode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_joint_state({{
                    "header": {{"stamp": {{"sec": 0, "nanosec": 0}}, "frame_id": "frame"}},
                    "name": {json.dumps(list(names))},
                    "position": PackedFloat64Array({json.dumps(list(positions))}),
                    "velocity": PackedFloat64Array({json.dumps(list(velocities))}),
                    "effort": PackedFloat64Array({json.dumps(list(efforts))})
                }})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                var restored = bridge.pdu_to_godot_joint_state(binary)
                print(JSON.stringify({{
                    "name": Array(restored["name"]),
                    "position": Array(restored["position"]),
                    "velocity": Array(restored["velocity"]),
                    "effort": Array(restored["effort"])
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        result = run_godot_cpp_bridge_script(repo_root, encode_script)
        godot_decoded = json.loads(result.stdout.strip().splitlines()[-1])

        python_generated = pdu_to_py_JointState(bytearray(godot_bin_path.read_bytes()))
        if isinstance(python_generated.name, list):
            python_names = python_generated.name
        else:
            python_names = []
            raw_name = bytes(python_generated.name)
            for index in range(0, len(raw_name), 128):
                chunk = raw_name[index:index + 128]
                python_names.append(chunk.split(b"\0", 1)[0].decode("utf-8"))

        return {
            "expected": expected,
            "godot_decoded": godot_decoded,
            "python_decoded": {
                "name": python_names,
                "position": python_generated.position if isinstance(python_generated.position, list) else list(struct.unpack(f"<{len(python_generated.position) // 8}d", bytes(python_generated.position))),
                "velocity": python_generated.velocity if isinstance(python_generated.velocity, list) else list(struct.unpack(f"<{len(python_generated.velocity) // 8}d", bytes(python_generated.velocity))),
                "effort": python_generated.effort if isinstance(python_generated.effort, list) else list(struct.unpack(f"<{len(python_generated.effort) // 8}d", bytes(python_generated.effort))),
            },
        }


def validate_simple_struct_varray_godot_cpp_oracle_interop(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_SimpleStructVarray import pdu_to_py_SimpleStructVarray

    def decode_simple_varray(item):
        data_value = item.data if isinstance(item.data, list) else list(bytes(item.data))
        fixed_value = item.fixed_array if isinstance(item.fixed_array, list) else list(bytes(item.fixed_array))
        return {
            "data": list(data_value),
            "fixed_array": list(fixed_value),
            "p_mem1": item.p_mem1,
        }

    expected = {
        "aaa": 7,
        "fixed_str": ["alpha", "beta"],
        "varray_str": ["gamma", "delta"],
        "fixed_array": [
            {"data": [1, 2], "fixed_array": [3, 4] + [0] * 8, "p_mem1": 5},
            {"data": [6], "fixed_array": [7, 8] + [0] * 8, "p_mem1": 9},
            {"data": [], "fixed_array": [0] * 10, "p_mem1": 0},
            {"data": [], "fixed_array": [0] * 10, "p_mem1": 0},
            {"data": [], "fixed_array": [0] * 10, "p_mem1": 0},
        ],
        "data": [
            {"data": [10, 11], "fixed_array": [12, 13] + [0] * 8, "p_mem1": 14},
            {"data": [15], "fixed_array": [16, 17] + [0] * 8, "p_mem1": 18},
        ],
    }

    tools = ensure_cpp_oracle_tools(repo_root)
    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "simple_struct_varray_cpp.bin"
        godot_bin_path = tmpdir_path / "simple_struct_varray_godot.bin"
        subprocess.run(
            [str(tools["simple_struct_varray_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        decode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func normalize_entry(entry: Dictionary) -> Dictionary:
                return {{
                    "data": Array(entry["data"]),
                    "fixed_array": Array(entry["fixed_array"]),
                    "p_mem1": entry["p_mem1"]
                }}

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var file = FileAccess.open("{cpp_bin_path}", FileAccess.READ)
                if file == null:
                    fail("failed to open input binary")
                var restored = bridge.pdu_to_godot_simple_struct_varray(file.get_buffer(file.get_length()))
                print(JSON.stringify({{
                    "aaa": restored["aaa"],
                    "fixed_str": Array(restored["fixed_str"]),
                    "varray_str": Array(restored["varray_str"]),
                    "fixed_array": restored["fixed_array"].map(normalize_entry),
                    "data": restored["data"].map(normalize_entry)
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        decoded = run_godot_cpp_bridge_script(repo_root, decode_script)

        encode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_simple_struct_varray({json.dumps(expected)})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                quit(0)
            """
        ).lstrip()
        run_godot_cpp_bridge_script(repo_root, encode_script)

        godot_generated = pdu_to_py_SimpleStructVarray(bytearray(godot_bin_path.read_bytes()))
        return {
            "expected": expected,
            "cpp_to_godot": json.loads(decoded.stdout.strip().splitlines()[-1]),
            "godot_generated": {
                "aaa": godot_generated.aaa,
                "fixed_str": list(godot_generated.fixed_str) if godot_generated.fixed_str is not None else [],
                "varray_str": list(godot_generated.varray_str) if isinstance(godot_generated.varray_str, list) else [],
                "fixed_array": [decode_simple_varray(item) for item in godot_generated.fixed_array],
                "data": [decode_simple_varray(item) for item in godot_generated.data],
            },
        }


def validate_simple_struct_varray_godot_cpp_size_case(repo_root: Path, varray_str_values, data_entries):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_SimpleStructVarray import pdu_to_py_SimpleStructVarray

    def decode_simple_varray(item):
        data_value = item.data if isinstance(item.data, list) else list(bytes(item.data))
        fixed_value = item.fixed_array if isinstance(item.fixed_array, list) else list(bytes(item.fixed_array))
        return {
            "data": list(data_value),
            "fixed_array": list(fixed_value),
            "p_mem1": item.p_mem1,
        }

    fixed_defaults = [{"data": [], "fixed_array": [0] * 10, "p_mem1": 0} for _ in range(5)]
    expected = {
        "varray_str": list(varray_str_values),
        "data": [
            {
                "data": list(spec["data"]),
                "fixed_array": list(spec["fixed_array"]) + [0] * (10 - len(spec["fixed_array"])),
                "p_mem1": spec["p_mem1"],
            }
            for spec in data_entries
        ],
    }
    encode_input = {
        "aaa": 7,
        "fixed_str": ["alpha", "beta"],
        "varray_str": list(varray_str_values),
        "fixed_array": fixed_defaults,
        "data": expected["data"],
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        godot_bin_path = tmpdir_path / "simple_struct_varray_godot.bin"

        encode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func normalize_entry(entry: Dictionary) -> Dictionary:
                return {{
                    "data": Array(entry["data"]),
                    "fixed_array": Array(entry["fixed_array"]),
                    "p_mem1": entry["p_mem1"]
                }}

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_simple_struct_varray({json.dumps(encode_input)})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                var restored = bridge.pdu_to_godot_simple_struct_varray(binary)
                print(JSON.stringify({{
                    "varray_str": Array(restored["varray_str"]),
                    "data": restored["data"].map(normalize_entry)
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        result = run_godot_cpp_bridge_script(repo_root, encode_script)
        godot_decoded = json.loads(result.stdout.strip().splitlines()[-1])

        python_generated = pdu_to_py_SimpleStructVarray(bytearray(godot_bin_path.read_bytes()))
        return {
            "expected": expected,
            "godot_decoded": godot_decoded,
            "python_decoded": {
                "varray_str": list(python_generated.varray_str) if isinstance(python_generated.varray_str, list) else [],
                "data": [decode_simple_varray(item) for item in python_generated.data],
            },
        }


def validate_disturbance_godot_cpp_oracle_interop(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_Disturbance import pdu_to_py_Disturbance

    tools = ensure_cpp_oracle_tools(repo_root)
    expected = {"d_user_custom": [[1.25, 2.5], [3.75]]}

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "disturbance_cpp.bin"
        godot_bin_path = tmpdir_path / "disturbance_godot.bin"
        subprocess.run(
            [str(tools["disturbance_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        decode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func normalize_custom(item: Dictionary) -> Array:
                return Array(item["data"])

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var file = FileAccess.open("{cpp_bin_path}", FileAccess.READ)
                if file == null:
                    fail("failed to open input binary")
                var restored = bridge.pdu_to_godot_disturbance(file.get_buffer(file.get_length()))
                print(JSON.stringify({{
                    "d_user_custom": restored["d_user_custom"].map(normalize_custom)
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        decoded = run_godot_cpp_bridge_script(repo_root, decode_script)

        encode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_disturbance({{
                    "d_temp": {{"value": 0.0}},
                    "d_wind": {{"value": {{"x": 0.0, "y": 0.0, "z": 0.0}}}},
                    "d_atm": {{"sea_level_atm": 0.0}},
                    "d_boundary": {{
                        "boundary_point": {{"x": 0.0, "y": 0.0, "z": 0.0}},
                        "boundary_normal": {{"x": 0.0, "y": 0.0, "z": 0.0}}
                    }},
                    "d_user_custom": [
                        {{"data": PackedFloat64Array([1.25, 2.5])}},
                        {{"data": PackedFloat64Array([3.75])}}
                    ]
                }})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                quit(0)
            """
        ).lstrip()
        run_godot_cpp_bridge_script(repo_root, encode_script)

        godot_generated = pdu_to_py_Disturbance(bytearray(godot_bin_path.read_bytes()))
        decoded_generated = []
        for item in godot_generated.d_user_custom:
            if isinstance(item.data, list):
                decoded_generated.append(item.data)
            else:
                count = len(item.data) // 8
                decoded_generated.append(list(struct.unpack(f"<{count}d", bytes(item.data))))

        return {
            "expected": expected,
            "cpp_to_godot": json.loads(decoded.stdout.strip().splitlines()[-1]),
            "godot_generated": {"d_user_custom": decoded_generated},
        }


def validate_disturbance_godot_cpp_size_case(repo_root: Path, data_sets):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_Disturbance import pdu_to_py_Disturbance

    expected = {"d_user_custom": [list(values) for values in data_sets]}
    godot_items = [
        {"data": list(values)}
        for values in data_sets
    ]

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        godot_bin_path = tmpdir_path / "disturbance_godot.bin"

        encode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func normalize_custom(item: Dictionary) -> Array:
                return Array(item["data"])

            func make_item(values: Array) -> Dictionary:
                return {{"data": PackedFloat64Array(values)}}

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var custom_items: Array = []
                for item in {json.dumps(godot_items)}:
                    custom_items.append(make_item(item["data"]))
                var binary = bridge.godot_to_pdu_disturbance({{
                    "d_temp": {{"value": 0.0}},
                    "d_wind": {{"value": {{"x": 0.0, "y": 0.0, "z": 0.0}}}},
                    "d_atm": {{"sea_level_atm": 0.0}},
                    "d_boundary": {{
                        "boundary_point": {{"x": 0.0, "y": 0.0, "z": 0.0}},
                        "boundary_normal": {{"x": 0.0, "y": 0.0, "z": 0.0}}
                    }},
                    "d_user_custom": custom_items
                }})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                var restored = bridge.pdu_to_godot_disturbance(binary)
                print(JSON.stringify({{
                    "d_user_custom": restored["d_user_custom"].map(normalize_custom)
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        result = run_godot_cpp_bridge_script(repo_root, encode_script)
        godot_decoded = json.loads(result.stdout.strip().splitlines()[-1])

        python_generated = pdu_to_py_Disturbance(bytearray(godot_bin_path.read_bytes()))
        decoded_generated = []
        for item in python_generated.d_user_custom:
            if isinstance(item.data, list):
                decoded_generated.append(item.data)
            else:
                count = len(item.data) // 8
                decoded_generated.append(list(struct.unpack(f"<{count}d", bytes(item.data))))

        return {
            "expected": expected,
            "godot_decoded": godot_decoded,
            "python_decoded": {"d_user_custom": decoded_generated},
        }


def validate_point_cloud2_godot_cpp_oracle_interop(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.sensor_msgs.pdu_conv_PointCloud2 import pdu_to_py_PointCloud2

    def decode_point_cloud(obj):
        data_value = obj.data if isinstance(obj.data, list) else list(bytes(obj.data))
        return {
            "header": {
                "stamp": {"sec": obj.header.stamp.sec, "nanosec": obj.header.stamp.nanosec},
                "frame_id": obj.header.frame_id,
            },
            "height": obj.height,
            "width": obj.width,
            "fields": [
                {"name": item.name, "offset": item.offset, "datatype": item.datatype, "count": item.count}
                for item in obj.fields
            ],
            "is_bigendian": bool(obj.is_bigendian),
            "point_step": obj.point_step,
            "row_step": obj.row_step,
            "data": list(data_value),
            "is_dense": bool(obj.is_dense),
        }

    expected = {
        "header": {"stamp": {"sec": 1, "nanosec": 200}, "frame_id": "pc"},
        "height": 2,
        "width": 3,
        "fields": [
            {"name": "x", "offset": 0, "datatype": 7, "count": 1},
            {"name": "intensity", "offset": 4, "datatype": 7, "count": 1},
        ],
        "is_bigendian": False,
        "point_step": 8,
        "row_step": 24,
        "data": [1, 2, 3, 4, 5, 6],
        "is_dense": True,
    }

    tools = ensure_cpp_oracle_tools(repo_root)
    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "point_cloud2_cpp.bin"
        godot_bin_path = tmpdir_path / "point_cloud2_godot.bin"
        subprocess.run(
            [str(tools["point_cloud2_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        decode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func normalize_field(item: Dictionary) -> Dictionary:
                return {{
                    "name": item["name"],
                    "offset": item["offset"],
                    "datatype": item["datatype"],
                    "count": item["count"]
                }}

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var file = FileAccess.open("{cpp_bin_path}", FileAccess.READ)
                if file == null:
                    fail("failed to open input binary")
                var restored = bridge.pdu_to_godot_point_cloud2(file.get_buffer(file.get_length()))
                print(JSON.stringify({{
                    "header": {{
                        "stamp": {{"sec": restored["header"]["stamp"]["sec"], "nanosec": restored["header"]["stamp"]["nanosec"]}},
                        "frame_id": restored["header"]["frame_id"]
                    }},
                    "height": restored["height"],
                    "width": restored["width"],
                    "fields": restored["fields"].map(normalize_field),
                    "is_bigendian": restored["is_bigendian"],
                    "point_step": restored["point_step"],
                    "row_step": restored["row_step"],
                    "data": Array(restored["data"]),
                    "is_dense": restored["is_dense"]
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        decoded = run_godot_cpp_bridge_script(repo_root, decode_script)

        encode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_point_cloud2({json.dumps(expected)})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                quit(0)
            """
        ).lstrip()
        run_godot_cpp_bridge_script(repo_root, encode_script)

        return {
            "expected": expected,
            "cpp_to_godot": json.loads(decoded.stdout.strip().splitlines()[-1]),
            "godot_generated": decode_point_cloud(pdu_to_py_PointCloud2(bytearray(godot_bin_path.read_bytes()))),
        }


def validate_point_cloud2_godot_cpp_size_case(repo_root: Path, field_specs, data_values):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.sensor_msgs.pdu_conv_PointCloud2 import pdu_to_py_PointCloud2

    expected = {
        "fields": [dict(spec) for spec in field_specs],
        "data": list(data_values),
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        godot_bin_path = tmpdir_path / "point_cloud2_godot.bin"

        encode_input = {
            "header": {"stamp": {"sec": 1, "nanosec": 200}, "frame_id": "pc"},
            "height": 2,
            "width": 3,
            "fields": [dict(spec) for spec in field_specs],
            "is_bigendian": False,
            "point_step": 8,
            "row_step": 24,
            "data": list(data_values),
            "is_dense": True,
        }
        encode_script = textwrap.dedent(
            f"""
            extends SceneTree

            func fail(message: String) -> void:
                push_error(message)
                quit(1)

            func normalize_field(item: Dictionary) -> Dictionary:
                return {{
                    "name": item["name"],
                    "offset": item["offset"],
                    "datatype": item["datatype"],
                    "count": item["count"]
                }}

            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_point_cloud2({json.dumps(encode_input)})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                var restored = bridge.pdu_to_godot_point_cloud2(binary)
                print(JSON.stringify({{
                    "fields": restored["fields"].map(normalize_field),
                    "data": Array(restored["data"])
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        result = run_godot_cpp_bridge_script(repo_root, encode_script)
        godot_decoded = json.loads(result.stdout.strip().splitlines()[-1])

        python_generated = pdu_to_py_PointCloud2(bytearray(godot_bin_path.read_bytes()))
        return {
            "expected": expected,
            "godot_decoded": godot_decoded,
            "python_decoded": {
                "fields": [
                    {"name": item.name, "offset": item.offset, "datatype": item.datatype, "count": item.count}
                    for item in python_generated.fields
                ],
                "data": list(python_generated.data if isinstance(python_generated.data, list) else bytes(python_generated.data)),
            },
        }


def validate_laser_scan_godot_cpp_oracle_interop(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.sensor_msgs.pdu_conv_LaserScan import pdu_to_py_LaserScan

    def decode_float32_varray(value):
        if isinstance(value, list):
            return list(value)
        if len(value) == 0:
            return []
        return list(struct.unpack(f"<{len(value) // 4}f", bytes(value)))

    expected = {"ranges": [1.5, 2.5], "intensities": [10.0, 20.0]}
    tools = ensure_cpp_oracle_tools(repo_root)
    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "laser_scan_cpp.bin"
        godot_bin_path = tmpdir_path / "laser_scan_godot.bin"
        subprocess.run(
            [str(tools["laser_scan_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        decode_script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var file = FileAccess.open("{cpp_bin_path}", FileAccess.READ)
                if file == null:
                    fail("failed to open input binary")
                var restored = bridge.pdu_to_godot_laser_scan(file.get_buffer(file.get_length()))
                print(JSON.stringify({{"ranges": Array(restored["ranges"]), "intensities": Array(restored["intensities"])}}, "", false))
                quit(0)
            """
        ).lstrip()
        decoded = run_godot_cpp_bridge_script(repo_root, decode_script)
        encode_script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_laser_scan({json.dumps({"header": {"stamp": {"sec": 1, "nanosec": 200}, "frame_id": "laser"}, "angle_min": -1.0, "angle_max": 1.0, "angle_increment": 0.5, "time_increment": 0.1, "scan_time": 0.2, "range_min": 0.3, "range_max": 30.0, "ranges": [1.5, 2.5], "intensities": [10.0, 20.0]})})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                quit(0)
            """
        ).lstrip()
        run_godot_cpp_bridge_script(repo_root, encode_script)
        py_generated = pdu_to_py_LaserScan(bytearray(godot_bin_path.read_bytes()))
        return {
            "expected": expected,
            "cpp_to_godot": json.loads(decoded.stdout.strip().splitlines()[-1]),
            "godot_generated": {
                "ranges": decode_float32_varray(py_generated.ranges),
                "intensities": decode_float32_varray(py_generated.intensities),
            },
        }


def validate_laser_scan_godot_cpp_size_case(repo_root: Path, ranges, intensities):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.sensor_msgs.pdu_conv_LaserScan import pdu_to_py_LaserScan

    def decode_float32_varray(value):
        if isinstance(value, list):
            return list(value)
        if len(value) == 0:
            return []
        return list(struct.unpack(f"<{len(value) // 4}f", bytes(value)))

    expected = {
        "ranges": list(ranges),
        "intensities": list(intensities),
    }
    encode_input = {
        "header": {"stamp": {"sec": 1, "nanosec": 200}, "frame_id": "laser"},
        "angle_min": -1.0,
        "angle_max": 1.0,
        "angle_increment": 0.5,
        "time_increment": 0.1,
        "scan_time": 0.2,
        "range_min": 0.3,
        "range_max": 30.0,
        "ranges": list(ranges),
        "intensities": list(intensities),
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        godot_bin_path = tmpdir_path / "laser_scan_godot.bin"
        script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_laser_scan({json.dumps(encode_input)})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                var restored = bridge.pdu_to_godot_laser_scan(binary)
                print(JSON.stringify({{
                    "ranges": Array(restored["ranges"]),
                    "intensities": Array(restored["intensities"])
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        result = run_godot_cpp_bridge_script(repo_root, script)
        python_generated = pdu_to_py_LaserScan(bytearray(godot_bin_path.read_bytes()))
        return {
            "expected": expected,
            "godot_decoded": json.loads(result.stdout.strip().splitlines()[-1]),
            "python_decoded": {
                "ranges": decode_float32_varray(python_generated.ranges),
                "intensities": decode_float32_varray(python_generated.intensities),
            },
        }


def validate_camera_info_godot_cpp_size_case(repo_root: Path, d_values):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.sensor_msgs.pdu_conv_CameraInfo import pdu_to_py_CameraInfo

    def decode_float64_varray(value):
        if isinstance(value, list):
            return list(value)
        if len(value) == 0:
            return []
        return list(struct.unpack(f"<{len(value) // 8}d", bytes(value)))

    expected = {"d": list(d_values)}
    encode_input = {
        "header": {"stamp": {"sec": 1, "nanosec": 200}, "frame_id": "cam"},
        "height": 480,
        "width": 640,
        "distortion_model": "plumb_bob",
        "d": list(d_values),
        "k": [1.0] * 9,
        "r": [2.0] * 9,
        "p": [3.0] * 12,
        "binning_x": 1,
        "binning_y": 2,
        "roi": {"x_offset": 3, "y_offset": 4, "height": 5, "width": 6, "do_rectify": True},
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        godot_bin_path = tmpdir_path / "camera_info_godot.bin"
        script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_camera_info({json.dumps(encode_input)})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                var restored = bridge.pdu_to_godot_camera_info(binary)
                print(JSON.stringify({{"d": Array(restored["d"])}}, "", false))
                quit(0)
            """
        ).lstrip()
        result = run_godot_cpp_bridge_script(repo_root, script)
        python_generated = pdu_to_py_CameraInfo(bytearray(godot_bin_path.read_bytes()))
        return {
            "expected": expected,
            "godot_decoded": json.loads(result.stdout.strip().splitlines()[-1]),
            "python_decoded": {"d": decode_float64_varray(python_generated.d)},
        }


def validate_camera_info_godot_cpp_oracle_interop(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.sensor_msgs.pdu_conv_CameraInfo import pdu_to_py_CameraInfo

    def decode_float64_varray(value):
        if isinstance(value, list):
            return list(value)
        if len(value) == 0:
            return []
        return list(struct.unpack(f"<{len(value) // 8}d", bytes(value)))

    expected = {"d": [0.1, 0.2]}
    tools = ensure_cpp_oracle_tools(repo_root)
    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "camera_info_cpp.bin"
        godot_bin_path = tmpdir_path / "camera_info_godot.bin"
        subprocess.run(
            [str(tools["camera_info_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        decode_script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var file = FileAccess.open("{cpp_bin_path}", FileAccess.READ)
                if file == null:
                    fail("failed to open input binary")
                var restored = bridge.pdu_to_godot_camera_info(file.get_buffer(file.get_length()))
                print(JSON.stringify({{"d": Array(restored["d"])}}, "", false))
                quit(0)
            """
        ).lstrip()
        decoded = run_godot_cpp_bridge_script(repo_root, decode_script)
        encode_script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_camera_info({json.dumps({"header": {"stamp": {"sec": 1, "nanosec": 200}, "frame_id": "cam"}, "height": 480, "width": 640, "distortion_model": "plumb_bob", "d": [0.1, 0.2], "k": [1.0] * 9, "r": [2.0] * 9, "p": [3.0] * 12, "binning_x": 1, "binning_y": 2, "roi": {"x_offset": 3, "y_offset": 4, "height": 5, "width": 6, "do_rectify": True}})})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                quit(0)
            """
        ).lstrip()
        run_godot_cpp_bridge_script(repo_root, encode_script)
        py_generated = pdu_to_py_CameraInfo(bytearray(godot_bin_path.read_bytes()))
        return {
            "expected": expected,
            "cpp_to_godot": json.loads(decoded.stdout.strip().splitlines()[-1]),
            "godot_generated": {"d": decode_float64_varray(py_generated.d)},
        }


def validate_multi_array_layout_godot_cpp_size_case(repo_root: Path, dim_specs):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.std_msgs.pdu_conv_MultiArrayLayout import pdu_to_py_MultiArrayLayout

    expected = {
        "dim": [dict(spec) for spec in dim_specs],
        "data_offset": 9,
    }
    encode_input = {
        "dim": [dict(spec) for spec in dim_specs],
        "data_offset": 9,
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        godot_bin_path = tmpdir_path / "multi_array_layout_godot.bin"
        script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func normalize_dim(item: Dictionary) -> Dictionary:
                return {{"label": item["label"], "size": item["size"], "stride": item["stride"]}}
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_multi_array_layout({json.dumps(encode_input)})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                var restored = bridge.pdu_to_godot_multi_array_layout(binary)
                print(JSON.stringify({{
                    "dim": restored["dim"].map(normalize_dim),
                    "data_offset": restored["data_offset"]
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        result = run_godot_cpp_bridge_script(repo_root, script)
        python_generated = pdu_to_py_MultiArrayLayout(bytearray(godot_bin_path.read_bytes()))
        return {
            "expected": expected,
            "godot_decoded": json.loads(result.stdout.strip().splitlines()[-1]),
            "python_decoded": {
                "dim": [{"label": item.label, "size": item.size, "stride": item.stride} for item in python_generated.dim],
                "data_offset": python_generated.data_offset,
            },
        }


def validate_multi_array_layout_godot_cpp_oracle_interop(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.std_msgs.pdu_conv_MultiArrayLayout import pdu_to_py_MultiArrayLayout

    expected = {
        "dim": [
            {"label": "x", "size": 2, "stride": 2},
            {"label": "y", "size": 3, "stride": 6},
        ],
        "data_offset": 9,
    }
    tools = ensure_cpp_oracle_tools(repo_root)
    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "multi_array_layout_cpp.bin"
        godot_bin_path = tmpdir_path / "multi_array_layout_godot.bin"
        subprocess.run(
            [str(tools["multi_array_layout_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        decode_script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func normalize_dim(item: Dictionary) -> Dictionary:
                return {{"label": item["label"], "size": item["size"], "stride": item["stride"]}}
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var file = FileAccess.open("{cpp_bin_path}", FileAccess.READ)
                if file == null:
                    fail("failed to open input binary")
                var restored = bridge.pdu_to_godot_multi_array_layout(file.get_buffer(file.get_length()))
                print(JSON.stringify({{"dim": restored["dim"].map(normalize_dim), "data_offset": restored["data_offset"]}}, "", false))
                quit(0)
            """
        ).lstrip()
        decoded = run_godot_cpp_bridge_script(repo_root, decode_script)
        encode_script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_multi_array_layout({json.dumps(expected)})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                quit(0)
            """
        ).lstrip()
        run_godot_cpp_bridge_script(repo_root, encode_script)
        py_generated = pdu_to_py_MultiArrayLayout(bytearray(godot_bin_path.read_bytes()))
        return {
            "expected": expected,
            "cpp_to_godot": json.loads(decoded.stdout.strip().splitlines()[-1]),
            "godot_generated": {
                "dim": [{"label": item.label, "size": item.size, "stride": item.stride} for item in py_generated.dim],
                "data_offset": py_generated.data_offset,
            },
        }


def validate_float64_multi_array_godot_cpp_size_case(repo_root: Path, dim_specs, data_values):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.std_msgs.pdu_conv_Float64MultiArray import pdu_to_py_Float64MultiArray

    def decode_float64_varray(value):
        if isinstance(value, list):
            return list(value)
        if len(value) == 0:
            return []
        return list(struct.unpack(f"<{len(value) // 8}d", bytes(value)))

    expected = {
        "layout": {"dim": [dict(spec) for spec in dim_specs], "data_offset": 9},
        "data": list(data_values),
    }
    encode_input = {
        "layout": {"dim": [dict(spec) for spec in dim_specs], "data_offset": 9},
        "data": list(data_values),
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        godot_bin_path = tmpdir_path / "float64_multi_array_godot.bin"
        script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func normalize_dim(item: Dictionary) -> Dictionary:
                return {{"label": item["label"], "size": item["size"], "stride": item["stride"]}}
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_float64_multi_array({json.dumps(encode_input)})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                var restored = bridge.pdu_to_godot_float64_multi_array(binary)
                print(JSON.stringify({{
                    "layout": {{
                        "dim": restored["layout"]["dim"].map(normalize_dim),
                        "data_offset": restored["layout"]["data_offset"]
                    }},
                    "data": Array(restored["data"])
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        result = run_godot_cpp_bridge_script(repo_root, script)
        python_generated = pdu_to_py_Float64MultiArray(bytearray(godot_bin_path.read_bytes()))
        return {
            "expected": expected,
            "godot_decoded": json.loads(result.stdout.strip().splitlines()[-1]),
            "python_decoded": {
                "layout": {
                    "dim": [{"label": item.label, "size": item.size, "stride": item.stride} for item in python_generated.layout.dim],
                    "data_offset": python_generated.layout.data_offset,
                },
                "data": decode_float64_varray(python_generated.data),
            },
        }


def validate_float64_multi_array_godot_cpp_oracle_interop(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.std_msgs.pdu_conv_Float64MultiArray import pdu_to_py_Float64MultiArray

    def decode_float64_varray(value):
        if isinstance(value, list):
            return list(value)
        if len(value) == 0:
            return []
        return list(struct.unpack(f"<{len(value) // 8}d", bytes(value)))

    expected = {
        "layout": {
            "dim": [
                {"label": "x", "size": 2, "stride": 2},
                {"label": "y", "size": 3, "stride": 6},
            ],
            "data_offset": 9,
        },
        "data": [1.5, 2.5],
    }
    tools = ensure_cpp_oracle_tools(repo_root)
    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "float64_multi_array_cpp.bin"
        godot_bin_path = tmpdir_path / "float64_multi_array_godot.bin"
        subprocess.run(
            [str(tools["float64_multi_array_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        decode_script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func normalize_dim(item: Dictionary) -> Dictionary:
                return {{"label": item["label"], "size": item["size"], "stride": item["stride"]}}
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var file = FileAccess.open("{cpp_bin_path}", FileAccess.READ)
                if file == null:
                    fail("failed to open input binary")
                var restored = bridge.pdu_to_godot_float64_multi_array(file.get_buffer(file.get_length()))
                print(JSON.stringify({{
                    "layout": {{
                        "dim": restored["layout"]["dim"].map(normalize_dim),
                        "data_offset": restored["layout"]["data_offset"]
                    }},
                    "data": Array(restored["data"])
                }}, "", false))
                quit(0)
            """
        ).lstrip()
        decoded = run_godot_cpp_bridge_script(repo_root, decode_script)
        encode_script = textwrap.dedent(
            f"""
            extends SceneTree
            func fail(message: String) -> void:
                push_error(message)
                quit(1)
            func _init() -> void:
                var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                if extension_resource == null:
                    fail("failed to load gdextension")
                var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                if bridge == null:
                    fail("failed to instantiate bridge")
                var binary = bridge.godot_to_pdu_float64_multi_array({json.dumps(expected)})
                var file = FileAccess.open("{godot_bin_path}", FileAccess.WRITE)
                if file == null:
                    fail("failed to open output binary")
                file.store_buffer(binary)
                quit(0)
            """
        ).lstrip()
        run_godot_cpp_bridge_script(repo_root, encode_script)
        py_generated = pdu_to_py_Float64MultiArray(bytearray(godot_bin_path.read_bytes()))
        return {
            "expected": expected,
            "cpp_to_godot": json.loads(decoded.stdout.strip().splitlines()[-1]),
            "godot_generated": {
                "layout": {
                    "dim": [{"label": item.label, "size": item.size, "stride": item.stride} for item in py_generated.layout.dim],
                    "data_offset": py_generated.layout.data_offset,
                },
                "data": decode_float64_varray(py_generated.data),
            },
        }


def validate_python_disturbance_layout(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_Disturbance import py_to_pdu_Disturbance
    from pdu.python.hako_msgs.pdu_pytype_Disturbance import Disturbance
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceAtm import DisturbanceAtm
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceBoundary import DisturbanceBoundary
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceTemperature import DisturbanceTemperature
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceUserCustom import DisturbanceUserCustom
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceWind import DisturbanceWind

    obj = Disturbance()
    obj.d_temp = DisturbanceTemperature()
    obj.d_wind = DisturbanceWind()
    obj.d_atm = DisturbanceAtm()
    obj.d_boundary = DisturbanceBoundary()
    item_1 = DisturbanceUserCustom()
    item_1.data = [1.25, 2.5]
    item_2 = DisturbanceUserCustom()
    item_2.data = [3.75]
    obj.d_user_custom = [item_1, item_2]

    binary = bytes(py_to_pdu_Disturbance(obj))
    heap_off = struct.unpack_from("<I", binary, 12)[0]
    top_len, top_off = struct.unpack_from("<ii", binary, 24 + 88)
    heap_bytes = binary[heap_off:]
    expected_heap_bytes = (
        struct.pack("<ii", 2, 16)
        + struct.pack("<ii", 1, 32)
        + struct.pack("<2d", 1.25, 2.5)
        + struct.pack("<1d", 3.75)
    )
    return {
        "top_len": top_len,
        "top_off": top_off,
        "heap_bytes": heap_bytes,
        "expected_top_len": 2,
        "expected_top_off": 0,
        "expected_heap_bytes": expected_heap_bytes,
    }


def validate_python_joint_state_layout(repo_root: Path):
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.builtin_interfaces.pdu_pytype_Time import Time
    from pdu.python.sensor_msgs.pdu_conv_JointState import py_to_pdu_JointState
    from pdu.python.sensor_msgs.pdu_pytype_JointState import JointState
    from pdu.python.std_msgs.pdu_pytype_Header import Header

    obj = JointState()
    obj.header = Header()
    obj.header.stamp = Time()
    obj.header.frame_id = "frame"
    obj.name = ["a", "b"]
    obj.position = [1.0, 2.0]
    obj.velocity = [3.0]
    obj.effort = [4.0]

    binary = bytes(py_to_pdu_JointState(obj))
    heap_off = struct.unpack_from("<I", binary, 12)[0]
    refs = {
        "name": struct.unpack_from("<ii", binary, 24 + 136),
        "position": struct.unpack_from("<ii", binary, 24 + 144),
        "velocity": struct.unpack_from("<ii", binary, 24 + 152),
        "effort": struct.unpack_from("<ii", binary, 24 + 160),
    }
    heap_bytes = binary[heap_off:]
    expected_name_bytes = bytearray(256)
    expected_name_bytes[0:2] = b"a\x00"
    expected_name_bytes[128:130] = b"b\x00"
    expected_heap_bytes = (
        bytes(expected_name_bytes)
        + struct.pack("<2d", 1.0, 2.0)
        + struct.pack("<1d", 3.0)
        + struct.pack("<1d", 4.0)
    )
    return {
        "refs": refs,
        "heap_bytes": heap_bytes,
        "expected_refs": {
            "name": (2, 0),
            "position": (2, 256),
            "velocity": (1, 272),
            "effort": (1, 280),
        },
        "expected_heap_bytes": expected_heap_bytes,
    }


def validate_disturbance_js_python_interop(repo_root: Path):
    py_to_js_script = """
import fs from 'node:fs';
import { pduToJs_Disturbance } from './pdu/javascript/hako_msgs/pdu_conv_Disturbance.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_Disturbance(arrayBuffer);
console.log(JSON.stringify({
  d_user_custom: obj.d_user_custom.map(item => item.data)
}));
"""
    js_to_py_script = """
import fs from 'node:fs';
import { Disturbance } from './pdu/javascript/hako_msgs/pdu_jstype_Disturbance.js';
import { DisturbanceTemperature } from './pdu/javascript/hako_msgs/pdu_jstype_DisturbanceTemperature.js';
import { DisturbanceWind } from './pdu/javascript/hako_msgs/pdu_jstype_DisturbanceWind.js';
import { DisturbanceAtm } from './pdu/javascript/hako_msgs/pdu_jstype_DisturbanceAtm.js';
import { DisturbanceBoundary } from './pdu/javascript/hako_msgs/pdu_jstype_DisturbanceBoundary.js';
import { DisturbanceUserCustom } from './pdu/javascript/hako_msgs/pdu_jstype_DisturbanceUserCustom.js';
import { jsToPdu_Disturbance } from './pdu/javascript/hako_msgs/pdu_conv_Disturbance.js';

const obj = new Disturbance();
obj.d_temp = new DisturbanceTemperature();
obj.d_wind = new DisturbanceWind();
obj.d_atm = new DisturbanceAtm();
obj.d_boundary = new DisturbanceBoundary();

const u1 = new DisturbanceUserCustom();
u1.data = [1.25, 2.5];
const u2 = new DisturbanceUserCustom();
u2.data = [3.75];
obj.d_user_custom = [u1, u2];

fs.writeFileSync(process.argv[1], Buffer.from(jsToPdu_Disturbance(obj)));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_Disturbance import (
        pdu_to_py_Disturbance,
        py_to_pdu_Disturbance,
    )
    from pdu.python.hako_msgs.pdu_pytype_Disturbance import Disturbance
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceAtm import DisturbanceAtm
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceBoundary import DisturbanceBoundary
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceTemperature import DisturbanceTemperature
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceUserCustom import DisturbanceUserCustom
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceWind import DisturbanceWind

    expected = [[1.25, 2.5], [3.75]]

    py_obj = Disturbance()
    py_obj.d_temp = DisturbanceTemperature()
    py_obj.d_wind = DisturbanceWind()
    py_obj.d_atm = DisturbanceAtm()
    py_obj.d_boundary = DisturbanceBoundary()
    user_1 = DisturbanceUserCustom()
    user_1.data = [1.25, 2.5]
    user_2 = DisturbanceUserCustom()
    user_2.data = [3.75]
    py_obj.d_user_custom = [user_1, user_2]

    with tempfile.TemporaryDirectory() as tmpdir:
        js_bin_path = Path(tmpdir) / "disturbance_js.bin"
        py_bin_path = Path(tmpdir) / "disturbance_py.bin"

        py_bin_path.write_bytes(py_to_pdu_Disturbance(py_obj))
        py_to_js = subprocess.run(
            ["node", "--input-type=module", "-e", py_to_js_script, str(py_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        py_to_js_data = json.loads(py_to_js.stdout)

        subprocess.run(
            ["node", "--input-type=module", "-e", js_to_py_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        restored = pdu_to_py_Disturbance(bytearray(js_bin_path.read_bytes()))
        js_to_py_data = []
        for item in restored.d_user_custom:
            if isinstance(item.data, list):
                js_to_py_data.append(item.data)
            else:
                count = len(item.data) // 8
                js_to_py_data.append(list(struct.unpack(f"<{count}d", bytes(item.data))))

        return {
            "expected": expected,
            "py_to_js": py_to_js_data["d_user_custom"],
            "js_to_py": js_to_py_data,
            "binaries_equal": py_bin_path.read_bytes() == js_bin_path.read_bytes(),
        }


def validate_disturbance_python_encode_size_case(repo_root: Path, data_sets):
    py_to_js_script = """
import fs from 'node:fs';
import { pduToJs_Disturbance } from './pdu/javascript/hako_msgs/pdu_conv_Disturbance.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_Disturbance(arrayBuffer);
console.log(JSON.stringify({
  d_user_custom: obj.d_user_custom.map(item => item.data)
}));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_Disturbance import (
        pdu_to_py_Disturbance,
        py_to_pdu_Disturbance,
    )
    from pdu.python.hako_msgs.pdu_pytype_Disturbance import Disturbance
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceAtm import DisturbanceAtm
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceBoundary import DisturbanceBoundary
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceTemperature import DisturbanceTemperature
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceUserCustom import DisturbanceUserCustom
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceWind import DisturbanceWind

    py_obj = Disturbance()
    py_obj.d_temp = DisturbanceTemperature()
    py_obj.d_wind = DisturbanceWind()
    py_obj.d_atm = DisturbanceAtm()
    py_obj.d_boundary = DisturbanceBoundary()
    py_obj.d_user_custom = []
    for data in data_sets:
        item = DisturbanceUserCustom()
        item.data = list(data)
        py_obj.d_user_custom.append(item)

    with tempfile.TemporaryDirectory() as tmpdir:
        py_bin_path = Path(tmpdir) / "disturbance_py.bin"
        py_bin_path.write_bytes(py_to_pdu_Disturbance(py_obj))

        py_restored = pdu_to_py_Disturbance(bytearray(py_bin_path.read_bytes()))
        py_decoded = []
        for item in py_restored.d_user_custom:
            if isinstance(item.data, list):
                py_decoded.append(item.data)
            else:
                count = len(item.data) // 8
                py_decoded.append(list(struct.unpack(f"<{count}d", bytes(item.data))))

        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", py_to_js_script, str(py_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": [list(data) for data in data_sets],
            "python_decoded": py_decoded,
            "javascript_decoded": json.loads(js_decode.stdout)["d_user_custom"],
        }


def validate_disturbance_user_custom_python_encode_size_case(repo_root: Path, data_values):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_DisturbanceUserCustom } from './pdu/javascript/hako_msgs/pdu_conv_DisturbanceUserCustom.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_DisturbanceUserCustom(arrayBuffer);
console.log(JSON.stringify({ data: obj.data }));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_DisturbanceUserCustom import (
        pdu_to_py_DisturbanceUserCustom,
        py_to_pdu_DisturbanceUserCustom,
    )
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceUserCustom import DisturbanceUserCustom

    py_obj = DisturbanceUserCustom()
    py_obj.data = list(data_values)

    with tempfile.TemporaryDirectory() as tmpdir:
        py_bin_path = Path(tmpdir) / "disturbance_user_custom_py.bin"
        py_bin_path.write_bytes(py_to_pdu_DisturbanceUserCustom(py_obj))

        py_restored = pdu_to_py_DisturbanceUserCustom(bytearray(py_bin_path.read_bytes()))
        if isinstance(py_restored.data, list):
            py_decoded = py_restored.data
        else:
            count = len(py_restored.data) // 8
            py_decoded = list(struct.unpack(f"<{count}d", bytes(py_restored.data)))

        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(py_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": list(data_values),
            "python_decoded": py_decoded,
            "javascript_decoded": json.loads(js_decode.stdout)["data"],
        }


def validate_joint_state_string_varray_interop(repo_root: Path):
    py_to_js_script = """
import fs from 'node:fs';
import { pduToJs_JointState } from './pdu/javascript/sensor_msgs/pdu_conv_JointState.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_JointState(arrayBuffer);
console.log(JSON.stringify({
  name: obj.name,
  position: obj.position,
  velocity: obj.velocity,
  effort: obj.effort
}));
"""
    js_to_py_script = """
import fs from 'node:fs';
import { JointState } from './pdu/javascript/sensor_msgs/pdu_jstype_JointState.js';
import { Header } from './pdu/javascript/std_msgs/pdu_jstype_Header.js';
import { Time } from './pdu/javascript/builtin_interfaces/pdu_jstype_Time.js';
import { jsToPdu_JointState } from './pdu/javascript/sensor_msgs/pdu_conv_JointState.js';

const obj = new JointState();
obj.header = new Header();
obj.header.stamp = new Time();
obj.header.frame_id = 'frame';
obj.name = ['a', 'b'];
obj.position = [1.0, 2.0];
obj.velocity = [3.0];
obj.effort = [4.0];

fs.writeFileSync(process.argv[1], Buffer.from(jsToPdu_JointState(obj)));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.builtin_interfaces.pdu_pytype_Time import Time
    from pdu.python.sensor_msgs.pdu_conv_JointState import pdu_to_py_JointState, py_to_pdu_JointState
    from pdu.python.sensor_msgs.pdu_pytype_JointState import JointState
    from pdu.python.std_msgs.pdu_pytype_Header import Header

    expected = {
        "name": ["a", "b"],
        "position": [1.0, 2.0],
        "velocity": [3.0],
        "effort": [4.0],
    }

    py_obj = JointState()
    py_obj.header = Header()
    py_obj.header.stamp = Time()
    py_obj.header.frame_id = "frame"
    py_obj.name = ["a", "b"]
    py_obj.position = [1.0, 2.0]
    py_obj.velocity = [3.0]
    py_obj.effort = [4.0]

    with tempfile.TemporaryDirectory() as tmpdir:
        js_bin_path = Path(tmpdir) / "joint_state_js.bin"
        py_bin_path = Path(tmpdir) / "joint_state_py.bin"

        py_bin_path.write_bytes(py_to_pdu_JointState(py_obj))
        py_to_js = subprocess.run(
            ["node", "--input-type=module", "-e", py_to_js_script, str(py_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        py_to_js_data = json.loads(py_to_js.stdout)

        subprocess.run(
            ["node", "--input-type=module", "-e", js_to_py_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        restored = pdu_to_py_JointState(bytearray(js_bin_path.read_bytes()))
        if isinstance(restored.name, list):
            name_value = restored.name
        else:
            name_value = []
            raw_name = bytes(restored.name)
            for index in range(0, len(raw_name), 128):
                chunk = raw_name[index:index + 128]
                name_value.append(chunk.split(b"\0", 1)[0].decode("utf-8"))
        js_to_py_data = {
            "name": name_value,
            "position": list(struct.unpack(f"<{len(restored.position) // 8}d", bytes(restored.position))) if not isinstance(restored.position, list) else restored.position,
            "velocity": list(struct.unpack(f"<{len(restored.velocity) // 8}d", bytes(restored.velocity))) if not isinstance(restored.velocity, list) else restored.velocity,
            "effort": list(struct.unpack(f"<{len(restored.effort) // 8}d", bytes(restored.effort))) if not isinstance(restored.effort, list) else restored.effort,
        }

        return {
            "expected": expected,
            "py_to_js": py_to_js_data,
            "js_to_py": js_to_py_data,
            "binaries_equal": py_bin_path.read_bytes() == js_bin_path.read_bytes(),
        }


def validate_joint_state_python_encode_size_case(repo_root: Path, names, positions, velocities, efforts):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_JointState } from './pdu/javascript/sensor_msgs/pdu_conv_JointState.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_JointState(arrayBuffer);
console.log(JSON.stringify({
  name: obj.name,
  position: obj.position,
  velocity: obj.velocity,
  effort: obj.effort
}));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.builtin_interfaces.pdu_pytype_Time import Time
    from pdu.python.sensor_msgs.pdu_conv_JointState import pdu_to_py_JointState, py_to_pdu_JointState
    from pdu.python.sensor_msgs.pdu_pytype_JointState import JointState
    from pdu.python.std_msgs.pdu_pytype_Header import Header

    py_obj = JointState()
    py_obj.header = Header()
    py_obj.header.stamp = Time()
    py_obj.header.frame_id = "frame"
    py_obj.name = list(names)
    py_obj.position = list(positions)
    py_obj.velocity = list(velocities)
    py_obj.effort = list(efforts)

    with tempfile.TemporaryDirectory() as tmpdir:
        py_bin_path = Path(tmpdir) / "joint_state_py.bin"
        py_bin_path.write_bytes(py_to_pdu_JointState(py_obj))

        restored = pdu_to_py_JointState(bytearray(py_bin_path.read_bytes()))
        if isinstance(restored.name, list):
            restored_name = restored.name
        else:
            restored_name = []
            raw_name = bytes(restored.name)
            for index in range(0, len(raw_name), 128):
                chunk = raw_name[index:index + 128]
                restored_name.append(chunk.split(b"\0", 1)[0].decode("utf-8"))

        def decode_numeric(value):
            if isinstance(value, list):
                return value
            count = len(value) // 8
            return list(struct.unpack(f"<{count}d", bytes(value)))

        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(py_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": {
                "name": list(names),
                "position": list(positions),
                "velocity": list(velocities),
                "effort": list(efforts),
            },
            "python_decoded": {
                "name": restored_name,
                "position": decode_numeric(restored.position),
                "velocity": decode_numeric(restored.velocity),
                "effort": decode_numeric(restored.effort),
            },
            "javascript_decoded": json.loads(js_decode.stdout),
        }


def validate_drone_visual_state_array_python_encode_size_case(repo_root: Path, drones):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_DroneVisualStateArray } from './pdu/javascript/hako_msgs/pdu_conv_DroneVisualStateArray.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_DroneVisualStateArray(arrayBuffer);
console.log(JSON.stringify({
  sequence_id: obj.sequence_id,
  chunk_index: obj.chunk_index,
  chunk_count: obj.chunk_count,
  start_index: obj.start_index,
  valid_count: obj.valid_count,
  drones: obj.drones.map(item => ({
    x: item.x,
    y: item.y,
    z: item.z,
    roll: item.roll,
    pitch: item.pitch,
    yaw: item.yaw,
    pwm_duty: item.pwm_duty
  }))
}));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_DroneVisualStateArray import (
        pdu_to_py_DroneVisualStateArray,
        py_to_pdu_DroneVisualStateArray,
    )
    from pdu.python.hako_msgs.pdu_pytype_DroneVisualState import DroneVisualState
    from pdu.python.hako_msgs.pdu_pytype_DroneVisualStateArray import DroneVisualStateArray

    def f32(value):
        return struct.unpack("<f", struct.pack("<f", float(value)))[0]

    def normalize_drone(item):
        pwm_duty = item.pwm_duty
        if not isinstance(pwm_duty, list):
            pwm_duty = list(struct.unpack(f"<{len(pwm_duty) // 4}f", bytes(pwm_duty))) if len(pwm_duty) > 0 else []
        return {
            "x": f32(item.x),
            "y": f32(item.y),
            "z": f32(item.z),
            "roll": f32(item.roll),
            "pitch": f32(item.pitch),
            "yaw": f32(item.yaw),
            "pwm_duty": [f32(value) for value in pwm_duty],
        }

    py_obj = DroneVisualStateArray()
    py_obj.sequence_id = 42
    py_obj.chunk_index = 3
    py_obj.chunk_count = 10
    py_obj.start_index = 300
    py_obj.valid_count = len(drones)
    for drone in drones:
        item = DroneVisualState()
        item.x = drone["x"]
        item.y = drone["y"]
        item.z = drone["z"]
        item.roll = drone["roll"]
        item.pitch = drone["pitch"]
        item.yaw = drone["yaw"]
        item.pwm_duty = list(drone["pwm_duty"])
        py_obj.drones.append(item)

    with tempfile.TemporaryDirectory() as tmpdir:
        py_bin_path = Path(tmpdir) / "drone_visual_state_array_py.bin"
        py_bin_path.write_bytes(py_to_pdu_DroneVisualStateArray(py_obj))

        restored = pdu_to_py_DroneVisualStateArray(bytearray(py_bin_path.read_bytes()))
        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(py_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        js_decoded = json.loads(js_decode.stdout)

        return {
            "expected": {
                "sequence_id": 42,
                "chunk_index": 3,
                "chunk_count": 10,
                "start_index": 300,
                "valid_count": len(drones),
                "drones": [
                    {
                        "x": f32(drone["x"]),
                        "y": f32(drone["y"]),
                        "z": f32(drone["z"]),
                        "roll": f32(drone["roll"]),
                        "pitch": f32(drone["pitch"]),
                        "yaw": f32(drone["yaw"]),
                        "pwm_duty": [f32(value) for value in drone["pwm_duty"]],
                    }
                    for drone in drones
                ],
            },
            "python_decoded": {
                "sequence_id": restored.sequence_id,
                "chunk_index": restored.chunk_index,
                "chunk_count": restored.chunk_count,
                "start_index": restored.start_index,
                "valid_count": restored.valid_count,
                "drones": [normalize_drone(item) for item in restored.drones],
            },
            "javascript_decoded": {
                "sequence_id": js_decoded["sequence_id"],
                "chunk_index": js_decoded["chunk_index"],
                "chunk_count": js_decoded["chunk_count"],
                "start_index": js_decoded["start_index"],
                "valid_count": js_decoded["valid_count"],
                "drones": [
                    {
                        "x": f32(item["x"]),
                        "y": f32(item["y"]),
                        "z": f32(item["z"]),
                        "roll": f32(item["roll"]),
                        "pitch": f32(item["pitch"]),
                        "yaw": f32(item["yaw"]),
                        "pwm_duty": [f32(value) for value in item["pwm_duty"]],
                    }
                    for item in js_decoded["drones"]
                ],
            },
        }


def make_drone_visual_state_array_case(drone_count=100, pwm_count=4):
    def f32(value):
        return struct.unpack("<f", struct.pack("<f", float(value)))[0]

    def f32_add(lhs, rhs):
        return f32(f32(lhs) + f32(rhs))

    def f32_mul(lhs, rhs):
        return f32(f32(lhs) * f32(rhs))

    pwm_bases = [0.1, 0.2, 0.3, 0.4]
    drones = []
    for index in range(drone_count):
        base = f32(index)
        pwm_delta = f32_mul(base, 0.001)
        drones.append(
            {
                "x": f32_add(base, 0.1),
                "y": f32_add(base, 0.2),
                "z": f32_add(base, 0.3),
                "roll": f32_add(base, 0.01),
                "pitch": f32_add(base, 0.02),
                "yaw": f32_add(base, 0.03),
                "pwm_duty": [f32_add(pwm_bases[slot], pwm_delta) for slot in range(pwm_count)],
            }
        )
    return drones


def ensure_cpp_oracle_tools(repo_root: Path):
    subprocess.run(
        ["cmake", "-S", str(repo_root / "tests" / "cpp"), "-B", str(CPP_ORACLE_BUILD_DIR)],
        cwd=repo_root,
        check=True,
        capture_output=True,
        text=True,
    )
    subprocess.run(
        [
            "cmake",
            "--build",
            str(CPP_ORACLE_BUILD_DIR),
            "-j4",
            "--target",
            "hakoniwa_pdu_cpp_tests",
            "drone_visual_state_array_cpp_dump",
            "disturbance_cpp_dump",
            "disturbance_user_custom_cpp_dump",
            "game_controller_operation_cpp_dump",
            "joint_state_cpp_dump",
            "laser_scan_cpp_dump",
            "camera_info_cpp_dump",
            "multi_array_layout_cpp_dump",
            "float64_multi_array_cpp_dump",
            "point_cloud2_cpp_dump",
            "simple_struct_varray_cpp_dump",
        ],
        cwd=repo_root,
        check=True,
        capture_output=True,
        text=True,
    )
    return {
        "test_bin": CPP_ORACLE_BUILD_DIR / "hakoniwa_pdu_cpp_tests",
        "drone_visual_state_array_dump": CPP_ORACLE_BUILD_DIR / "drone_visual_state_array_cpp_dump",
        "disturbance_dump": CPP_ORACLE_BUILD_DIR / "disturbance_cpp_dump",
        "disturbance_user_custom_dump": CPP_ORACLE_BUILD_DIR / "disturbance_user_custom_cpp_dump",
        "game_controller_operation_dump": CPP_ORACLE_BUILD_DIR / "game_controller_operation_cpp_dump",
        "joint_state_dump": CPP_ORACLE_BUILD_DIR / "joint_state_cpp_dump",
        "laser_scan_dump": CPP_ORACLE_BUILD_DIR / "laser_scan_cpp_dump",
        "camera_info_dump": CPP_ORACLE_BUILD_DIR / "camera_info_cpp_dump",
        "multi_array_layout_dump": CPP_ORACLE_BUILD_DIR / "multi_array_layout_cpp_dump",
        "float64_multi_array_dump": CPP_ORACLE_BUILD_DIR / "float64_multi_array_cpp_dump",
        "point_cloud2_dump": CPP_ORACLE_BUILD_DIR / "point_cloud2_cpp_dump",
        "simple_struct_varray_dump": CPP_ORACLE_BUILD_DIR / "simple_struct_varray_cpp_dump",
    }


def validate_game_controller_operation_cpp_oracle_interop(repo_root: Path):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_GameControllerOperation } from './pdu/javascript/hako_msgs/pdu_conv_GameControllerOperation.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_GameControllerOperation(arrayBuffer);
console.log(JSON.stringify({
  axis: obj.axis,
  button: obj.button
}));
"""
    js_encode_script = """
import fs from 'node:fs';
import { GameControllerOperation } from './pdu/javascript/hako_msgs/pdu_jstype_GameControllerOperation.js';
import { jsToPdu_GameControllerOperation } from './pdu/javascript/hako_msgs/pdu_conv_GameControllerOperation.js';

const obj = new GameControllerOperation();
obj.axis = [0.5, -1.0, 2.0, -3.0, 4.0, -5.0];
obj.button = [true, false, true, true, false, true, false, true, true, false, true, false, true, true, false];

fs.writeFileSync(process.argv[1], Buffer.from(jsToPdu_GameControllerOperation(obj)));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_GameControllerOperation import (
        pdu_to_py_GameControllerOperation,
        py_to_pdu_GameControllerOperation,
    )
    from pdu.python.hako_msgs.pdu_pytype_GameControllerOperation import (
        GameControllerOperation,
    )

    tools = ensure_cpp_oracle_tools(repo_root)
    expected = {
        "axis": [0.5, -1.0, 2.0, -3.0, 4.0, -5.0],
        "button": [True, False, True, True, False, True, False, True, True, False, True, False, True, True, False],
    }

    py_obj = GameControllerOperation()
    py_obj.axis = expected["axis"].copy()
    py_obj.button = expected["button"].copy()

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "game_controller_operation_cpp.bin"
        py_bin_path = tmpdir_path / "game_controller_operation_py.bin"
        js_bin_path = tmpdir_path / "game_controller_operation_js.bin"

        subprocess.run(
            [str(tools["game_controller_operation_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        py_bin_path.write_bytes(py_to_pdu_GameControllerOperation(py_obj))
        subprocess.run(
            ["node", "--input-type=module", "-e", js_encode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        cpp_to_python = pdu_to_py_GameControllerOperation(bytearray(cpp_bin_path.read_bytes()))
        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        py_generated = pdu_to_py_GameControllerOperation(bytearray(py_bin_path.read_bytes()))
        js_generated_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": expected,
            "cpp_to_python": {
                "axis": list(cpp_to_python.axis),
                "button": [bool(value) for value in cpp_to_python.button],
            },
            "cpp_to_javascript": json.loads(js_decode.stdout),
            "python_generated": {
                "axis": list(py_generated.axis),
                "button": [bool(value) for value in py_generated.button],
            },
            "javascript_generated": json.loads(js_generated_decode.stdout),
        }


def validate_drone_visual_state_array_cpp_oracle_interop(repo_root: Path):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_DroneVisualStateArray } from './pdu/javascript/hako_msgs/pdu_conv_DroneVisualStateArray.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_DroneVisualStateArray(arrayBuffer);
console.log(JSON.stringify({
  sequence_id: obj.sequence_id,
  chunk_index: obj.chunk_index,
  chunk_count: obj.chunk_count,
  start_index: obj.start_index,
  valid_count: obj.valid_count,
  drones: obj.drones.map(item => ({
    x: item.x,
    y: item.y,
    z: item.z,
    roll: item.roll,
    pitch: item.pitch,
    yaw: item.yaw,
    pwm_duty: item.pwm_duty
  }))
}));
"""
    js_encode_script = """
import fs from 'node:fs';
import { pduToJs_DroneVisualStateArray, jsToPdu_DroneVisualStateArray } from './pdu/javascript/hako_msgs/pdu_conv_DroneVisualStateArray.js';
import { DroneVisualStateArray } from './pdu/javascript/hako_msgs/pdu_jstype_DroneVisualStateArray.js';

const src = fs.readFileSync(process.argv[1]);
const srcArrayBuffer = src.buffer.slice(src.byteOffset, src.byteOffset + src.byteLength);
const decoded = pduToJs_DroneVisualStateArray(srcArrayBuffer);
const obj = DroneVisualStateArray.fromDict(decoded.toDict());

fs.writeFileSync(process.argv[2], Buffer.from(jsToPdu_DroneVisualStateArray(obj)));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_DroneVisualStateArray import (
        pdu_to_py_DroneVisualStateArray,
        py_to_pdu_DroneVisualStateArray,
    )
    from pdu.python.hako_msgs.pdu_pytype_DroneVisualState import DroneVisualState
    from pdu.python.hako_msgs.pdu_pytype_DroneVisualStateArray import DroneVisualStateArray

    tools = ensure_cpp_oracle_tools(repo_root)

    def f32(value):
        return struct.unpack("<f", struct.pack("<f", float(value)))[0]

    def normalize_drone(item):
        pwm_duty = item.pwm_duty
        if not isinstance(pwm_duty, list):
            pwm_duty = list(struct.unpack(f"<{len(pwm_duty) // 4}f", bytes(pwm_duty))) if len(pwm_duty) > 0 else []
        return {
            "x": f32(item.x),
            "y": f32(item.y),
            "z": f32(item.z),
            "roll": f32(item.roll),
            "pitch": f32(item.pitch),
            "yaw": f32(item.yaw),
            "pwm_duty": [f32(value) for value in pwm_duty],
        }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "drone_visual_state_array_cpp.bin"
        py_bin_path = tmpdir_path / "drone_visual_state_array_py.bin"
        js_bin_path = tmpdir_path / "drone_visual_state_array_js.bin"

        subprocess.run(
            [str(tools["drone_visual_state_array_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        cpp_to_python = pdu_to_py_DroneVisualStateArray(bytearray(cpp_bin_path.read_bytes()))
        cpp_oracle = {
            "sequence_id": cpp_to_python.sequence_id,
            "chunk_index": cpp_to_python.chunk_index,
            "chunk_count": cpp_to_python.chunk_count,
            "start_index": cpp_to_python.start_index,
            "valid_count": cpp_to_python.valid_count,
            "drones": [normalize_drone(item) for item in cpp_to_python.drones],
        }

        py_obj = DroneVisualStateArray()
        py_obj.sequence_id = cpp_oracle["sequence_id"]
        py_obj.chunk_index = cpp_oracle["chunk_index"]
        py_obj.chunk_count = cpp_oracle["chunk_count"]
        py_obj.start_index = cpp_oracle["start_index"]
        py_obj.valid_count = cpp_oracle["valid_count"]
        for drone in cpp_oracle["drones"]:
            item = DroneVisualState()
            item.x = drone["x"]
            item.y = drone["y"]
            item.z = drone["z"]
            item.roll = drone["roll"]
            item.pitch = drone["pitch"]
            item.yaw = drone["yaw"]
            item.pwm_duty = list(drone["pwm_duty"])
            py_obj.drones.append(item)

        py_bin_path.write_bytes(py_to_pdu_DroneVisualStateArray(py_obj))
        subprocess.run(
            ["node", "--input-type=module", "-e", js_encode_script, str(cpp_bin_path), str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        py_generated = pdu_to_py_DroneVisualStateArray(bytearray(py_bin_path.read_bytes()))
        js_generated_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        js_decoded = json.loads(js_decode.stdout)
        js_generated_decoded = json.loads(js_generated_decode.stdout)

        return {
            "expected": cpp_oracle,
            "cpp_to_python": cpp_oracle,
            "cpp_to_javascript": {
                "sequence_id": js_decoded["sequence_id"],
                "chunk_index": js_decoded["chunk_index"],
                "chunk_count": js_decoded["chunk_count"],
                "start_index": js_decoded["start_index"],
                "valid_count": js_decoded["valid_count"],
                "drones": [
                    {
                        "x": f32(item["x"]),
                        "y": f32(item["y"]),
                        "z": f32(item["z"]),
                        "roll": f32(item["roll"]),
                        "pitch": f32(item["pitch"]),
                        "yaw": f32(item["yaw"]),
                        "pwm_duty": [f32(value) for value in item["pwm_duty"]],
                    }
                    for item in js_decoded["drones"]
                ],
            },
            "python_generated": {
                "sequence_id": py_generated.sequence_id,
                "chunk_index": py_generated.chunk_index,
                "chunk_count": py_generated.chunk_count,
                "start_index": py_generated.start_index,
                "valid_count": py_generated.valid_count,
                "drones": [normalize_drone(item) for item in py_generated.drones],
            },
            "javascript_generated": {
                "sequence_id": js_generated_decoded["sequence_id"],
                "chunk_index": js_generated_decoded["chunk_index"],
                "chunk_count": js_generated_decoded["chunk_count"],
                "start_index": js_generated_decoded["start_index"],
                "valid_count": js_generated_decoded["valid_count"],
                "drones": [
                    {
                        "x": f32(item["x"]),
                        "y": f32(item["y"]),
                        "z": f32(item["z"]),
                        "roll": f32(item["roll"]),
                        "pitch": f32(item["pitch"]),
                        "yaw": f32(item["yaw"]),
                        "pwm_duty": [f32(value) for value in item["pwm_duty"]],
                    }
                    for item in js_generated_decoded["drones"]
                ],
            },
        }


def validate_disturbance_cpp_oracle_interop(repo_root: Path):
    py_decode_script = """
import fs from 'node:fs';
import { pduToJs_Disturbance } from './pdu/javascript/hako_msgs/pdu_conv_Disturbance.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_Disturbance(arrayBuffer);
console.log(JSON.stringify({
  d_user_custom: obj.d_user_custom.map(item => item.data)
}));
"""
    js_encode_script = """
import fs from 'node:fs';
import { Disturbance } from './pdu/javascript/hako_msgs/pdu_jstype_Disturbance.js';
import { DisturbanceTemperature } from './pdu/javascript/hako_msgs/pdu_jstype_DisturbanceTemperature.js';
import { DisturbanceWind } from './pdu/javascript/hako_msgs/pdu_jstype_DisturbanceWind.js';
import { DisturbanceAtm } from './pdu/javascript/hako_msgs/pdu_jstype_DisturbanceAtm.js';
import { DisturbanceBoundary } from './pdu/javascript/hako_msgs/pdu_jstype_DisturbanceBoundary.js';
import { DisturbanceUserCustom } from './pdu/javascript/hako_msgs/pdu_jstype_DisturbanceUserCustom.js';
import { jsToPdu_Disturbance } from './pdu/javascript/hako_msgs/pdu_conv_Disturbance.js';

const obj = new Disturbance();
obj.d_temp = new DisturbanceTemperature();
obj.d_wind = new DisturbanceWind();
obj.d_atm = new DisturbanceAtm();
obj.d_boundary = new DisturbanceBoundary();
const item1 = new DisturbanceUserCustom();
item1.data = [1.25, 2.5];
const item2 = new DisturbanceUserCustom();
item2.data = [3.75];
obj.d_user_custom = [item1, item2];

fs.writeFileSync(process.argv[1], Buffer.from(jsToPdu_Disturbance(obj)));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_Disturbance import (
        pdu_to_py_Disturbance,
        py_to_pdu_Disturbance,
    )
    from pdu.python.hako_msgs.pdu_pytype_Disturbance import Disturbance
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceAtm import DisturbanceAtm
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceBoundary import DisturbanceBoundary
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceTemperature import DisturbanceTemperature
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceUserCustom import DisturbanceUserCustom
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceWind import DisturbanceWind

    tools = ensure_cpp_oracle_tools(repo_root)
    expected = [[1.25, 2.5], [3.75]]

    py_obj = Disturbance()
    py_obj.d_temp = DisturbanceTemperature()
    py_obj.d_wind = DisturbanceWind()
    py_obj.d_atm = DisturbanceAtm()
    py_obj.d_boundary = DisturbanceBoundary()
    item_1 = DisturbanceUserCustom()
    item_1.data = [1.25, 2.5]
    item_2 = DisturbanceUserCustom()
    item_2.data = [3.75]
    py_obj.d_user_custom = [item_1, item_2]

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "disturbance_cpp.bin"
        py_bin_path = tmpdir_path / "disturbance_py.bin"
        js_bin_path = tmpdir_path / "disturbance_js.bin"

        subprocess.run(
            [str(tools["disturbance_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        py_bin_path.write_bytes(py_to_pdu_Disturbance(py_obj))
        subprocess.run(
            ["node", "--input-type=module", "-e", js_encode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        py_restored = pdu_to_py_Disturbance(bytearray(cpp_bin_path.read_bytes()))
        py_decoded = []
        for item in py_restored.d_user_custom:
            if isinstance(item.data, list):
                py_decoded.append(item.data)
            else:
                count = len(item.data) // 8
                py_decoded.append(list(struct.unpack(f"<{count}d", bytes(item.data))))

        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", py_decode_script, str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        py_generated = pdu_to_py_Disturbance(bytearray(py_bin_path.read_bytes()))
        py_generated_decoded = []
        for item in py_generated.d_user_custom:
            if isinstance(item.data, list):
                py_generated_decoded.append(item.data)
            else:
                count = len(item.data) // 8
                py_generated_decoded.append(list(struct.unpack(f"<{count}d", bytes(item.data))))

        js_generated_decode = subprocess.run(
            ["node", "--input-type=module", "-e", py_decode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": expected,
            "cpp_to_python": py_decoded,
            "cpp_to_javascript": json.loads(js_decode.stdout)["d_user_custom"],
            "python_generated": py_generated_decoded,
            "javascript_generated": json.loads(js_generated_decode.stdout)["d_user_custom"],
        }


def validate_disturbance_user_custom_cpp_oracle_interop(repo_root: Path):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_DisturbanceUserCustom } from './pdu/javascript/hako_msgs/pdu_conv_DisturbanceUserCustom.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_DisturbanceUserCustom(arrayBuffer);
console.log(JSON.stringify({
  data: obj.data
}));
"""
    js_encode_script = """
import fs from 'node:fs';
import { DisturbanceUserCustom } from './pdu/javascript/hako_msgs/pdu_jstype_DisturbanceUserCustom.js';
import { jsToPdu_DisturbanceUserCustom } from './pdu/javascript/hako_msgs/pdu_conv_DisturbanceUserCustom.js';

const obj = new DisturbanceUserCustom();
obj.data = [1.25, 2.5];

fs.writeFileSync(process.argv[1], Buffer.from(jsToPdu_DisturbanceUserCustom(obj)));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_DisturbanceUserCustom import (
        pdu_to_py_DisturbanceUserCustom,
        py_to_pdu_DisturbanceUserCustom,
    )
    from pdu.python.hako_msgs.pdu_pytype_DisturbanceUserCustom import (
        DisturbanceUserCustom,
    )

    tools = ensure_cpp_oracle_tools(repo_root)
    expected = {"data": [1.25, 2.5]}

    py_obj = DisturbanceUserCustom()
    py_obj.data = expected["data"].copy()

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "disturbance_user_custom_cpp.bin"
        py_bin_path = tmpdir_path / "disturbance_user_custom_py.bin"
        js_bin_path = tmpdir_path / "disturbance_user_custom_js.bin"

        subprocess.run(
            [str(tools["disturbance_user_custom_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        py_bin_path.write_bytes(py_to_pdu_DisturbanceUserCustom(py_obj))
        subprocess.run(
            ["node", "--input-type=module", "-e", js_encode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        cpp_to_python = pdu_to_py_DisturbanceUserCustom(bytearray(cpp_bin_path.read_bytes()))
        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        py_generated = pdu_to_py_DisturbanceUserCustom(bytearray(py_bin_path.read_bytes()))
        js_generated_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        def decode_data(value):
            if isinstance(value, list):
                return value
            count = len(value) // 8
            return list(struct.unpack(f"<{count}d", bytes(value)))

        return {
            "expected": expected,
            "cpp_to_python": {"data": decode_data(cpp_to_python.data)},
            "cpp_to_javascript": json.loads(js_decode.stdout),
            "python_generated": {"data": decode_data(py_generated.data)},
            "javascript_generated": json.loads(js_generated_decode.stdout),
        }


def validate_simple_struct_varray_cpp_oracle_interop(repo_root: Path):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_SimpleStructVarray } from './pdu/javascript/hako_msgs/pdu_conv_SimpleStructVarray.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_SimpleStructVarray(arrayBuffer);
console.log(JSON.stringify({
  aaa: obj.aaa,
  fixed_str: obj.fixed_str,
  varray_str: obj.varray_str,
  fixed_array: obj.fixed_array.map(item => ({ data: item.data, fixed_array: item.fixed_array, p_mem1: item.p_mem1 })),
  data: obj.data.map(item => ({ data: item.data, fixed_array: item.fixed_array, p_mem1: item.p_mem1 }))
}));
"""
    js_encode_script = """
import fs from 'node:fs';
import { SimpleStructVarray } from './pdu/javascript/hako_msgs/pdu_jstype_SimpleStructVarray.js';
import { SimpleVarray } from './pdu/javascript/hako_msgs/pdu_jstype_SimpleVarray.js';
import { jsToPdu_SimpleStructVarray } from './pdu/javascript/hako_msgs/pdu_conv_SimpleStructVarray.js';

function makeSimpleVarray(data, fixedArray, pMem1) {
  const obj = new SimpleVarray();
  obj.data = data;
  obj.fixed_array = [...fixedArray, ...new Array(10 - fixedArray.length).fill(0)];
  obj.p_mem1 = pMem1;
  return obj;
}

const obj = new SimpleStructVarray();
obj.aaa = 7;
obj.fixed_str = ['alpha', 'beta'];
obj.varray_str = ['gamma', 'delta'];
obj.fixed_array = [
  makeSimpleVarray([1, 2], [3, 4], 5),
  makeSimpleVarray([6], [7, 8], 9),
  makeSimpleVarray([], [], 0),
  makeSimpleVarray([], [], 0),
  makeSimpleVarray([], [], 0),
];
obj.data = [
  makeSimpleVarray([10, 11], [12, 13], 14),
  makeSimpleVarray([15], [16, 17], 18),
];

fs.writeFileSync(process.argv[1], Buffer.from(jsToPdu_SimpleStructVarray(obj)));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_SimpleStructVarray import (
        pdu_to_py_SimpleStructVarray,
        py_to_pdu_SimpleStructVarray,
    )
    from pdu.python.hako_msgs.pdu_pytype_SimpleStructVarray import SimpleStructVarray
    from pdu.python.hako_msgs.pdu_pytype_SimpleVarray import SimpleVarray

    def make_simple_varray(data_values, fixed_values, p_mem1):
        obj = SimpleVarray()
        obj.data = list(data_values)
        obj.fixed_array = list(fixed_values) + [0] * (10 - len(fixed_values))
        obj.p_mem1 = p_mem1
        return obj

    def decode_simple_varray(item):
        data_value = item.data if isinstance(item.data, list) else list(bytes(item.data))
        fixed_value = item.fixed_array if isinstance(item.fixed_array, list) else list(bytes(item.fixed_array))
        return {
            "data": list(data_value),
            "fixed_array": list(fixed_value),
            "p_mem1": item.p_mem1,
        }

    expected = {
        "aaa": 7,
        "fixed_str": ["alpha", "beta"],
        "varray_str": ["gamma", "delta"],
        "fixed_array": [
            {"data": [1, 2], "fixed_array": [3, 4] + [0] * 8, "p_mem1": 5},
            {"data": [6], "fixed_array": [7, 8] + [0] * 8, "p_mem1": 9},
            {"data": [], "fixed_array": [0] * 10, "p_mem1": 0},
            {"data": [], "fixed_array": [0] * 10, "p_mem1": 0},
            {"data": [], "fixed_array": [0] * 10, "p_mem1": 0},
        ],
        "data": [
            {"data": [10, 11], "fixed_array": [12, 13] + [0] * 8, "p_mem1": 14},
            {"data": [15], "fixed_array": [16, 17] + [0] * 8, "p_mem1": 18},
        ],
    }

    py_obj = SimpleStructVarray()
    py_obj.aaa = expected["aaa"]
    py_obj.fixed_str = expected["fixed_str"].copy()
    py_obj.varray_str = expected["varray_str"].copy()
    py_obj.fixed_array = [
        make_simple_varray([1, 2], [3, 4], 5),
        make_simple_varray([6], [7, 8], 9),
        make_simple_varray([], [], 0),
        make_simple_varray([], [], 0),
        make_simple_varray([], [], 0),
    ]
    py_obj.data = [
        make_simple_varray([10, 11], [12, 13], 14),
        make_simple_varray([15], [16, 17], 18),
    ]

    tools = ensure_cpp_oracle_tools(repo_root)
    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "simple_struct_varray_cpp.bin"
        py_bin_path = tmpdir_path / "simple_struct_varray_py.bin"
        js_bin_path = tmpdir_path / "simple_struct_varray_js.bin"

        subprocess.run(
            [str(tools["simple_struct_varray_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        py_bin_path.write_bytes(py_to_pdu_SimpleStructVarray(py_obj))
        subprocess.run(
            ["node", "--input-type=module", "-e", js_encode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        cpp_to_python = pdu_to_py_SimpleStructVarray(bytearray(cpp_bin_path.read_bytes()))
        py_generated = pdu_to_py_SimpleStructVarray(bytearray(py_bin_path.read_bytes()))
        cpp_to_js = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        js_generated = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        def decode_struct(obj):
            return {
                "aaa": obj.aaa,
                "fixed_str": list(obj.fixed_str) if obj.fixed_str is not None else [],
                "varray_str": list(obj.varray_str) if isinstance(obj.varray_str, list) else [],
                "fixed_array": [decode_simple_varray(item) for item in obj.fixed_array],
                "data": [decode_simple_varray(item) for item in obj.data],
            }

        return {
            "expected": expected,
            "cpp_to_python": decode_struct(cpp_to_python),
            "cpp_to_javascript": json.loads(cpp_to_js.stdout),
            "python_generated": decode_struct(py_generated),
            "javascript_generated": json.loads(js_generated.stdout),
        }


def validate_simple_struct_varray_python_encode_size_case(repo_root: Path, varray_str_values, data_entries):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_SimpleStructVarray } from './pdu/javascript/hako_msgs/pdu_conv_SimpleStructVarray.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_SimpleStructVarray(arrayBuffer);
console.log(JSON.stringify({
  varray_str: obj.varray_str,
  data: obj.data.map(item => ({ data: item.data, fixed_array: item.fixed_array, p_mem1: item.p_mem1 }))
}));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.hako_msgs.pdu_conv_SimpleStructVarray import (
        pdu_to_py_SimpleStructVarray,
        py_to_pdu_SimpleStructVarray,
    )
    from pdu.python.hako_msgs.pdu_pytype_SimpleStructVarray import SimpleStructVarray
    from pdu.python.hako_msgs.pdu_pytype_SimpleVarray import SimpleVarray

    def make_simple_varray(spec):
        obj = SimpleVarray()
        obj.data = list(spec["data"])
        obj.fixed_array = list(spec["fixed_array"]) + [0] * (10 - len(spec["fixed_array"]))
        obj.p_mem1 = spec["p_mem1"]
        return obj

    def decode_simple_varray(item):
        data_value = item.data if isinstance(item.data, list) else list(bytes(item.data))
        fixed_value = item.fixed_array if isinstance(item.fixed_array, list) else list(bytes(item.fixed_array))
        return {
            "data": list(data_value),
            "fixed_array": list(fixed_value),
            "p_mem1": item.p_mem1,
        }

    py_obj = SimpleStructVarray()
    py_obj.aaa = 7
    py_obj.fixed_str = ["alpha", "beta"]
    py_obj.varray_str = list(varray_str_values)
    py_obj.fixed_array = [make_simple_varray({"data": [], "fixed_array": [], "p_mem1": 0}) for _ in range(5)]
    py_obj.data = [make_simple_varray(spec) for spec in data_entries]

    with tempfile.TemporaryDirectory() as tmpdir:
        py_bin_path = Path(tmpdir) / "simple_struct_varray_py.bin"
        py_bin_path.write_bytes(py_to_pdu_SimpleStructVarray(py_obj))

        restored = pdu_to_py_SimpleStructVarray(bytearray(py_bin_path.read_bytes()))
        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(py_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": {
                "varray_str": list(varray_str_values),
                "data": [
                    {
                        "data": list(spec["data"]),
                        "fixed_array": list(spec["fixed_array"]) + [0] * (10 - len(spec["fixed_array"])),
                        "p_mem1": spec["p_mem1"],
                    }
                    for spec in data_entries
                ],
            },
            "python_decoded": {
                "varray_str": list(restored.varray_str) if isinstance(restored.varray_str, list) else [],
                "data": [decode_simple_varray(item) for item in restored.data],
            },
            "javascript_decoded": json.loads(js_decode.stdout),
        }


def validate_joint_state_cpp_oracle_interop(repo_root: Path):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_JointState } from './pdu/javascript/sensor_msgs/pdu_conv_JointState.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_JointState(arrayBuffer);
console.log(JSON.stringify({
  frame_id: obj.header.frame_id,
  name: obj.name,
  position: obj.position,
  velocity: obj.velocity,
  effort: obj.effort
}));
"""
    js_encode_script = """
import fs from 'node:fs';
import { JointState } from './pdu/javascript/sensor_msgs/pdu_jstype_JointState.js';
import { Header } from './pdu/javascript/std_msgs/pdu_jstype_Header.js';
import { Time } from './pdu/javascript/builtin_interfaces/pdu_jstype_Time.js';
import { jsToPdu_JointState } from './pdu/javascript/sensor_msgs/pdu_conv_JointState.js';

const obj = new JointState();
obj.header = new Header();
obj.header.stamp = new Time();
obj.header.frame_id = 'frame';
obj.name = ['a', 'b'];
obj.position = [1.0, 2.0];
obj.velocity = [3.0];
obj.effort = [4.0];

fs.writeFileSync(process.argv[1], Buffer.from(jsToPdu_JointState(obj)));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.builtin_interfaces.pdu_pytype_Time import Time
    from pdu.python.sensor_msgs.pdu_conv_JointState import pdu_to_py_JointState, py_to_pdu_JointState
    from pdu.python.sensor_msgs.pdu_pytype_JointState import JointState
    from pdu.python.std_msgs.pdu_pytype_Header import Header

    tools = ensure_cpp_oracle_tools(repo_root)
    expected = {
        "frame_id": "frame",
        "name": ["a", "b"],
        "position": [1.0, 2.0],
        "velocity": [3.0],
        "effort": [4.0],
    }

    py_obj = JointState()
    py_obj.header = Header()
    py_obj.header.stamp = Time()
    py_obj.header.frame_id = "frame"
    py_obj.name = ["a", "b"]
    py_obj.position = [1.0, 2.0]
    py_obj.velocity = [3.0]
    py_obj.effort = [4.0]

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "joint_state_cpp.bin"
        py_bin_path = tmpdir_path / "joint_state_py.bin"
        js_bin_path = tmpdir_path / "joint_state_js.bin"

        subprocess.run(
            [str(tools["joint_state_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        py_bin_path.write_bytes(py_to_pdu_JointState(py_obj))
        subprocess.run(
            ["node", "--input-type=module", "-e", js_encode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        restored = pdu_to_py_JointState(bytearray(cpp_bin_path.read_bytes()))
        if isinstance(restored.name, list):
            restored_name = restored.name
        else:
            restored_name = []
            raw_name = bytes(restored.name)
            for index in range(0, len(raw_name), 128):
                chunk = raw_name[index:index + 128]
                restored_name.append(chunk.split(b"\0", 1)[0].decode("utf-8"))

        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        py_generated = pdu_to_py_JointState(bytearray(py_bin_path.read_bytes()))
        if isinstance(py_generated.name, list):
            py_generated_name = py_generated.name
        else:
            py_generated_name = []
            raw_name = bytes(py_generated.name)
            for index in range(0, len(raw_name), 128):
                chunk = raw_name[index:index + 128]
                py_generated_name.append(chunk.split(b"\0", 1)[0].decode("utf-8"))

        js_generated_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": expected,
            "cpp_to_python": {
                "frame_id": restored.header.frame_id,
                "name": restored_name,
                "position": restored.position if isinstance(restored.position, list) else list(struct.unpack(f"<{len(restored.position) // 8}d", bytes(restored.position))),
                "velocity": restored.velocity if isinstance(restored.velocity, list) else list(struct.unpack(f"<{len(restored.velocity) // 8}d", bytes(restored.velocity))),
                "effort": restored.effort if isinstance(restored.effort, list) else list(struct.unpack(f"<{len(restored.effort) // 8}d", bytes(restored.effort))),
            },
            "cpp_to_javascript": json.loads(js_decode.stdout),
            "python_generated": {
                "frame_id": py_generated.header.frame_id,
                "name": py_generated_name,
                "position": py_generated.position if isinstance(py_generated.position, list) else list(struct.unpack(f"<{len(py_generated.position) // 8}d", bytes(py_generated.position))),
                "velocity": py_generated.velocity if isinstance(py_generated.velocity, list) else list(struct.unpack(f"<{len(py_generated.velocity) // 8}d", bytes(py_generated.velocity))),
                "effort": py_generated.effort if isinstance(py_generated.effort, list) else list(struct.unpack(f"<{len(py_generated.effort) // 8}d", bytes(py_generated.effort))),
            },
            "javascript_generated": json.loads(js_generated_decode.stdout),
        }


def validate_point_cloud2_cpp_oracle_interop(repo_root: Path):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_PointCloud2 } from './pdu/javascript/sensor_msgs/pdu_conv_PointCloud2.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_PointCloud2(arrayBuffer);
console.log(JSON.stringify({
  header: {
    stamp: { sec: obj.header.stamp.sec, nanosec: obj.header.stamp.nanosec },
    frame_id: obj.header.frame_id
  },
  height: obj.height,
  width: obj.width,
  fields: obj.fields.map(item => ({ name: item.name, offset: item.offset, datatype: item.datatype, count: item.count })),
  is_bigendian: obj.is_bigendian,
  point_step: obj.point_step,
  row_step: obj.row_step,
  data: obj.data,
  is_dense: obj.is_dense
}));
"""
    js_encode_script = """
import fs from 'node:fs';
import { PointCloud2 } from './pdu/javascript/sensor_msgs/pdu_jstype_PointCloud2.js';
import { PointField } from './pdu/javascript/sensor_msgs/pdu_jstype_PointField.js';
import { jsToPdu_PointCloud2 } from './pdu/javascript/sensor_msgs/pdu_conv_PointCloud2.js';

const makePointField = (name, offset, datatype, count) => {
  const field = new PointField();
  field.name = name;
  field.offset = offset;
  field.datatype = datatype;
  field.count = count;
  return field;
};

const obj = new PointCloud2();
obj.header.stamp.sec = 1;
obj.header.stamp.nanosec = 200;
obj.header.frame_id = 'pc';
obj.height = 2;
obj.width = 3;
obj.fields = [
  makePointField('x', 0, 7, 1),
  makePointField('intensity', 4, 7, 1)
];
obj.is_bigendian = false;
obj.point_step = 8;
obj.row_step = 24;
obj.data = [1, 2, 3, 4, 5, 6];
obj.is_dense = true;

fs.writeFileSync(process.argv[1], Buffer.from(jsToPdu_PointCloud2(obj)));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.sensor_msgs.pdu_conv_PointCloud2 import pdu_to_py_PointCloud2, py_to_pdu_PointCloud2
    from pdu.python.sensor_msgs.pdu_pytype_PointCloud2 import PointCloud2
    from pdu.python.sensor_msgs.pdu_pytype_PointField import PointField

    def decode_field(item):
        return {
            "name": item.name,
            "offset": item.offset,
            "datatype": item.datatype,
            "count": item.count,
        }

    def decode_point_cloud(obj):
        data_value = obj.data if isinstance(obj.data, list) else list(bytes(obj.data))
        return {
            "header": {
                "stamp": {"sec": obj.header.stamp.sec, "nanosec": obj.header.stamp.nanosec},
                "frame_id": obj.header.frame_id,
            },
            "height": obj.height,
            "width": obj.width,
            "fields": [decode_field(item) for item in obj.fields],
            "is_bigendian": bool(obj.is_bigendian),
            "point_step": obj.point_step,
            "row_step": obj.row_step,
            "data": list(data_value),
            "is_dense": bool(obj.is_dense),
        }

    def make_point_field(name, offset, datatype, count):
        field = PointField()
        field.name = name
        field.offset = offset
        field.datatype = datatype
        field.count = count
        return field

    expected = {
        "header": {"stamp": {"sec": 1, "nanosec": 200}, "frame_id": "pc"},
        "height": 2,
        "width": 3,
        "fields": [
            {"name": "x", "offset": 0, "datatype": 7, "count": 1},
            {"name": "intensity", "offset": 4, "datatype": 7, "count": 1},
        ],
        "is_bigendian": False,
        "point_step": 8,
        "row_step": 24,
        "data": [1, 2, 3, 4, 5, 6],
        "is_dense": True,
    }

    py_obj = PointCloud2()
    py_obj.header.stamp.sec = 1
    py_obj.header.stamp.nanosec = 200
    py_obj.header.frame_id = "pc"
    py_obj.height = 2
    py_obj.width = 3
    py_obj.fields = [
        make_point_field("x", 0, 7, 1),
        make_point_field("intensity", 4, 7, 1),
    ]
    py_obj.is_bigendian = False
    py_obj.point_step = 8
    py_obj.row_step = 24
    py_obj.data = expected["data"].copy()
    py_obj.is_dense = True

    tools = ensure_cpp_oracle_tools(repo_root)
    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        cpp_bin_path = tmpdir_path / "point_cloud2_cpp.bin"
        py_bin_path = tmpdir_path / "point_cloud2_py.bin"
        js_bin_path = tmpdir_path / "point_cloud2_js.bin"

        subprocess.run(
            [str(tools["point_cloud2_dump"]), str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        py_bin_path.write_bytes(py_to_pdu_PointCloud2(py_obj))
        subprocess.run(
            ["node", "--input-type=module", "-e", js_encode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        cpp_to_python = pdu_to_py_PointCloud2(bytearray(cpp_bin_path.read_bytes()))
        py_generated = pdu_to_py_PointCloud2(bytearray(py_bin_path.read_bytes()))
        cpp_to_js = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(cpp_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )
        js_generated = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(js_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": expected,
            "cpp_to_python": decode_point_cloud(cpp_to_python),
            "cpp_to_javascript": json.loads(cpp_to_js.stdout),
            "python_generated": decode_point_cloud(py_generated),
            "javascript_generated": json.loads(js_generated.stdout),
        }


def validate_point_cloud2_python_encode_size_case(repo_root: Path, field_specs, data_values):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_PointCloud2 } from './pdu/javascript/sensor_msgs/pdu_conv_PointCloud2.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_PointCloud2(arrayBuffer);
console.log(JSON.stringify({
  fields: obj.fields.map(item => ({ name: item.name, offset: item.offset, datatype: item.datatype, count: item.count })),
  data: obj.data
}));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.sensor_msgs.pdu_conv_PointCloud2 import pdu_to_py_PointCloud2, py_to_pdu_PointCloud2
    from pdu.python.sensor_msgs.pdu_pytype_PointCloud2 import PointCloud2
    from pdu.python.sensor_msgs.pdu_pytype_PointField import PointField

    def make_point_field(spec):
        field = PointField()
        field.name = spec["name"]
        field.offset = spec["offset"]
        field.datatype = spec["datatype"]
        field.count = spec["count"]
        return field

    def decode_point_field(item):
        return {
            "name": item.name,
            "offset": item.offset,
            "datatype": item.datatype,
            "count": item.count,
        }

    py_obj = PointCloud2()
    py_obj.header.stamp.sec = 1
    py_obj.header.stamp.nanosec = 200
    py_obj.header.frame_id = "pc"
    py_obj.height = 2
    py_obj.width = 3
    py_obj.fields = [make_point_field(spec) for spec in field_specs]
    py_obj.is_bigendian = False
    py_obj.point_step = 8
    py_obj.row_step = 24
    py_obj.data = list(data_values)
    py_obj.is_dense = True

    expected = {
        "fields": [dict(spec) for spec in field_specs],
        "data": list(data_values),
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        py_bin_path = tmpdir_path / "point_cloud2_py.bin"

        py_bin_path.write_bytes(py_to_pdu_PointCloud2(py_obj))
        restored = pdu_to_py_PointCloud2(bytearray(py_bin_path.read_bytes()))
        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(py_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": expected,
            "python_decoded": {
                "fields": [decode_point_field(item) for item in restored.fields],
                "data": list(restored.data if isinstance(restored.data, list) else bytes(restored.data)),
            },
            "javascript_decoded": json.loads(js_decode.stdout),
        }


def validate_laser_scan_python_encode_size_case(repo_root: Path, ranges, intensities):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_LaserScan } from './pdu/javascript/sensor_msgs/pdu_conv_LaserScan.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_LaserScan(arrayBuffer);
console.log(JSON.stringify({
  ranges: obj.ranges,
  intensities: obj.intensities
}));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.sensor_msgs.pdu_conv_LaserScan import pdu_to_py_LaserScan, py_to_pdu_LaserScan
    from pdu.python.sensor_msgs.pdu_pytype_LaserScan import LaserScan

    def decode_float32_varray(value):
        if isinstance(value, list):
            return list(value)
        if len(value) == 0:
            return []
        return list(struct.unpack(f"<{len(value) // 4}f", bytes(value)))

    py_obj = LaserScan()
    py_obj.header.stamp.sec = 1
    py_obj.header.stamp.nanosec = 200
    py_obj.header.frame_id = "laser"
    py_obj.angle_min = -1.0
    py_obj.angle_max = 1.0
    py_obj.angle_increment = 0.5
    py_obj.time_increment = 0.1
    py_obj.scan_time = 0.2
    py_obj.range_min = 0.3
    py_obj.range_max = 30.0
    py_obj.ranges = list(ranges)
    py_obj.intensities = list(intensities)

    expected = {
        "ranges": list(ranges),
        "intensities": list(intensities),
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        py_bin_path = tmpdir_path / "laser_scan_py.bin"

        py_bin_path.write_bytes(py_to_pdu_LaserScan(py_obj))
        restored = pdu_to_py_LaserScan(bytearray(py_bin_path.read_bytes()))
        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(py_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": expected,
            "python_decoded": {
                "ranges": decode_float32_varray(restored.ranges),
                "intensities": decode_float32_varray(restored.intensities),
            },
            "javascript_decoded": json.loads(js_decode.stdout),
        }


def validate_camera_info_python_encode_size_case(repo_root: Path, d_values):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_CameraInfo } from './pdu/javascript/sensor_msgs/pdu_conv_CameraInfo.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_CameraInfo(arrayBuffer);
console.log(JSON.stringify({
  d: obj.d
}));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.sensor_msgs.pdu_conv_CameraInfo import pdu_to_py_CameraInfo, py_to_pdu_CameraInfo
    from pdu.python.sensor_msgs.pdu_pytype_CameraInfo import CameraInfo

    def decode_float64_varray(value):
        if isinstance(value, list):
            return list(value)
        if len(value) == 0:
            return []
        return list(struct.unpack(f"<{len(value) // 8}d", bytes(value)))

    py_obj = CameraInfo()
    py_obj.header.stamp.sec = 1
    py_obj.header.stamp.nanosec = 200
    py_obj.header.frame_id = "cam"
    py_obj.height = 480
    py_obj.width = 640
    py_obj.distortion_model = "plumb_bob"
    py_obj.d = list(d_values)
    py_obj.k = [1.0] * 9
    py_obj.r = [2.0] * 9
    py_obj.p = [3.0] * 12
    py_obj.binning_x = 1
    py_obj.binning_y = 2
    py_obj.roi.x_offset = 3
    py_obj.roi.y_offset = 4
    py_obj.roi.height = 5
    py_obj.roi.width = 6
    py_obj.roi.do_rectify = True

    expected = {
        "d": list(d_values),
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        py_bin_path = tmpdir_path / "camera_info_py.bin"

        py_bin_path.write_bytes(py_to_pdu_CameraInfo(py_obj))
        restored = pdu_to_py_CameraInfo(bytearray(py_bin_path.read_bytes()))
        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(py_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": expected,
            "python_decoded": {
                "d": decode_float64_varray(restored.d),
            },
            "javascript_decoded": json.loads(js_decode.stdout),
        }


def validate_multi_array_layout_python_encode_size_case(repo_root: Path, dim_specs):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_MultiArrayLayout } from './pdu/javascript/std_msgs/pdu_conv_MultiArrayLayout.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_MultiArrayLayout(arrayBuffer);
console.log(JSON.stringify({
  dim: obj.dim.map(item => ({ label: item.label, size: item.size, stride: item.stride })),
  data_offset: obj.data_offset
}));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.std_msgs.pdu_conv_MultiArrayLayout import pdu_to_py_MultiArrayLayout, py_to_pdu_MultiArrayLayout
    from pdu.python.std_msgs.pdu_pytype_MultiArrayDimension import MultiArrayDimension
    from pdu.python.std_msgs.pdu_pytype_MultiArrayLayout import MultiArrayLayout

    def make_dim(spec):
        dim = MultiArrayDimension()
        dim.label = spec["label"]
        dim.size = spec["size"]
        dim.stride = spec["stride"]
        return dim

    py_obj = MultiArrayLayout()
    py_obj.dim = [make_dim(spec) for spec in dim_specs]
    py_obj.data_offset = 9

    expected = {
        "dim": [dict(spec) for spec in dim_specs],
        "data_offset": 9,
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        py_bin_path = tmpdir_path / "multi_array_layout_py.bin"

        py_bin_path.write_bytes(py_to_pdu_MultiArrayLayout(py_obj))
        restored = pdu_to_py_MultiArrayLayout(bytearray(py_bin_path.read_bytes()))
        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(py_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": expected,
            "python_decoded": {
                "dim": [{"label": item.label, "size": item.size, "stride": item.stride} for item in restored.dim],
                "data_offset": restored.data_offset,
            },
            "javascript_decoded": json.loads(js_decode.stdout),
        }


def validate_float64_multi_array_python_encode_size_case(repo_root: Path, dim_specs, data_values):
    js_decode_script = """
import fs from 'node:fs';
import { pduToJs_Float64MultiArray } from './pdu/javascript/std_msgs/pdu_conv_Float64MultiArray.js';

const bin = fs.readFileSync(process.argv[1]);
const arrayBuffer = bin.buffer.slice(bin.byteOffset, bin.byteOffset + bin.byteLength);
const obj = pduToJs_Float64MultiArray(arrayBuffer);
console.log(JSON.stringify({
  layout: {
    dim: obj.layout.dim.map(item => ({ label: item.label, size: item.size, stride: item.stride })),
    data_offset: obj.layout.data_offset
  },
  data: obj.data
}));
"""

    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from pdu.python.std_msgs.pdu_conv_Float64MultiArray import pdu_to_py_Float64MultiArray, py_to_pdu_Float64MultiArray
    from pdu.python.std_msgs.pdu_pytype_Float64MultiArray import Float64MultiArray
    from pdu.python.std_msgs.pdu_pytype_MultiArrayDimension import MultiArrayDimension

    def make_dim(spec):
        dim = MultiArrayDimension()
        dim.label = spec["label"]
        dim.size = spec["size"]
        dim.stride = spec["stride"]
        return dim

    def decode_float64_varray(value):
        if isinstance(value, list):
            return list(value)
        if len(value) == 0:
            return []
        return list(struct.unpack(f"<{len(value) // 8}d", bytes(value)))

    py_obj = Float64MultiArray()
    py_obj.layout.dim = [make_dim(spec) for spec in dim_specs]
    py_obj.layout.data_offset = 9
    py_obj.data = list(data_values)

    expected = {
        "layout": {
            "dim": [dict(spec) for spec in dim_specs],
            "data_offset": 9,
        },
        "data": list(data_values),
    }

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir_path = Path(tmpdir)
        py_bin_path = tmpdir_path / "float64_multi_array_py.bin"

        py_bin_path.write_bytes(py_to_pdu_Float64MultiArray(py_obj))
        restored = pdu_to_py_Float64MultiArray(bytearray(py_bin_path.read_bytes()))
        js_decode = subprocess.run(
            ["node", "--input-type=module", "-e", js_decode_script, str(py_bin_path)],
            cwd=repo_root,
            check=True,
            capture_output=True,
            text=True,
        )

        return {
            "expected": expected,
            "python_decoded": {
                "layout": {
                    "dim": [{"label": item.label, "size": item.size, "stride": item.stride} for item in restored.layout.dim],
                    "data_offset": restored.layout.data_offset,
                },
                "data": decode_float64_varray(restored.data),
            },
            "javascript_decoded": json.loads(js_decode.stdout),
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

    js_dict_result = validate_javascript_from_dict_roundtrip(repo_root)
    if js_dict_result["game_axis"] != js_dict_result["expected_game_axis"]:
        failures.append("javascript fromDict does not preserve primitive arrays")
    if js_dict_result["game_buttons"] != js_dict_result["expected_game_buttons"]:
        failures.append("javascript fromDict does not preserve bool arrays")
    if js_dict_result["game_json_axis"] != js_dict_result["expected_game_axis"]:
        failures.append("javascript fromJSON does not preserve primitive arrays")
    if js_dict_result["game_json_buttons"] != js_dict_result["expected_game_buttons"]:
        failures.append("javascript fromJSON does not preserve bool arrays")
    if js_dict_result["fixed_str"] != js_dict_result["expected_fixed_str"]:
        failures.append("javascript fromDict does not preserve string arrays")
    if js_dict_result["varray_str"] != js_dict_result["expected_varray_str"]:
        failures.append("javascript fromDict does not preserve varray string arrays")
    if js_dict_result["fixed_array_data0"] != js_dict_result["expected_fixed_array_data0"]:
        failures.append("javascript fromDict does not preserve struct arrays")
    if js_dict_result["data_array0"] != js_dict_result["expected_data_array0"]:
        failures.append("javascript fromDict does not preserve varray struct arrays")
    if js_dict_result["fixed_str_json"] != js_dict_result["expected_fixed_str"]:
        failures.append("javascript fromJSON does not preserve string arrays")
    if js_dict_result["varray_str_json"] != js_dict_result["expected_varray_str"]:
        failures.append("javascript fromJSON does not preserve varray string arrays")
    if js_dict_result["fixed_array_data0_json"] != js_dict_result["expected_fixed_array_data0"]:
        failures.append("javascript fromJSON does not preserve struct arrays")
    if js_dict_result["data_array0_json"] != js_dict_result["expected_data_array0"]:
        failures.append("javascript fromJSON does not preserve varray struct arrays")

    disturbance_interop = validate_disturbance_js_python_interop(repo_root)
    if disturbance_interop["py_to_js"] != disturbance_interop["expected"]:
        failures.append("python -> javascript disturbance interop does not preserve nested varray data")
    if disturbance_interop["js_to_py"] != disturbance_interop["expected"]:
        failures.append("javascript -> python disturbance interop does not preserve nested varray data")
    if not disturbance_interop["binaries_equal"]:
        failures.append("python and javascript disturbance binaries do not match")

    joint_state_interop = validate_joint_state_string_varray_interop(repo_root)
    if joint_state_interop["py_to_js"] != joint_state_interop["expected"]:
        failures.append("python -> javascript joint_state interop does not preserve string varray data")
    if joint_state_interop["js_to_py"] != joint_state_interop["expected"]:
        failures.append("javascript -> python joint_state interop does not preserve string varray data")
    if not joint_state_interop["binaries_equal"]:
        failures.append("python and javascript joint_state binaries do not match")

    if failures:
        for failure in failures:
            print(f"FAIL: {failure}", file=sys.stderr)
        return 1

    print("OK: generated artifact validation passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
