#include <gtest/gtest.h>

#include <array>

#include "hako_msgs/pdu_cpptype_GameControllerOperation.hpp"
#include "hako_msgs/pdu_cpptype_conv_GameControllerOperation.hpp"
#include "hako_msgs/pdu_ctype_GameControllerOperation.h"

namespace {

TEST(GameControllerOperationCppInteropTest, CppToPduLayoutMatchesExpectedFixedArrayLayout) {
    HakoCpp_GameControllerOperation src{};
    src.axis = {0.5, -1.0, 2.0, -3.0, 4.0, -5.0};
    src.button = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};

    Hako_GameControllerOperation* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_GameControllerOperation(src, &base_ptr);

    ASSERT_GT(pdu_size, 0);
    ASSERT_NE(base_ptr, nullptr);

    auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(meta->heap_off, HAKO_PDU_META_DATA_SIZE() + HAKO_ALIGN_SIZE(sizeof(Hako_GameControllerOperation), HAKO_ALIGNMENT_SIZE));
    EXPECT_EQ(meta->total_size, meta->heap_off);

    EXPECT_DOUBLE_EQ(base_ptr->axis[0], 0.5);
    EXPECT_DOUBLE_EQ(base_ptr->axis[1], -1.0);
    EXPECT_DOUBLE_EQ(base_ptr->axis[2], 2.0);
    EXPECT_DOUBLE_EQ(base_ptr->axis[3], -3.0);
    EXPECT_DOUBLE_EQ(base_ptr->axis[4], 4.0);
    EXPECT_DOUBLE_EQ(base_ptr->axis[5], -5.0);

    const std::array<Hako_bool, 15> expected_buttons = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};
    for (int i = 0; i < 15; ++i) {
        EXPECT_EQ(base_ptr->button[i], expected_buttons[i]);
    }

    hako_destroy_pdu(base_ptr);
}

TEST(GameControllerOperationCppInteropTest, PduRoundtripPreservesValues) {
    HakoCpp_GameControllerOperation src{};
    src.axis = {0.5, -1.0, 2.0, -3.0, 4.0, -5.0};
    src.button = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};

    Hako_GameControllerOperation* base_ptr = nullptr;
    ASSERT_GT(hako_convert_cpp2pdu_GameControllerOperation(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    HakoCpp_GameControllerOperation restored{};
    EXPECT_EQ(hako_convert_pdu2cpp_GameControllerOperation(*base_ptr, restored), 0);
    EXPECT_EQ(restored.axis, src.axis);
    EXPECT_EQ(restored.button, src.button);

    hako_destroy_pdu(base_ptr);
}

}  // namespace
