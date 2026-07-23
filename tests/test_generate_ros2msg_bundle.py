#!/usr/bin/env python3
from __future__ import annotations

import importlib.util
import tempfile
import unittest
from pathlib import Path


TOOL_PATH = Path(__file__).resolve().parents[1] / "tools" / "generate_ros2msg_bundle.py"
SPEC = importlib.util.spec_from_file_location("generate_ros2msg_bundle", TOOL_PATH)
assert SPEC is not None and SPEC.loader is not None
bundle_tool = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(bundle_tool)


class Ros2MsgBundleTest(unittest.TestCase):
    def write_msg(self, root: Path, package: str, message: str, text: str) -> None:
        path = root / package / "msg" / f"{message}.msg"
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    def test_joint_state_resolves_transitive_dependencies(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            self.write_msg(
                root,
                "sensor_msgs",
                "JointState",
                "std_msgs/Header header\n"
                "string[] name\n"
                "float64[] position\n"
                "float64[] velocity\n"
                "float64[] effort\n",
            )
            self.write_msg(
                root,
                "std_msgs",
                "Header",
                "builtin_interfaces/Time stamp\nstring frame_id\n",
            )
            self.write_msg(
                root,
                "builtin_interfaces",
                "Time",
                "int32 sec\nuint32 nanosec\n",
            )

            top, deps = bundle_tool.resolve_bundle("sensor_msgs/JointState", [root])
            rendered = bundle_tool.render_bundle(top, deps)

            self.assertEqual(
                [name for name, _ in deps],
                ["std_msgs/msg/Header", "builtin_interfaces/msg/Time"],
            )
            self.assertTrue(rendered.startswith("std_msgs/Header header\n"))
            self.assertIn(
                f"{bundle_tool.SEPARATOR}\nMSG: std_msgs/Header\n",
                rendered,
            )
            self.assertIn(
                f"{bundle_tool.SEPARATOR}\nMSG: builtin_interfaces/Time\n",
                rendered,
            )
            self.assertNotIn("MSG: std_msgs/msg/Header", rendered)

    def test_same_package_bounded_types_and_arrays(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            self.write_msg(
                root,
                "demo_msgs",
                "Outer",
                "string<=32 label\nInner[<=4] items\nuint8[16] digest\n",
            )
            self.write_msg(root, "demo_msgs", "Inner", "float64 value\n")

            _, deps = bundle_tool.resolve_bundle("demo_msgs/msg/Outer", [root])
            rendered = bundle_tool.render_bundle("Inner[<=4] items\n", deps)

            self.assertEqual([name for name, _ in deps], ["demo_msgs/msg/Inner"])
            self.assertIn("MSG: demo_msgs/Inner\n", rendered)

    def test_missing_dependency_fails_instead_of_emitting_partial_bundle(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            self.write_msg(root, "demo_msgs", "Outer", "missing_msgs/Missing value\n")

            with self.assertRaises(bundle_tool.BundleError):
                bundle_tool.resolve_bundle("demo_msgs/Outer", [root])


if __name__ == "__main__":
    unittest.main()
