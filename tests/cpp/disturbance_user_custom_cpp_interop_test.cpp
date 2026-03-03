#include <gtest/gtest.h>

#include <vector>

#include "hako_msgs/pdu_cpptype_DisturbanceUserCustom.hpp"
#include "hako_msgs/pdu_cpptype_conv_DisturbanceUserCustom.hpp"
#include "hako_msgs/pdu_ctype_DisturbanceUserCustom.h"

namespace {

TEST(DisturbanceUserCustomCppInteropTest, CppToPduLayoutMatchesExpectedPrimitiveVarrayLayout) {
    HakoCpp_DisturbanceUserCustom src{};
    src.data = {1.25, 2.5};

    Hako_DisturbanceUserCustom* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_DisturbanceUserCustom(src, &base_ptr);

    ASSERT_GT(pdu_size, 0);
    ASSERT_NE(base_ptr, nullptr);

    auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(base_ptr->_data_len, 2);
    EXPECT_EQ(base_ptr->_data_off, 0);
    EXPECT_EQ(meta->heap_off, HAKO_PDU_META_DATA_SIZE() + HAKO_ALIGN_SIZE(sizeof(Hako_DisturbanceUserCustom), HAKO_ALIGNMENT_SIZE));

    auto* heap_ptr = static_cast<char*>(hako_get_heap_ptr_pdu(base_ptr));
    ASSERT_NE(heap_ptr, nullptr);
    const auto* payload = reinterpret_cast<const Hako_float64*>(heap_ptr + base_ptr->_data_off);
    EXPECT_DOUBLE_EQ(payload[0], 1.25);
    EXPECT_DOUBLE_EQ(payload[1], 2.5);

    hako_destroy_pdu(base_ptr);
}

TEST(DisturbanceUserCustomCppInteropTest, PduRoundtripPreservesSingleElementVarray) {
    HakoCpp_DisturbanceUserCustom src{};
    src.data = {3.75};

    Hako_DisturbanceUserCustom* base_ptr = nullptr;
    ASSERT_GT(hako_convert_cpp2pdu_DisturbanceUserCustom(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    HakoCpp_DisturbanceUserCustom restored{};
    EXPECT_EQ(hako_convert_pdu2cpp_DisturbanceUserCustom(*base_ptr, restored), 0);
    EXPECT_EQ(restored.data, std::vector<Hako_float64>({3.75}));

    hako_destroy_pdu(base_ptr);
}

TEST(DisturbanceUserCustomCppInteropTest, EmptyVarrayUsesCurrentHeapOffset) {
    HakoCpp_DisturbanceUserCustom src{};
    Hako_DisturbanceUserCustom* base_ptr = nullptr;

    ASSERT_GT(hako_convert_cpp2pdu_DisturbanceUserCustom(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(base_ptr->_data_len, 0);
    EXPECT_EQ(base_ptr->_data_off, 0);
    EXPECT_EQ(meta->total_size, meta->heap_off);

    HakoCpp_DisturbanceUserCustom restored{};
    EXPECT_EQ(hako_convert_pdu2cpp_DisturbanceUserCustom(*base_ptr, restored), 0);
    EXPECT_TRUE(restored.data.empty());

    hako_destroy_pdu(base_ptr);
}

}  // namespace
