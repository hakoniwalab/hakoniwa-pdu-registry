#!/usr/bin/env python3
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from generators.generate_hako_pdu_msgs.ros_message_parser import parse_ros_message_file


ROOT = Path(__file__).resolve().parents[1]


class ZeroFieldMessagesTest(unittest.TestCase):
    def test_zero_field_message_uses_reserved_octet(self):
        with tempfile.TemporaryDirectory() as tmp:
            msg_file = Path(tmp) / "Empty.msg"
            msg_file.write_text("# no data fields\n", encoding="utf-8")

            self.assertEqual(
                parse_ros_message_file(msg_file),
                [{"type": "uint8", "name": "hako_dummy"}],
            )

    def test_non_empty_message_is_unchanged(self):
        with tempfile.TemporaryDirectory() as tmp:
            msg_file = Path(tmp) / "Value.msg"
            msg_file.write_text("uint32 value\n", encoding="utf-8")

            self.assertEqual(
                parse_ros_message_file(msg_file),
                [{"type": "uint32", "name": "value"}],
            )

    def test_zero_field_service_is_accepted(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            srv_dir = root / "std_srvs"
            srv_dir.mkdir()
            srv_file = srv_dir / "Empty.srv"
            srv_file.write_text("---\n", encoding="utf-8")
            output = root / "out"

            subprocess.run(
                [
                    sys.executable,
                    "-m",
                    "generators.generate_hako_service_msgs.main",
                    str(srv_file),
                    "--out",
                    str(output),
                ],
                cwd=ROOT,
                check=True,
            )

            msg_dir = output / "std_srvs_msgs" / "msg"
            request = msg_dir / "EmptyRequest.msg"
            response = msg_dir / "EmptyResponse.msg"
            self.assertEqual(request.read_text(encoding="utf-8"), "")
            self.assertEqual(response.read_text(encoding="utf-8"), "")

            # The common PDU parser maps these empty generated messages onto the
            # same one-octet representation as a native zero-field ROS message.
            self.assertEqual(
                parse_ros_message_file(request),
                [{"type": "uint8", "name": "hako_dummy"}],
            )
            self.assertEqual(
                parse_ros_message_file(response),
                [{"type": "uint8", "name": "hako_dummy"}],
            )


if __name__ == "__main__":
    unittest.main()
