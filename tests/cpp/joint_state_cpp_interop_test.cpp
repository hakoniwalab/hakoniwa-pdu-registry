#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "pdu_primitive_ctypes_conv.hpp"

static inline int hako_convert_pdu2cpp_array_string_varray(const Hako_cstring* src, std::vector<std::string>& dst, int len)
{
    return hako_convert_pdu2ros_array_string_varray(src, dst, len);
}

static inline int hako_convert_cpp2pdu_array_string_varray(const std::vector<std::string>& src, Hako_cstring* dst)
{
    return hako_convert_ros2pdu_array_string_varray(src, dst);
}

#include "sensor_msgs/pdu_cpptype_JointState.hpp"
#include "sensor_msgs/pdu_cpptype_conv_JointState.hpp"
#include "sensor_msgs/pdu_ctype_JointState.h"

namespace {

TEST(JointStateCppInteropTest, CppToPduLayoutMatchesExpectedVarrayLayout) {
    HakoCpp_JointState src{};
    src.header.frame_id = "frame";
    src.name = {"a", "b"};
    src.position = {1.0, 2.0};
    src.velocity = {3.0};
    src.effort = {4.0};

    Hako_JointState* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_JointState(src, &base_ptr);

    ASSERT_GT(pdu_size, 0);
    ASSERT_NE(base_ptr, nullptr);

    auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(base_ptr->_name_len, 2);
    EXPECT_EQ(base_ptr->_name_off, 0);
    EXPECT_EQ(base_ptr->_position_len, 2);
    EXPECT_EQ(base_ptr->_position_off, 256);
    EXPECT_EQ(base_ptr->_velocity_len, 1);
    EXPECT_EQ(base_ptr->_velocity_off, 272);
    EXPECT_EQ(base_ptr->_effort_len, 1);
    EXPECT_EQ(base_ptr->_effort_off, 280);
    EXPECT_EQ(meta->heap_off, HAKO_PDU_META_DATA_SIZE() + HAKO_ALIGN_SIZE(sizeof(Hako_JointState), HAKO_ALIGNMENT_SIZE));

    auto* heap_ptr = static_cast<char*>(hako_get_heap_ptr_pdu(base_ptr));
    ASSERT_NE(heap_ptr, nullptr);

    const auto* names = reinterpret_cast<const Hako_cstring*>(heap_ptr);
    EXPECT_STREQ(names[0].data, "a");
    EXPECT_STREQ(names[1].data, "b");

    const auto* position = reinterpret_cast<const Hako_float64*>(heap_ptr + base_ptr->_position_off);
    const auto* velocity = reinterpret_cast<const Hako_float64*>(heap_ptr + base_ptr->_velocity_off);
    const auto* effort = reinterpret_cast<const Hako_float64*>(heap_ptr + base_ptr->_effort_off);
    EXPECT_DOUBLE_EQ(position[0], 1.0);
    EXPECT_DOUBLE_EQ(position[1], 2.0);
    EXPECT_DOUBLE_EQ(velocity[0], 3.0);
    EXPECT_DOUBLE_EQ(effort[0], 4.0);

    hako_destroy_pdu(base_ptr);
}

TEST(JointStateCppInteropTest, PduRoundtripPreservesValues) {
    HakoCpp_JointState src{};
    src.header.frame_id = "frame";
    src.name = {"a", "b"};
    src.position = {1.0, 2.0};
    src.velocity = {3.0};
    src.effort = {4.0};

    Hako_JointState* base_ptr = nullptr;
    ASSERT_GT(hako_convert_cpp2pdu_JointState(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    HakoCpp_JointState restored{};
    EXPECT_EQ(hako_convert_pdu2cpp_JointState(*base_ptr, restored), 0);
    EXPECT_EQ(restored.header.frame_id, "frame");
    EXPECT_EQ(restored.name, std::vector<std::string>({"a", "b"}));
    EXPECT_EQ(restored.position, std::vector<Hako_float64>({1.0, 2.0}));
    EXPECT_EQ(restored.velocity, std::vector<Hako_float64>({3.0}));
    EXPECT_EQ(restored.effort, std::vector<Hako_float64>({4.0}));

    hako_destroy_pdu(base_ptr);
}

TEST(JointStateCppInteropTest, EmptyArraysUseCurrentHeapOffset) {
    HakoCpp_JointState src{};
    Hako_JointState* base_ptr = nullptr;
    ASSERT_GT(hako_convert_cpp2pdu_JointState(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    EXPECT_EQ(base_ptr->_name_len, 0);
    EXPECT_EQ(base_ptr->_name_off, 0);
    EXPECT_EQ(base_ptr->_position_len, 0);
    EXPECT_EQ(base_ptr->_position_off, 0);
    EXPECT_EQ(base_ptr->_velocity_len, 0);
    EXPECT_EQ(base_ptr->_velocity_off, 0);
    EXPECT_EQ(base_ptr->_effort_len, 0);
    EXPECT_EQ(base_ptr->_effort_off, 0);

    auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(meta->total_size, meta->heap_off);

    hako_destroy_pdu(base_ptr);
}

}  // namespace
