#include <gtest/gtest.h>

#include <vector>

#include "sensor_msgs/pdu_cpptype_PointCloud2.hpp"
#include "sensor_msgs/pdu_cpptype_conv_PointCloud2.hpp"
#include "sensor_msgs/pdu_ctype_PointCloud2.h"

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

TEST(PointCloud2CppInteropTest, CppToPduLayoutMatchesExpectedVarrayLayout) {
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
    src.is_bigendian = false;
    src.point_step = 8;
    src.row_step = 24;
    src.data = {1, 2, 3, 4, 5, 6};
    src.is_dense = true;

    Hako_PointCloud2* base_ptr = nullptr;
    const int pdu_size = hako_convert_cpp2pdu_PointCloud2(src, &base_ptr);

    ASSERT_GT(pdu_size, 0);
    ASSERT_NE(base_ptr, nullptr);

    auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(base_ptr->_fields_len, 2);
    EXPECT_EQ(base_ptr->_fields_off, 0);
    EXPECT_EQ(base_ptr->_data_len, 6);
    EXPECT_EQ(base_ptr->_data_off, 280);
    EXPECT_EQ(meta->heap_off, HAKO_PDU_META_DATA_SIZE() + HAKO_ALIGN_SIZE(sizeof(Hako_PointCloud2), HAKO_ALIGNMENT_SIZE));

    auto* heap_ptr = static_cast<char*>(hako_get_heap_ptr_pdu(base_ptr));
    ASSERT_NE(heap_ptr, nullptr);

    const auto* fields = reinterpret_cast<const Hako_PointField*>(heap_ptr);
    EXPECT_STREQ(fields[0].name, "x");
    EXPECT_EQ(fields[0].offset, 0U);
    EXPECT_EQ(fields[0].datatype, 7U);
    EXPECT_EQ(fields[0].count, 1U);
    EXPECT_STREQ(fields[1].name, "intensity");
    EXPECT_EQ(fields[1].offset, 4U);
    EXPECT_EQ(fields[1].datatype, 7U);
    EXPECT_EQ(fields[1].count, 1U);

    const auto* data = reinterpret_cast<const Hako_uint8*>(heap_ptr + base_ptr->_data_off);
    EXPECT_EQ(std::vector<Hako_uint8>(data, data + 6), std::vector<Hako_uint8>({1, 2, 3, 4, 5, 6}));

    hako_destroy_pdu(base_ptr);
}

TEST(PointCloud2CppInteropTest, PduRoundtripPreservesValues) {
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
    src.is_bigendian = false;
    src.point_step = 8;
    src.row_step = 24;
    src.data = {1, 2, 3, 4, 5, 6};
    src.is_dense = true;

    Hako_PointCloud2* base_ptr = nullptr;
    ASSERT_GT(hako_convert_cpp2pdu_PointCloud2(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    HakoCpp_PointCloud2 restored{};
    EXPECT_EQ(hako_convert_pdu2cpp_PointCloud2(*base_ptr, restored), 0);
    EXPECT_EQ(restored.header.stamp.sec, 1);
    EXPECT_EQ(restored.header.stamp.nanosec, 200U);
    EXPECT_EQ(restored.header.frame_id, "pc");
    EXPECT_EQ(restored.height, 2U);
    EXPECT_EQ(restored.width, 3U);
    ASSERT_EQ(restored.fields.size(), 2U);
    EXPECT_EQ(restored.fields[0].name, "x");
    EXPECT_EQ(restored.fields[1].name, "intensity");
    EXPECT_EQ(restored.data, std::vector<Hako_uint8>({1, 2, 3, 4, 5, 6}));
    EXPECT_EQ(restored.is_dense, true);

    hako_destroy_pdu(base_ptr);
}

TEST(PointCloud2CppInteropTest, EmptyVarraysUseCurrentHeapOffset) {
    HakoCpp_PointCloud2 src{};

    Hako_PointCloud2* base_ptr = nullptr;
    ASSERT_GT(hako_convert_cpp2pdu_PointCloud2(src, &base_ptr), 0);
    ASSERT_NE(base_ptr, nullptr);

    EXPECT_EQ(base_ptr->_fields_len, 0);
    EXPECT_EQ(base_ptr->_fields_off, 0);
    EXPECT_EQ(base_ptr->_data_len, 0);
    EXPECT_EQ(base_ptr->_data_off, 0);

    auto* meta = hako_get_pdu_meta_data(base_ptr);
    ASSERT_NE(meta, nullptr);
    EXPECT_EQ(meta->total_size, meta->heap_off);

    hako_destroy_pdu(base_ptr);
}

}  // namespace
