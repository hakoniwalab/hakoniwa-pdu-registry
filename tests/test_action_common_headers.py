#!/usr/bin/env python3
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
MSG_DIR = ROOT / "idl" / "hako_action_msgs" / "msg"


class ActionCommonHeaderTest(unittest.TestCase):
    def test_request_header_contract(self) -> None:
        self.assertEqual(
            (MSG_DIR / "ActionRequestHeader.msg").read_text(encoding="utf-8"),
            "uint8 version\n"
            "uint8 request_kind\n"
            "uint8[2] reserved\n"
            "uint8[16] goal_id\n",
        )

    def test_response_header_contract(self) -> None:
        self.assertEqual(
            (MSG_DIR / "ActionResponseHeader.msg").read_text(encoding="utf-8"),
            "uint8 version\n"
            "uint8 response_kind\n"
            "uint8 status\n"
            "uint8 reserved\n"
            "uint8[16] goal_id\n",
        )

    def test_feedback_header_contract(self) -> None:
        self.assertEqual(
            (MSG_DIR / "ActionFeedbackHeader.msg").read_text(encoding="utf-8"),
            "uint8 version\n"
            "uint8[3] reserved\n"
            "uint8[16] goal_id\n"
            "uint32 sequence_no\n",
        )

    def test_headers_do_not_embed_ros_constants(self) -> None:
        for path in MSG_DIR.glob("Action*Header.msg"):
            for line in path.read_text(encoding="utf-8").splitlines():
                self.assertNotIn("=", line, f"PDU IDL constants are unsupported: {path}")

    def test_generation_input_lists_all_headers(self) -> None:
        entries = (ROOT / "config" / "action_header_msgs.txt").read_text(
            encoding="utf-8"
        ).splitlines()
        self.assertEqual(
            entries,
            [
                "hako_action_msgs/ActionRequestHeader",
                "hako_action_msgs/ActionResponseHeader",
                "hako_action_msgs/ActionFeedbackHeader",
            ],
        )


if __name__ == "__main__":
    unittest.main()
