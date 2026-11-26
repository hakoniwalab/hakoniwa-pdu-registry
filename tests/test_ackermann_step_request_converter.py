import unittest

from pdu.python.hako_srv_msgs.pdu_conv_AckermannStepRequestPacket import (
    pdu_to_py_AckermannStepRequestPacket,
    py_to_pdu_AckermannStepRequestPacket,
)
from pdu.python.hako_srv_msgs.pdu_pytype_AckermannStepRequestPacket import (
    AckermannStepRequestPacket,
)


class AckermannStepRequestConverterTest(unittest.TestCase):
    def test_packet_roundtrip_preserves_tire_friction_and_existing_fields(self):
        for tire_friction in (0.5, 0.0):
            with self.subTest(tire_friction=tire_friction):
                src = AckermannStepRequestPacket()
                src.header.request_id = 17
                src.header.service_name = "ackermann_step"
                src.header.client_name = "test_client"
                src.header.opcode = 3
                src.header.status_poll_interval_msec = 20
                src.body.step = 42
                src.body.drive.steering_angle = 0.1
                src.body.drive.steering_angle_velocity = 0.2
                src.body.drive.speed = 3.0
                src.body.drive.acceleration = 0.4
                src.body.drive.jerk = 0.5
                src.body.tire_friction = tire_friction

                restored = pdu_to_py_AckermannStepRequestPacket(
                    py_to_pdu_AckermannStepRequestPacket(src)
                )

                self.assertEqual(restored.header.to_dict(), src.header.to_dict())
                self.assertEqual(restored.body.step, src.body.step)
                self.assertAlmostEqual(restored.body.drive.steering_angle, src.body.drive.steering_angle, places=6)
                self.assertAlmostEqual(restored.body.drive.steering_angle_velocity, src.body.drive.steering_angle_velocity, places=6)
                self.assertAlmostEqual(restored.body.drive.speed, src.body.drive.speed, places=6)
                self.assertAlmostEqual(restored.body.drive.acceleration, src.body.drive.acceleration, places=6)
                self.assertAlmostEqual(restored.body.drive.jerk, src.body.drive.jerk, places=6)
                self.assertEqual(restored.body.tire_friction, tire_friction)


if __name__ == "__main__":
    unittest.main()
