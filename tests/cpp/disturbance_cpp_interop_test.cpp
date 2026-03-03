#include <gtest/gtest.h>

#include <array>
#include <cstring>
#include <vector>

#include "hako_msgs/pdu_cpptype_Disturbance.hpp"
#include "hako_msgs/pdu_cpptype_conv_Disturbance.hpp"
#include "hako_msgs/pdu_ctype_Disturbance.h"
#include "hako_msgs/pdu_ctype_DisturbanceUserCustom.h"
#include "pdu_primitive_ctypes.h"

namespace {

using hako::pdu::msgs::hako_msgs::Disturbance;

std::vector<unsigned char> ToBytes(void* base_ptr) {
    auto* meta = hako_get_pdu_meta_data(base_ptr);
    EXPECT_NE(meta, nullptr);
    auto* top_ptr = static_cast<unsigned char*>(hako_get_top_ptr_pdu(base_ptr));
    EXPECT_NE(top_ptr, nullptr);
    return std::vector<unsigned char>(top_ptr, top_ptr + meta->total_size);
}

TEST(DisturbanceCppInteropTest, CppToPduLayoutMatchesExpectedNestedVarrayLayout) {
    HakoCpp_Disturbance src{};

    HakoCpp_DisturbanceUserCustom item1;
    item1.data = {1.25, 2.5};
    HakoCpp_DisturbanceUserCustom item2;
    item2.data = {3.75};
    src.d_user_custom = {item1, item2};

    Hako_Disturbance* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_Disturbance(src, &base_ptr);

    ASSERT_GT(pdu_size, 0);
    ASSERT_NE(base_ptr, nullptr);

    const auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(base_ptr->_d_user_custom_len, 2);
    EXPECT_EQ(base_ptr->_d_user_custom_off, 0);
    EXPECT_EQ(meta->heap_off, HAKO_PDU_META_DATA_SIZE() + sizeof(Hako_Disturbance));

    auto* heap_ptr = static_cast<char*>(hako_get_heap_ptr_pdu(base_ptr));
    ASSERT_NE(heap_ptr, nullptr);

    const auto* children = reinterpret_cast<const Hako_DisturbanceUserCustom*>(heap_ptr);
    EXPECT_EQ(children[0]._data_len, 2);
    EXPECT_EQ(children[0]._data_off, 16);
    EXPECT_EQ(children[1]._data_len, 1);
    EXPECT_EQ(children[1]._data_off, 32);

    const auto* payload0 = reinterpret_cast<const Hako_float64*>(heap_ptr + children[0]._data_off);
    const auto* payload1 = reinterpret_cast<const Hako_float64*>(heap_ptr + children[1]._data_off);
    EXPECT_DOUBLE_EQ(payload0[0], 1.25);
    EXPECT_DOUBLE_EQ(payload0[1], 2.5);
    EXPECT_DOUBLE_EQ(payload1[0], 3.75);

    hako_destroy_pdu(base_ptr);
}

TEST(DisturbanceCppInteropTest, PduRoundtripPreservesNestedVarrayValues) {
    HakoCpp_Disturbance src{};

    HakoCpp_DisturbanceUserCustom item1;
    item1.data = {1.25, 2.5};
    HakoCpp_DisturbanceUserCustom item2;
    item2.data = {3.75};
    src.d_user_custom = {item1, item2};

    Hako_Disturbance* base_ptr = nullptr;
    ASSERT_GT(hako_convert_cpp2pdu_Disturbance(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    HakoCpp_Disturbance restored;
    EXPECT_EQ(hako_convert_pdu2cpp_Disturbance(*base_ptr, restored), 0);
    ASSERT_EQ(restored.d_user_custom.size(), 2U);
    ASSERT_EQ(restored.d_user_custom[0].data.size(), 2U);
    ASSERT_EQ(restored.d_user_custom[1].data.size(), 1U);
    EXPECT_DOUBLE_EQ(restored.d_user_custom[0].data[0], 1.25);
    EXPECT_DOUBLE_EQ(restored.d_user_custom[0].data[1], 2.5);
    EXPECT_DOUBLE_EQ(restored.d_user_custom[1].data[0], 3.75);

    hako_destroy_pdu(base_ptr);
}

TEST(DisturbanceCppInteropTest, EmptyNestedVarrayUsesCurrentHeapOffset) {
    HakoCpp_Disturbance src{};
    Hako_Disturbance* base_ptr = nullptr;

    ASSERT_GT(hako_convert_cpp2pdu_Disturbance(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(base_ptr->_d_user_custom_len, 0);
    EXPECT_EQ(base_ptr->_d_user_custom_off, 0);
    EXPECT_EQ(meta->total_size, meta->heap_off);

    hako_destroy_pdu(base_ptr);
}

}  // namespace
