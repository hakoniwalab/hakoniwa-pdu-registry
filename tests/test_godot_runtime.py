import shutil
import subprocess
import tempfile
import textwrap
import unittest
import os
from pathlib import Path

from generators.generate_hako_pdu_msgs.code_generator import CodeGenerator


class GodotRuntimeTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.repo_root = Path(__file__).resolve().parents[1]
        cls.godot_bin = Path(
            os.environ.get(
                "HAKO_GODOT_BIN",
                "/Applications/Godot_mono.app/Contents/MacOS/Godot",
            )
        )
        cls.template_dir = cls.repo_root / "template"

    def make_message_def(self, package, message, fields):
        return {
            "package": package,
            "message": message,
            "fields": fields,
        }

    def test_generated_gdscript_roundtrip_in_headless_godot(self):
        if not self.godot_bin.exists():
            self.skipTest(f"Godot executable not found: {self.godot_bin}")

        with tempfile.TemporaryDirectory() as tmpdir:
            project_dir = Path(tmpdir)
            generator = CodeGenerator(self.template_dir)
            message_cache = {
                "builtin_interfaces/Time": self.make_message_def(
                    "builtin_interfaces",
                    "Time",
                    [
                        {"name": "sec", "type": "int32"},
                        {"name": "nanosec", "type": "uint32"},
                    ],
                ),
                "std_msgs/Header": self.make_message_def(
                    "std_msgs",
                    "Header",
                    [
                        {"name": "stamp", "type": "builtin_interfaces/Time"},
                        {"name": "frame_id", "type": "string"},
                    ],
                ),
                "geometry_msgs/Point": self.make_message_def(
                    "geometry_msgs",
                    "Point",
                    [
                        {"name": "x", "type": "float64"},
                        {"name": "y", "type": "float64"},
                        {"name": "z", "type": "float64"},
                    ],
                ),
                "geometry_msgs/Vector3": self.make_message_def(
                    "geometry_msgs",
                    "Vector3",
                    [
                        {"name": "x", "type": "float64"},
                        {"name": "y", "type": "float64"},
                        {"name": "z", "type": "float64"},
                    ],
                ),
                "hako_msgs/DisturbanceTemperature": self.make_message_def(
                    "hako_msgs",
                    "DisturbanceTemperature",
                    [{"name": "value", "type": "float64"}],
                ),
                "hako_msgs/DisturbanceWind": self.make_message_def(
                    "hako_msgs",
                    "DisturbanceWind",
                    [{"name": "value", "type": "geometry_msgs/Vector3"}],
                ),
                "hako_msgs/DisturbanceAtm": self.make_message_def(
                    "hako_msgs",
                    "DisturbanceAtm",
                    [{"name": "sea_level_atm", "type": "float64"}],
                ),
                "hako_msgs/DisturbanceBoundary": self.make_message_def(
                    "hako_msgs",
                    "DisturbanceBoundary",
                    [
                        {"name": "boundary_point", "type": "geometry_msgs/Point"},
                        {"name": "boundary_normal", "type": "geometry_msgs/Vector3"},
                    ],
                ),
                "hako_msgs/DisturbanceUserCustom": self.make_message_def(
                    "hako_msgs",
                    "DisturbanceUserCustom",
                    [{"name": "data", "type": "float64[]"}],
                ),
                "hako_msgs/Disturbance": self.make_message_def(
                    "hako_msgs",
                    "Disturbance",
                    [
                        {"name": "d_temp", "type": "hako_msgs/DisturbanceTemperature"},
                        {"name": "d_wind", "type": "hako_msgs/DisturbanceWind"},
                        {"name": "d_atm", "type": "hako_msgs/DisturbanceAtm"},
                        {"name": "d_boundary", "type": "hako_msgs/DisturbanceBoundary"},
                        {"name": "d_user_custom", "type": "hako_msgs/DisturbanceUserCustom[]"},
                    ],
                ),
                "hako_msgs/SimpleVarray": self.make_message_def(
                    "hako_msgs",
                    "SimpleVarray",
                    [
                        {"name": "data", "type": "int32[]"},
                        {"name": "fixed_array", "type": "int32[2]"},
                        {"name": "p_mem1", "type": "int32"},
                    ],
                ),
                "hako_msgs/SimpleStructVarray": self.make_message_def(
                    "hako_msgs",
                    "SimpleStructVarray",
                    [
                        {"name": "aaa", "type": "int32"},
                        {"name": "fixed_str", "type": "string[2]"},
                        {"name": "varray_str", "type": "string[]"},
                        {"name": "fixed_array", "type": "hako_msgs/SimpleVarray[5]"},
                        {"name": "data", "type": "hako_msgs/SimpleVarray[]"},
                    ],
                ),
                "sensor_msgs/JointState": self.make_message_def(
                    "sensor_msgs",
                    "JointState",
                    [
                        {"name": "header", "type": "std_msgs/Header"},
                        {"name": "name", "type": "string[]"},
                        {"name": "position", "type": "float64[]"},
                        {"name": "velocity", "type": "float64[]"},
                        {"name": "effort", "type": "float64[]"},
                    ],
                ),
            }
            generator.generate_all(message_cache, {}, project_dir)
            shutil.rmtree(project_dir / "types")
            shutil.rmtree(project_dir / "python")
            shutil.rmtree(project_dir / "javascript")
            shutil.rmtree(project_dir / "csharp")
            shutil.rmtree(project_dir / "csharp_v2")
            shutil.rmtree(project_dir / "godot_cpp_runtime")

            (project_dir / "project.godot").write_text(
                textwrap.dedent(
                    """
                    config_version=5

                    [application]
                    config/name="hakoniwa-pdu-registry-godot-test"
                    """
                ).lstrip()
            )

            (project_dir / "run_roundtrip.gd").write_text(
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
                            "header": {
                                "stamp": {"sec": 12, "nanosec": 34},
                                "frame_id": "base_link"
                            },
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
                        print("GODOT_ROUNDTRIP_OK")
                        quit(0)
                    """
                ).lstrip()
            )

            completed = subprocess.run(
                [
                    str(self.godot_bin),
                    "--headless",
                    "--path",
                    str(project_dir),
                    "--script",
                    "res://run_roundtrip.gd",
                ],
                cwd=self.repo_root,
                env={**os.environ, "HOME": str(project_dir)},
                capture_output=True,
                text=True,
                check=False,
            )

            if completed.returncode != 0:
                self.fail(
                    "Godot headless roundtrip failed\n"
                    f"stdout:\n{completed.stdout}\n"
                    f"stderr:\n{completed.stderr}"
                )

            self.assertIn("GODOT_ROUNDTRIP_OK", completed.stdout + completed.stderr)


if __name__ == "__main__":
    unittest.main()
