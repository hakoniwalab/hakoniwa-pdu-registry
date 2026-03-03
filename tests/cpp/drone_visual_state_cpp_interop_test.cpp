#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "hako_msgs/pdu_cpptype_DroneVisualState.hpp"
#include "hako_msgs/pdu_cpptype_DroneVisualStateArray.hpp"
#include "hako_msgs/pdu_cpptype_conv_DroneVisualState.hpp"
#include "hako_msgs/pdu_cpptype_conv_DroneVisualStateArray.hpp"
#include "hako_msgs/pdu_ctype_DroneVisualState.h"
#include "hako_msgs/pdu_ctype_DroneVisualStateArray.h"

namespace {

constexpr int kDroneCount = 100;
constexpr int kPwmCount = 4;

HakoCpp_DroneVisualState MakeDroneVisualState(
    float x,
    float y,
    float z,
    float roll,
    float pitch,
    float yaw,
    std::initializer_list<Hako_float32> pwm_duty)
{
    HakoCpp_DroneVisualState value{};
    value.x = x;
    value.y = y;
    value.z = z;
    value.roll = roll;
    value.pitch = pitch;
    value.yaw = yaw;
    value.pwm_duty = std::vector<Hako_float32>(pwm_duty);
    return value;
}

std::vector<HakoCpp_DroneVisualState> MakeDroneFleet()
{
    std::vector<HakoCpp_DroneVisualState> drones;
    drones.reserve(kDroneCount);
    for (int i = 0; i < kDroneCount; ++i) {
        const float base = static_cast<float>(i);
        drones.push_back(MakeDroneVisualState(
            base + 0.1F,
            base + 0.2F,
            base + 0.3F,
            base + 0.01F,
            base + 0.02F,
            base + 0.03F,
            {
                0.10F + (base * 0.001F),
                0.20F + (base * 0.001F),
                0.30F + (base * 0.001F),
                0.40F + (base * 0.001F),
            }));
    }
    return drones;
}

TEST(DroneVisualStateCppInteropTest, CppToPduLayoutMatchesExpectedVarrayLayout) {
    HakoCpp_DroneVisualState src = MakeDroneVisualState(1.5F, -2.25F, 3.75F, 0.1F, -0.2F, 0.3F, {0.25F, 0.5F, 0.75F});

    Hako_DroneVisualState* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_DroneVisualState(src, &base_ptr);

    ASSERT_GT(pdu_size, 0);
    ASSERT_NE(base_ptr, nullptr);

    auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(meta->heap_off, HAKO_PDU_META_DATA_SIZE() + HAKO_ALIGN_SIZE(sizeof(Hako_DroneVisualState), HAKO_ALIGNMENT_SIZE));
    EXPECT_EQ(base_ptr->_pwm_duty_len, 3);
    EXPECT_EQ(base_ptr->_pwm_duty_off, 0);
    EXPECT_EQ(meta->total_size, meta->heap_off + HAKO_ALIGN_SIZE(3 * static_cast<int>(sizeof(Hako_float32)), HAKO_ALIGNMENT_SIZE));

    auto* heap_ptr = static_cast<Hako_float32*>(hako_get_heap_ptr_pdu(base_ptr));
    ASSERT_NE(heap_ptr, nullptr);
    EXPECT_FLOAT_EQ(heap_ptr[0], 0.25F);
    EXPECT_FLOAT_EQ(heap_ptr[1], 0.5F);
    EXPECT_FLOAT_EQ(heap_ptr[2], 0.75F);

    hako_destroy_pdu(base_ptr);
}

TEST(DroneVisualStateCppInteropTest, PduRoundtripPreservesValues) {
    HakoCpp_DroneVisualState src = MakeDroneVisualState(-1.0F, 2.0F, -3.0F, 0.4F, 0.5F, 0.6F, {0.1F, 0.9F});

    Hako_DroneVisualState* base_ptr = nullptr;
    ASSERT_GT(hako_convert_cpp2pdu_DroneVisualState(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    HakoCpp_DroneVisualState restored{};
    EXPECT_EQ(hako_convert_pdu2cpp_DroneVisualState(*base_ptr, restored), 0);
    EXPECT_FLOAT_EQ(restored.x, src.x);
    EXPECT_FLOAT_EQ(restored.y, src.y);
    EXPECT_FLOAT_EQ(restored.z, src.z);
    EXPECT_FLOAT_EQ(restored.roll, src.roll);
    EXPECT_FLOAT_EQ(restored.pitch, src.pitch);
    EXPECT_FLOAT_EQ(restored.yaw, src.yaw);
    EXPECT_EQ(restored.pwm_duty, src.pwm_duty);

    hako_destroy_pdu(base_ptr);
}

TEST(DroneVisualStateArrayCppInteropTest, CppToPduLayoutMatchesExpectedNestedVarrayLayout) {
    HakoCpp_DroneVisualStateArray src{};
    src.sequence_id = 42;
    src.chunk_index = 3;
    src.chunk_count = 10;
    src.start_index = 300;
    src.valid_count = kDroneCount;
    src.drones = MakeDroneFleet();

    Hako_DroneVisualStateArray* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_DroneVisualStateArray(src, &base_ptr);

    ASSERT_GT(pdu_size, 0);
    ASSERT_NE(base_ptr, nullptr);

    auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(base_ptr->sequence_id, 42U);
    EXPECT_EQ(base_ptr->chunk_index, 3U);
    EXPECT_EQ(base_ptr->chunk_count, 10U);
    EXPECT_EQ(base_ptr->start_index, 300U);
    EXPECT_EQ(base_ptr->valid_count, kDroneCount);
    EXPECT_EQ(base_ptr->_drones_len, kDroneCount);
    EXPECT_EQ(base_ptr->_drones_off, 0);
    EXPECT_EQ(meta->heap_off, HAKO_PDU_META_DATA_SIZE() + HAKO_ALIGN_SIZE(sizeof(Hako_DroneVisualStateArray), HAKO_ALIGNMENT_SIZE));
    std::cout << "DroneVisualStateArray total PDU size (" << kDroneCount << " drones x " << kPwmCount
              << " pwm): " << pdu_size << " bytes" << std::endl;

    auto* heap_ptr = static_cast<char*>(hako_get_heap_ptr_pdu(base_ptr));
    ASSERT_NE(heap_ptr, nullptr);
    const auto* states = reinterpret_cast<const Hako_DroneVisualState*>(heap_ptr);
    EXPECT_EQ(states[0]._pwm_duty_len, kPwmCount);
    EXPECT_EQ(states[0]._pwm_duty_off, kDroneCount * static_cast<int>(sizeof(Hako_DroneVisualState)));
    EXPECT_EQ(states[kDroneCount - 1]._pwm_duty_len, kPwmCount);
    EXPECT_EQ(states[kDroneCount - 1]._pwm_duty_off,
              (kDroneCount * static_cast<int>(sizeof(Hako_DroneVisualState))) +
              ((kDroneCount - 1) * kPwmCount * static_cast<int>(sizeof(Hako_float32))));

    const auto* first_pwm = reinterpret_cast<const Hako_float32*>(heap_ptr + states[0]._pwm_duty_off);
    const auto* last_pwm = reinterpret_cast<const Hako_float32*>(heap_ptr + states[kDroneCount - 1]._pwm_duty_off);
    EXPECT_FLOAT_EQ(first_pwm[0], 0.10F);
    EXPECT_FLOAT_EQ(first_pwm[3], 0.40F);
    EXPECT_FLOAT_EQ(last_pwm[0], 0.199F);
    EXPECT_FLOAT_EQ(last_pwm[3], 0.499F);
    EXPECT_EQ(meta->total_size, 4856);

    hako_destroy_pdu(base_ptr);
}

TEST(DroneVisualStateArrayCppInteropTest, PduRoundtripPreservesValues) {
    HakoCpp_DroneVisualStateArray src{};
    src.sequence_id = 42;
    src.chunk_index = 3;
    src.chunk_count = 10;
    src.start_index = 300;
    src.valid_count = kDroneCount;
    src.drones = MakeDroneFleet();

    Hako_DroneVisualStateArray* base_ptr = nullptr;
    ASSERT_GT(hako_convert_cpp2pdu_DroneVisualStateArray(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    HakoCpp_DroneVisualStateArray restored{};
    EXPECT_EQ(hako_convert_pdu2cpp_DroneVisualStateArray(*base_ptr, restored), 0);
    EXPECT_EQ(restored.sequence_id, src.sequence_id);
    EXPECT_EQ(restored.chunk_index, src.chunk_index);
    EXPECT_EQ(restored.chunk_count, src.chunk_count);
    EXPECT_EQ(restored.start_index, src.start_index);
    EXPECT_EQ(restored.valid_count, src.valid_count);
    ASSERT_EQ(restored.drones.size(), src.drones.size());
    for (size_t i = 0; i < src.drones.size(); ++i) {
        EXPECT_FLOAT_EQ(restored.drones[i].x, src.drones[i].x);
        EXPECT_FLOAT_EQ(restored.drones[i].y, src.drones[i].y);
        EXPECT_FLOAT_EQ(restored.drones[i].z, src.drones[i].z);
        EXPECT_FLOAT_EQ(restored.drones[i].roll, src.drones[i].roll);
        EXPECT_FLOAT_EQ(restored.drones[i].pitch, src.drones[i].pitch);
        EXPECT_FLOAT_EQ(restored.drones[i].yaw, src.drones[i].yaw);
        EXPECT_EQ(restored.drones[i].pwm_duty, src.drones[i].pwm_duty);
    }

    hako_destroy_pdu(base_ptr);
}

}  // namespace
