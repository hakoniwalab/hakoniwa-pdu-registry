#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "hako_msgs/pdu_cpptype_cdr_conv_GameControllerOperation.hpp"
#include "sensor_msgs/pdu_cpptype_cdr_conv_JointState.hpp"
#include "sensor_msgs/pdu_cpptype_cdr_conv_PointCloud2.hpp"

namespace {

HakoCpp_PointField MakePointField(const std::string& name, Hako_uint32 offset, Hako_uint8 datatype, Hako_uint32 count)
{
    HakoCpp_PointField field{};
    field.name = name;
    field.offset = offset;
    field.datatype = datatype;
    field.count = count;
    return field;
}

TEST(CdrConversionTest, GameControllerOperationRoundtripPreservesFixedArraysAndCompactBool)
{
    HakoCpp_GameControllerOperation src{};
    src.axis = {0.5, -1.0, 2.0, -3.0, 4.0, -5.0};
    src.button = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};

    std::vector<uint8_t> payload;
    const int len = hako_convert_cpp2cdr_GameControllerOperation(src, payload);
    ASSERT_GT(len, 0);
    ASSERT_EQ(payload.size(), static_cast<size_t>(len));

    // The 15 boolean values must be serialized as CDR boolean bytes, not Hako_bool int32 values.
    EXPECT_LT(payload.size(), 100U);

    HakoCpp_GameControllerOperation restored{};
    ASSERT_TRUE(hako_convert_cdr2cpp_GameControllerOperation(payload, restored));
    EXPECT_EQ(restored.axis, src.axis);
    EXPECT_EQ(restored.button, src.button);
}

TEST(CdrConversionTest, JointStateRoundtripPreservesNestedStructStringSequenceAndDoubleSequences)
{
    HakoCpp_JointState src{};
    src.header.stamp.sec = 12;
    src.header.stamp.nanosec = 345;
    src.header.frame_id = "joint_frame";
    src.name = {"joint_a", "joint_b"};
    src.position = {1.0, 2.0};
    src.velocity = {3.0};
    src.effort = {4.0, 5.0, 6.0};

    std::vector<uint8_t> payload;
    ASSERT_GT(hako_convert_cpp2cdr_JointState(src, payload), 0);

    HakoCpp_JointState restored{};
    ASSERT_TRUE(hako_convert_cdr2cpp_JointState(payload, restored));
    EXPECT_EQ(restored.header.stamp.sec, src.header.stamp.sec);
    EXPECT_EQ(restored.header.stamp.nanosec, src.header.stamp.nanosec);
    EXPECT_EQ(restored.header.frame_id, src.header.frame_id);
    EXPECT_EQ(restored.name, src.name);
    EXPECT_EQ(restored.position, src.position);
    EXPECT_EQ(restored.velocity, src.velocity);
    EXPECT_EQ(restored.effort, src.effort);
}

TEST(CdrConversionTest, PointCloud2RoundtripPreservesStructSequenceByteSequenceAndBoolFields)
{
    HakoCpp_PointCloud2 src{};
    src.header.stamp.sec = 1;
    src.header.stamp.nanosec = 200;
    src.header.frame_id = "pc";
    src.height = 2;
    src.width = 3;
    src.fields = {
        MakePointField("x", 0, 7, 1),
        MakePointField("intensity", 4, 7, 1),
    };
    src.is_bigendian = 0;
    src.point_step = 8;
    src.row_step = 24;
    src.data = {1, 2, 3, 4, 5, 6};
    src.is_dense = 1;

    std::vector<uint8_t> payload;
    ASSERT_GT(hako_convert_cpp2cdr_PointCloud2(src, payload), 0);

    HakoCpp_PointCloud2 restored{};
    ASSERT_TRUE(hako_convert_cdr2cpp_PointCloud2(payload, restored));
    EXPECT_EQ(restored.header.stamp.sec, src.header.stamp.sec);
    EXPECT_EQ(restored.header.stamp.nanosec, src.header.stamp.nanosec);
    EXPECT_EQ(restored.header.frame_id, src.header.frame_id);
    EXPECT_EQ(restored.height, src.height);
    EXPECT_EQ(restored.width, src.width);
    ASSERT_EQ(restored.fields.size(), src.fields.size());
    EXPECT_EQ(restored.fields[0].name, src.fields[0].name);
    EXPECT_EQ(restored.fields[0].offset, src.fields[0].offset);
    EXPECT_EQ(restored.fields[0].datatype, src.fields[0].datatype);
    EXPECT_EQ(restored.fields[0].count, src.fields[0].count);
    EXPECT_EQ(restored.fields[1].name, src.fields[1].name);
    EXPECT_EQ(restored.fields[1].offset, src.fields[1].offset);
    EXPECT_EQ(restored.fields[1].datatype, src.fields[1].datatype);
    EXPECT_EQ(restored.fields[1].count, src.fields[1].count);
    EXPECT_EQ(restored.is_bigendian, src.is_bigendian);
    EXPECT_EQ(restored.point_step, src.point_step);
    EXPECT_EQ(restored.row_step, src.row_step);
    EXPECT_EQ(restored.data, src.data);
    EXPECT_EQ(restored.is_dense, src.is_dense);
}

}  // namespace
