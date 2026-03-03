#include <gtest/gtest.h>

#include <array>
#include <string>
#include <vector>

#include "pdu_primitive_ctypes_conv.hpp"

template<int _src_len, int _dst_len>
static inline int hako_convert_cpu2pdu_array_string(std::array<std::string, _src_len>& src, Hako_cstring dst[])
{
    return hako_convert_ros2pdu_array_string<_src_len, _dst_len>(src, dst);
}

template<int _src_len, int _dst_len>
static inline int hako_convert_pdu2cpp_array_string(Hako_cstring src[], std::array<std::string, _dst_len>& dst)
{
    return hako_convert_pdu2ros_array_string<_src_len, _dst_len>(src, dst);
}

static inline int hako_convert_pdu2cpp_array_string_varray(const Hako_cstring* src, std::vector<std::string>& dst, int len)
{
    return hako_convert_pdu2ros_array_string_varray(src, dst, len);
}

static inline int hako_convert_cpp2pdu_array_string_varray(const std::vector<std::string>& src, Hako_cstring* dst)
{
    return hako_convert_ros2pdu_array_string_varray(src, dst);
}

#include "hako_msgs/pdu_cpptype_SimpleStructVarray.hpp"
#include "hako_msgs/pdu_cpptype_conv_SimpleStructVarray.hpp"
#include "hako_msgs/pdu_ctype_SimpleStructVarray.h"

namespace {

HakoCpp_SimpleVarray MakeSimpleVarray(std::initializer_list<Hako_int8> data, std::initializer_list<Hako_int8> fixed, Hako_int32 p_mem1)
{
    HakoCpp_SimpleVarray value{};
    value.data = std::vector<Hako_int8>(data);
    std::fill(value.fixed_array.begin(), value.fixed_array.end(), 0);
    int index = 0;
    for (auto item : fixed) {
        value.fixed_array[index++] = item;
    }
    value.p_mem1 = p_mem1;
    return value;
}

TEST(SimpleStructVarrayCppInteropTest, CppToPduLayoutMatchesExpectedVarrayLayout) {
    HakoCpp_SimpleStructVarray src{};
    src.aaa = 7;
    src.fixed_str = {"alpha", "beta"};
    src.varray_str = {"gamma", "delta"};
    src.fixed_array[0] = MakeSimpleVarray({1, 2}, {3, 4}, 5);
    src.fixed_array[1] = MakeSimpleVarray({6}, {7, 8}, 9);
    src.data = {
        MakeSimpleVarray({10, 11}, {12, 13}, 14),
        MakeSimpleVarray({15}, {16, 17}, 18),
    };

    Hako_SimpleStructVarray* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_SimpleStructVarray(src, &base_ptr);

    ASSERT_GT(pdu_size, 0);
    ASSERT_NE(base_ptr, nullptr);

    auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(base_ptr->_varray_str_len, 2);
    EXPECT_EQ(base_ptr->_varray_str_off, 0);
    EXPECT_EQ(base_ptr->_data_len, 2);
    EXPECT_EQ(base_ptr->_data_off, 259);

    auto* heap_ptr = static_cast<char*>(hako_get_heap_ptr_pdu(base_ptr));
    ASSERT_NE(heap_ptr, nullptr);

    const auto* strings = reinterpret_cast<const Hako_cstring*>(heap_ptr);
    EXPECT_STREQ(strings[0].data, "gamma");
    EXPECT_STREQ(strings[1].data, "delta");

    const auto* data_items = reinterpret_cast<const Hako_SimpleVarray*>(heap_ptr + base_ptr->_data_off);
    EXPECT_EQ(data_items[0]._data_len, 2);
    EXPECT_EQ(data_items[1]._data_len, 1);
    EXPECT_EQ(data_items[0]._data_off, 307);
    EXPECT_EQ(data_items[1]._data_off, 309);

    hako_destroy_pdu(base_ptr);
}

TEST(SimpleStructVarrayCppInteropTest, PduRoundtripPreservesValues) {
    HakoCpp_SimpleStructVarray src{};
    src.aaa = 7;
    src.fixed_str = {"alpha", "beta"};
    src.varray_str = {"gamma"};
    src.fixed_array[0] = MakeSimpleVarray({1, 2}, {3, 4}, 5);
    src.data = {MakeSimpleVarray({10}, {11, 12}, 13)};

    Hako_SimpleStructVarray* base_ptr = nullptr;
    ASSERT_GT(hako_convert_cpp2pdu_SimpleStructVarray(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    HakoCpp_SimpleStructVarray restored{};
    EXPECT_EQ(hako_convert_pdu2cpp_SimpleStructVarray(*base_ptr, restored), 0);
    EXPECT_EQ(restored.aaa, 7);
    EXPECT_EQ(restored.fixed_str[0], "alpha");
    EXPECT_EQ(restored.fixed_str[1], "beta");
    EXPECT_EQ(restored.varray_str, std::vector<std::string>({"gamma"}));
    ASSERT_EQ(restored.data.size(), 1U);
    EXPECT_EQ(restored.data[0].data, std::vector<Hako_int8>({10}));
    EXPECT_EQ(restored.data[0].p_mem1, 13);

    hako_destroy_pdu(base_ptr);
}

TEST(SimpleStructVarrayCppInteropTest, EmptyVarraysUseCurrentHeapOffset) {
    HakoCpp_SimpleStructVarray src{};
    src.fixed_str = {"alpha", "beta"};

    Hako_SimpleStructVarray* base_ptr = nullptr;
    ASSERT_GT(hako_convert_cpp2pdu_SimpleStructVarray(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(base_ptr->_varray_str_len, 0);
    EXPECT_EQ(base_ptr->_varray_str_off, 0);
    EXPECT_EQ(base_ptr->_data_len, 0);
    EXPECT_EQ(base_ptr->_data_off, 0);
    EXPECT_EQ(meta->total_size, meta->heap_off);

    hako_destroy_pdu(base_ptr);
}

}  // namespace
