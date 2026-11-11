// Users that map the string-array helper names with #define before including a generated
// C++ converter (the workaround used before the helpers existed) must still compile and work.
#include <gtest/gtest.h>

#include <string>
#include <vector>

#define hako_convert_pdu2cpp_array_string_varray hako_convert_pdu2ros_array_string_varray
#define hako_convert_cpp2pdu_array_string_varray hako_convert_ros2pdu_array_string_varray
#include "sensor_msgs/pdu_cpptype_conv_JointState.hpp"
#undef hako_convert_pdu2cpp_array_string_varray
#undef hako_convert_cpp2pdu_array_string_varray

TEST(StringVarrayAliasCompat, DefineWorkaroundStillRoundTrips)
{
    HakoCpp_JointState src{};
    src.name = {"shoulder", "elbow"};
    src.position = {0.1, 0.2};
    Hako_JointState* pdu = nullptr;
    const int size = hako_convert_cpp2pdu_JointState(src, &pdu);
    ASSERT_GT(size, 0);
    ASSERT_NE(pdu, nullptr);
    HakoCpp_JointState dst{};
    ASSERT_EQ(hako_convert_pdu2cpp_JointState(*pdu, dst), 0);
    EXPECT_EQ(dst.name, src.name);
    EXPECT_EQ(dst.position, src.position);
    hako_destroy_pdu(pdu);
}
