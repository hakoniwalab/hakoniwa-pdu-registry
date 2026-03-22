import os
import subprocess
import tempfile
import textwrap
import unittest
from pathlib import Path


class GodotCppBridgeTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.repo_root = Path(__file__).resolve().parents[1]
        cls.godot_bin = Path(
            os.environ.get(
                "HAKO_GODOT_BIN",
                "/Applications/Godot_mono.app/Contents/MacOS/Godot",
            )
        )
        cls.godot_cpp_root = Path(
            os.environ.get(
                "HAKO_GODOT_CPP_ROOT",
                "/Users/tmori/project/oss/godot-cpp",
            )
        )
        cls.bridge_dir = cls.repo_root / "tests" / "godot_cpp_smoke"

    def test_generated_godot_cpp_converter_roundtrip(self):
        if not self.godot_bin.exists():
            self.skipTest(f"Godot executable not found: {self.godot_bin}")
        if not self.godot_cpp_root.exists():
            self.skipTest(f"godot-cpp root not found: {self.godot_cpp_root}")

        subprocess.run(
            [
                "cmake",
                "-S",
                str(self.bridge_dir),
                "-B",
                str(self.bridge_dir / "build"),
            ],
            cwd=self.repo_root,
            env={**os.environ, "HAKO_GODOT_CPP_ROOT": str(self.godot_cpp_root)},
            check=True,
            capture_output=True,
            text=True,
        )
        subprocess.run(
            [
                "cmake",
                "--build",
                str(self.bridge_dir / "build"),
                "-j4",
            ],
            cwd=self.repo_root,
            env={**os.environ, "HAKO_GODOT_CPP_ROOT": str(self.godot_cpp_root)},
            check=True,
            capture_output=True,
            text=True,
        )

        with tempfile.TemporaryDirectory() as tmpdir:
            project_dir = Path(tmpdir)
            (project_dir / "project.godot").write_text(
                'config_version=5\n\n[application]\nconfig/name="hakoniwa-pdu-godot-cpp-bridge-test"\n'
            )
            (project_dir / "hako_pdu_godot_smoke.gdextension").write_text(
                (self.bridge_dir / "hako_pdu_godot_smoke.gdextension").read_text()
            )
            (project_dir / "bin").mkdir()
            dylib_src = self.bridge_dir / "bin" / "libhako_pdu_godot_smoke.dylib"
            dylib_dst = project_dir / "bin" / "libhako_pdu_godot_smoke.dylib"
            dylib_dst.write_bytes(dylib_src.read_bytes())

            (project_dir / "run_bridge.gd").write_text(
                textwrap.dedent(
                    """
                    extends SceneTree

                    func fail(message: String) -> void:
                        push_error(message)
                        quit(1)

                    func expect_equal(actual, expected, label: String) -> void:
                        if actual != expected:
                            fail("%s: expected=%s actual=%s" % [label, str(expected), str(actual)])

                    func _init() -> void:
                        var extension_resource = load("res://hako_pdu_godot_smoke.gdextension")
                        if extension_resource == null:
                            fail("failed to load gdextension")

                        var bridge = ClassDB.instantiate("HakoPduGodotSmokeBridge")
                        if bridge == null:
                            fail("failed to instantiate bridge")

                        var disturbance_input := {
                            "data": PackedFloat64Array([1.25, 2.5])
                        }
                        var disturbance_binary = bridge.godot_to_pdu_disturbance_user_custom(disturbance_input)
                        var disturbance_restored = bridge.pdu_to_godot_disturbance_user_custom(disturbance_binary)
                        expect_equal(Array(disturbance_restored["data"]), [1.25, 2.5], "disturbance_user_custom.data")

                        var joint_input := {
                            "header": {"stamp": {"sec": 12, "nanosec": 34}, "frame_id": "base_link"},
                            "name": ["joint1", "joint2"],
                            "position": PackedFloat64Array([0.1, 0.2]),
                            "velocity": PackedFloat64Array([1.5]),
                            "effort": PackedFloat64Array()
                        }
                        var joint_binary = bridge.godot_to_pdu_joint_state(joint_input)
                        var joint_restored = bridge.pdu_to_godot_joint_state(joint_binary)
                        expect_equal(joint_restored["header"]["frame_id"], "base_link", "joint.header.frame_id")
                        expect_equal(Array(joint_restored["name"]), ["joint1", "joint2"], "joint.name")
                        expect_equal(Array(joint_restored["position"]), [0.1, 0.2], "joint.position")
                        expect_equal(Array(joint_restored["velocity"]), [1.5], "joint.velocity")
                        expect_equal(Array(joint_restored["effort"]), [], "joint.effort")

                        var simple_input := {
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
                        var simple_binary = bridge.godot_to_pdu_simple_struct_varray(simple_input)
                        var simple_restored = bridge.pdu_to_godot_simple_struct_varray(simple_binary)
                        expect_equal(simple_restored["aaa"], 7, "simple.aaa")
                        expect_equal(Array(simple_restored["fixed_str"]), ["alpha", "beta"], "simple.fixed_str")
                        expect_equal(Array(simple_restored["varray_str"]), ["x", "y", "z"], "simple.varray_str")
                        expect_equal(Array(simple_restored["fixed_array"][0]["data"]), [1, 2], "simple.fixed_array[0].data")
                        expect_equal(Array(simple_restored["data"][0]["fixed_array"]), [10, 11], "simple.data[0].fixed_array")

                        print("GODOT_CPP_BRIDGE_OK")
                        quit(0)
                    """
                ).lstrip()
            )

            try:
                completed = subprocess.run(
                    [
                        str(self.godot_bin),
                        "--headless",
                        "--path",
                        str(project_dir),
                        "--script",
                        "res://run_bridge.gd",
                    ],
                    cwd=self.repo_root,
                    env={**os.environ, "HOME": str(project_dir)},
                    capture_output=True,
                    text=True,
                    check=False,
                    timeout=30,
                )
            except subprocess.TimeoutExpired as exc:
                self.fail(
                    "Godot C++ bridge roundtrip timed out\n"
                    f"stdout:\n{exc.stdout}\n"
                    f"stderr:\n{exc.stderr}"
                )

            if completed.returncode != 0:
                self.fail(
                    "Godot C++ bridge roundtrip failed\n"
                    f"stdout:\n{completed.stdout}\n"
                    f"stderr:\n{completed.stderr}"
                )

            self.assertIn("GODOT_CPP_BRIDGE_OK", completed.stdout + completed.stderr)


if __name__ == "__main__":
    unittest.main()
