// The converter class's cpp2pdu() builds the PDU straight into the caller's
// buffer. It must produce, byte for byte, the PDU hako_convert_cpp2pdu_<T>()
// lays out (metadata, base, heap), whatever the buffer held before, and refuse
// a buffer that is too small without writing past it.
#include <gtest/gtest.h>

#include <cstring>
#include <string>
#include <vector>

#include "sensor_msgs/pdu_cpptype_conv_JointState.hpp"
#include "sensor_msgs/pdu_cpptype_conv_PointCloud2.hpp"
#include "std_msgs/pdu_cpptype_conv_Float64MultiArray.hpp"

namespace {

// The reference: the PDU made by hako_convert_cpp2pdu_<T>() (an allocated PDU).
template <typename CppT, typename HakoT, typename ConvertFn>
std::vector<char> ReferencePdu(CppT& src, ConvertFn convert)
{
    HakoT* base_ptr = nullptr;
    const int size = convert(src, &base_ptr);
    EXPECT_GT(size, 0);
    if (size <= 0 || base_ptr == nullptr) {
        return {};
    }
    const char* top = static_cast<const char*>(hako_get_top_ptr_pdu(base_ptr));
    std::vector<char> pdu(top, top + size);
    hako_destroy_pdu(base_ptr);
    return pdu;
}

// cpp2pdu() into a buffer first filled with fill_byte (stale data from before).
template <typename ConverterT, typename CppT>
std::vector<char> DirectPdu(CppT& src, std::size_t capacity, unsigned char fill_byte)
{
    std::vector<char> buffer(capacity, static_cast<char>(fill_byte));
    ConverterT conv;
    const int size = conv.cpp2pdu(src, buffer.data(), static_cast<int>(buffer.size()));
    EXPECT_GT(size, 0);
    buffer.resize(size > 0 ? static_cast<std::size_t>(size) : 0);
    return buffer;
}

HakoCpp_PointCloud2 MakeCloud(std::size_t bytes)
{
    HakoCpp_PointCloud2 cloud{};
    cloud.header.stamp.sec = 12;
    cloud.header.stamp.nanosec = 345;
    cloud.header.frame_id = "overhead_lidar";
    const char* names[] = {"x", "y", "z"};
    for (int i = 0; i < 3; ++i) {
        HakoCpp_PointField field{};
        field.name = names[i];
        field.offset = 4 * i;
        field.datatype = 7;
        field.count = 1;
        cloud.fields.push_back(field);
    }
    cloud.height = 1;
    cloud.width = static_cast<Hako_uint32>(bytes / 12);
    cloud.point_step = 12;
    cloud.row_step = static_cast<Hako_uint32>(bytes);
    cloud.data.resize(bytes);
    for (std::size_t i = 0; i < bytes; ++i) {
        cloud.data[i] = static_cast<Hako_uint8>((i * 31u + 7u) & 0xffu);
    }
    cloud.is_dense = true;
    return cloud;
}

TEST(Cpp2PduDirectWriteTest, PointCloud2MatchesReferenceByteForByte)
{
    for (std::size_t bytes : {std::size_t{0}, std::size_t{12}, std::size_t{1001}, std::size_t{4194304}}) {
        HakoCpp_PointCloud2 cloud = MakeCloud(bytes);
        const std::vector<char> reference =
            ReferencePdu<HakoCpp_PointCloud2, Hako_PointCloud2>(cloud, hako_convert_cpp2pdu_PointCloud2);
        for (unsigned char fill : {0x00u, 0xabu}) {
            const std::vector<char> direct =
                DirectPdu<hako::pdu::msgs::sensor_msgs::PointCloud2>(cloud, reference.size() + 64, fill);
            ASSERT_EQ(direct.size(), reference.size()) << "bytes=" << bytes;
            EXPECT_EQ(0, std::memcmp(direct.data(), reference.data(), reference.size())) << "bytes=" << bytes;
        }
    }
}

TEST(Cpp2PduDirectWriteTest, PointCloud2RoundTrip)
{
    HakoCpp_PointCloud2 cloud = MakeCloud(1200);
    std::vector<char> pdu = DirectPdu<hako::pdu::msgs::sensor_msgs::PointCloud2>(cloud, 1200 + 4096, 0xab);
    hako::pdu::msgs::sensor_msgs::PointCloud2 conv;
    HakoCpp_PointCloud2 back{};
    ASSERT_TRUE(conv.pdu2cpp(pdu.data(), back));
    EXPECT_EQ(back.header.frame_id, cloud.header.frame_id);
    ASSERT_EQ(back.fields.size(), 3u);
    EXPECT_EQ(back.fields[2].name, "z");
    EXPECT_EQ(back.width, cloud.width);
    EXPECT_EQ(back.data, cloud.data);
}

TEST(Cpp2PduDirectWriteTest, JointStateMatchesReference)
{
    // A string array and three float64 arrays: several heap blocks in a row.
    HakoCpp_JointState state{};
    state.header.frame_id = "base_link";
    state.name = {"shoulder_pan", "shoulder_lift", "elbow_flex"};
    state.position = {0.1, -0.2, 0.3};
    state.velocity = {1.0, 2.0};
    state.effort = {};
    const std::vector<char> reference =
        ReferencePdu<HakoCpp_JointState, Hako_JointState>(state, hako_convert_cpp2pdu_JointState);
    const std::vector<char> direct =
        DirectPdu<hako::pdu::msgs::sensor_msgs::JointState>(state, reference.size(), 0xab);
    ASSERT_EQ(direct.size(), reference.size());
    EXPECT_EQ(0, std::memcmp(direct.data(), reference.data(), reference.size()));
}

TEST(Cpp2PduDirectWriteTest, NestedStructArrayMatchesReference)
{
    // layout.dim is an array of structs holding a string; data is a float64 array.
    HakoCpp_Float64MultiArray array{};
    HakoCpp_MultiArrayDimension dim{};
    dim.label = "rows";
    dim.size = 2;
    dim.stride = 6;
    array.layout.dim.push_back(dim);
    dim.label = "cols";
    dim.size = 3;
    dim.stride = 3;
    array.layout.dim.push_back(dim);
    array.layout.data_offset = 0;
    array.data = {1, 2, 3, 4, 5, 6};
    const std::vector<char> reference =
        ReferencePdu<HakoCpp_Float64MultiArray, Hako_Float64MultiArray>(array, hako_convert_cpp2pdu_Float64MultiArray);
    const std::vector<char> direct =
        DirectPdu<hako::pdu::msgs::std_msgs::Float64MultiArray>(array, reference.size(), 0xab);
    ASSERT_EQ(direct.size(), reference.size());
    EXPECT_EQ(0, std::memcmp(direct.data(), reference.data(), reference.size()));
}

TEST(Cpp2PduDirectWriteTest, TooSmallBufferIsRefusedUntouched)
{
    HakoCpp_PointCloud2 cloud = MakeCloud(1200);
    const std::vector<char> reference =
        ReferencePdu<HakoCpp_PointCloud2, Hako_PointCloud2>(cloud, hako_convert_cpp2pdu_PointCloud2);
    std::vector<char> buffer(reference.size() + 16, static_cast<char>(0x5a));
    hako::pdu::msgs::sensor_msgs::PointCloud2 conv;
    const int short_len = static_cast<int>(reference.size()) - 1;
    EXPECT_EQ(-1, conv.cpp2pdu(cloud, buffer.data(), short_len));
    for (char c : buffer) {
        ASSERT_EQ(static_cast<char>(0x5a), c);
    }
}

TEST(Cpp2PduDirectWriteTest, UnalignedExactSizeBuffer)
{
    // The output needs no alignment and no room beyond the PDU itself.
    HakoCpp_PointCloud2 cloud = MakeCloud(1001);
    const std::vector<char> reference =
        ReferencePdu<HakoCpp_PointCloud2, Hako_PointCloud2>(cloud, hako_convert_cpp2pdu_PointCloud2);
    for (std::size_t shift : {std::size_t{1}, std::size_t{3}, std::size_t{5}}) {
        std::vector<char> storage(reference.size() + shift + 1, static_cast<char>(0x5a));
        char* out = storage.data() + shift;
        hako::pdu::msgs::sensor_msgs::PointCloud2 conv;
        ASSERT_EQ(static_cast<int>(reference.size()),
                  conv.cpp2pdu(cloud, out, static_cast<int>(reference.size())));
        EXPECT_EQ(0, std::memcmp(out, reference.data(), reference.size())) << "shift=" << shift;
        EXPECT_EQ(static_cast<char>(0x5a), storage[shift - 1]);
        EXPECT_EQ(static_cast<char>(0x5a), storage[shift + reference.size()]);
    }
}

TEST(Cpp2PduDirectWriteTest, BufferOverlappingTheSourceIsRefused)
{
    // The source's arrays are read while the PDU is written: writing over them
    // is refused, and the source is left as it was.
    HakoCpp_PointCloud2 cloud = MakeCloud(8192);
    const std::vector<Hako_uint8> before = cloud.data;
    hako::pdu::msgs::sensor_msgs::PointCloud2 conv;
    char* inside = reinterpret_cast<char*>(cloud.data.data());
    EXPECT_EQ(-1, conv.cpp2pdu(cloud, inside, static_cast<int>(cloud.data.size())));
    EXPECT_EQ(before, cloud.data);
}

TEST(Cpp2PduDirectWriteTest, NegativeLengthIsRefused)
{
    HakoCpp_PointCloud2 cloud = MakeCloud(12);
    std::vector<char> buffer(4096);
    hako::pdu::msgs::sensor_msgs::PointCloud2 conv;
    EXPECT_EQ(-1, conv.cpp2pdu(cloud, buffer.data(), -1));
    EXPECT_EQ(-1, conv.cpp2pdu(cloud, nullptr, 4096));
}

}  // namespace
