#!/usr/bin/env python3
from __future__ import annotations

import importlib.util
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest import mock


TOOL_PATH = Path(__file__).resolve().parents[1] / "tools" / "generate_from_sources.py"
sys.path.insert(0, str(TOOL_PATH.parent))
SPEC = importlib.util.spec_from_file_location("generate_from_sources", TOOL_PATH)
assert SPEC is not None and SPEC.loader is not None
generate_tool = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(generate_tool)


class GenerateFromSourcesTest(unittest.TestCase):
    def test_rejects_invalid_or_escaping_inputs(self) -> None:
        with self.assertRaisesRegex(generate_tool.GenerateError, "package/Message"):
            generate_tool.validate_messages(["../Drive"])
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary).resolve()
            with self.assertRaisesRegex(generate_tool.GenerateError, "inside"):
                generate_tool.validate_output_dir(root, Path("../outside"))

    def test_generates_only_selected_list_without_editing_global_list(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            repo = Path(temporary).resolve()
            (repo / "config").mkdir()
            (repo / "docker").mkdir()
            global_list = repo / "config" / "ros_msgs.txt"
            global_list.write_text("many_msgs/Existing\n", encoding="utf-8")
            (repo / "config" / "search_path.txt").write_text(
                "/opt/ros/${ROS_DISTRO}/share\n"
                "/root/workspace/hakoniwa-pdu-registry/idl\n",
                encoding="utf-8",
            )
            source = repo / "source.yaml"
            source.write_text("fixture", encoding="utf-8")
            observed: dict[str, object] = {}

            def inspect_command(command, **kwargs):
                observed["command"] = command
                message_path = Path(
                    str(command[5]).replace(str(generate_tool.CONTAINER_ROOT), str(repo), 1)
                )
                search_path = Path(
                    str(command[7]).replace(str(generate_tool.CONTAINER_ROOT), str(repo), 1)
                )
                observed["messages"] = message_path.read_text(encoding="utf-8")
                observed["search"] = search_path.read_text(encoding="utf-8")
                return SimpleNamespace(returncode=0)

            manifest = SimpleNamespace(packages=("ackermann_msgs",))
            with (
                mock.patch.object(generate_tool, "load_source_manifest", return_value=manifest),
                mock.patch.object(generate_tool, "fetch_sources") as fetch,
                mock.patch.object(generate_tool.subprocess, "run", side_effect=inspect_command),
            ):
                generate_tool.run_generation(
                    repo_root=repo,
                    source_files=[source],
                    messages=[
                        "ackermann_msgs/AckermannDriveStamped",
                        "ackermann_msgs/AckermannDriveStamped",
                    ],
                    output_dir=Path("pdu"),
                )

            fetch.assert_called_once_with(
                sources=source.resolve(), output=repo / "output_msgs", clean=True
            )
            self.assertEqual(
                observed["messages"], "ackermann_msgs/AckermannDriveStamped\n"
            )
            self.assertIn(
                "/root/workspace/hakoniwa-pdu-registry/output_msgs\n",
                observed["search"],
            )
            command = observed["command"]
            self.assertIn("--incremental", command)
            self.assertNotIn("--cdr", command)
            self.assertEqual(global_list.read_text(encoding="utf-8"), "many_msgs/Existing\n")

    def test_selected_package_must_be_declared_by_source(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            repo = Path(temporary).resolve()
            source = repo / "source.yaml"
            source.write_text("fixture", encoding="utf-8")
            manifest = SimpleNamespace(packages=("other_msgs",))
            with (
                mock.patch.object(generate_tool, "load_source_manifest", return_value=manifest),
                mock.patch.object(generate_tool, "fetch_sources"),
            ):
                with self.assertRaisesRegex(generate_tool.GenerateError, "not declared"):
                    generate_tool.run_generation(
                        repo_root=repo,
                        source_files=[source],
                        messages=["ackermann_msgs/AckermannDrive"],
                        output_dir=Path("pdu"),
                    )


if __name__ == "__main__":
    unittest.main()
