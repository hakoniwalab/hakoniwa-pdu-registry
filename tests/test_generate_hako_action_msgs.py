#!/usr/bin/env python3
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


class GenerateHakoActionMsgsTest(unittest.TestCase):
    def test_generates_six_messages(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            action_dir = root / "sample"
            action_dir.mkdir()
            action_file = action_dir / "Fibonacci.action"
            action_file.write_text(
                "int32 order\n"
                "---\n"
                "int32[] sequence\n"
                "---\n"
                "int32[] partial_sequence\n",
                encoding="utf-8",
            )
            output = root / "out"
            subprocess.run(
                [
                    sys.executable,
                    "-m",
                    "generators.generate_hako_action_msgs.main",
                    str(action_file),
                    "--out",
                    str(output),
                ],
                cwd=ROOT,
                check=True,
            )

            msg_dir = output / "sample_action_msgs" / "msg"
            expected = {
                "FibonacciGoal.msg": "int32 order\n",
                "FibonacciResult.msg": "int32[] sequence\n",
                "FibonacciFeedback.msg": "int32[] partial_sequence\n",
                "FibonacciActionRequest.msg": (
                    "hako_action_msgs/ActionRequestHeader header\n"
                    "FibonacciGoal body\n"
                ),
                "FibonacciActionResponse.msg": (
                    "hako_action_msgs/ActionResponseHeader header\n"
                    "FibonacciResult body\n"
                ),
                "FibonacciActionFeedback.msg": (
                    "hako_action_msgs/ActionFeedbackHeader header\n"
                    "FibonacciFeedback body\n"
                ),
            }
            self.assertEqual({path.name for path in msg_dir.glob("*.msg")}, set(expected))
            for filename, content in expected.items():
                self.assertEqual((msg_dir / filename).read_text(encoding="utf-8"), content)

    def test_requires_exactly_three_sections(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            action_dir = root / "example_actions"
            action_dir.mkdir()
            action_file = action_dir / "Broken.action"
            action_file.write_text("int32 value\n---\nint32 result\n", encoding="utf-8")
            result = subprocess.run(
                [
                    sys.executable,
                    "-m",
                    "generators.generate_hako_action_msgs.main",
                    str(action_file),
                    "--out",
                    str(root / "out"),
                ],
                cwd=ROOT,
                capture_output=True,
                text=True,
            )
            self.assertNotEqual(result.returncode, 0)
            self.assertIn("exactly two '---' separators", result.stderr)


if __name__ == "__main__":
    unittest.main()
