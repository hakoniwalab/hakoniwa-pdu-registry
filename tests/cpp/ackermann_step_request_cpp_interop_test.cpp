#include <gtest/gtest.h>

#include "hako_srv_msgs/pdu_cpptype_AckermannStepRequestPacket.hpp"
#include "hako_srv_msgs/pdu_cpptype_conv_AckermannStepRequestPacket.hpp"
#include "hako_srv_msgs/pdu_ctype_AckermannStepRequestPacket.h"

namespace {

TEST(AckermannStepRequestCppInteropTest, PacketRoundtripPreservesTireFrictionAndExistingFields) {
    for (const double tire_friction : {0.5, 0.0}) {
        HakoCpp_AckermannStepRequestPacket src{};
        src.header.request_id = 17;
        src.header.service_name = "ackermann_step";
        src.header.client_name = "test_client";
        src.header.opcode = 3;
        src.header.status_poll_interval_msec = 20;
        src.body.step = 42;
        src.body.drive.steering_angle = 0.1F;
        src.body.drive.steering_angle_velocity = 0.2F;
        src.body.drive.speed = 3.0F;
        src.body.drive.acceleration = 0.4F;
        src.body.drive.jerk = 0.5F;
        src.body.tire_friction = tire_friction;

        Hako_AckermannStepRequestPacket* base_ptr = nullptr;
        ASSERT_GT(hako_convert_cpp2pdu_AckermannStepRequestPacket(src, &base_ptr), 0);
        ASSERT_NE(base_ptr, nullptr);

        HakoCpp_AckermannStepRequestPacket restored{};
        ASSERT_EQ(hako_convert_pdu2cpp_AckermannStepRequestPacket(*base_ptr, restored), 0);
        EXPECT_EQ(restored.header.request_id, src.header.request_id);
        EXPECT_EQ(restored.header.service_name, src.header.service_name);
        EXPECT_EQ(restored.header.client_name, src.header.client_name);
        EXPECT_EQ(restored.header.opcode, src.header.opcode);
        EXPECT_EQ(restored.header.status_poll_interval_msec, src.header.status_poll_interval_msec);
        EXPECT_EQ(restored.body.step, src.body.step);
        EXPECT_FLOAT_EQ(restored.body.drive.steering_angle, src.body.drive.steering_angle);
        EXPECT_FLOAT_EQ(restored.body.drive.steering_angle_velocity, src.body.drive.steering_angle_velocity);
        EXPECT_FLOAT_EQ(restored.body.drive.speed, src.body.drive.speed);
        EXPECT_FLOAT_EQ(restored.body.drive.acceleration, src.body.drive.acceleration);
        EXPECT_FLOAT_EQ(restored.body.drive.jerk, src.body.drive.jerk);
        EXPECT_DOUBLE_EQ(restored.body.tire_friction, tire_friction);

        hako_destroy_pdu(base_ptr);
    }
}

}  // namespace
