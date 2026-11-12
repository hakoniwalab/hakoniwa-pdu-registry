// Strings in fixed char arrays: a message string as long as the array or
// longer is cut so the terminating '\0' stays inside it (it used to be written
// one or more bytes past the array), and a PDU string that fills its array
// with no '\0' is read up to the array's end, not past it.
#include <gtest/gtest.h>

#include <cstring>
#include <string>
#include <vector>

#include "sensor_msgs/pdu_cpptype_conv_JointState.hpp"
#include "sensor_msgs/pdu_cpptype_conv_PointCloud2.hpp"

namespace {

constexpr std::size_t kFrameIdSize = M_SIZE(Hako_Header, frame_id);

std::vector<char> ToPdu(HakoCpp_PointCloud2& cloud)
{
    std::vector<char> buffer(1 << 16, static_cast<char>(0x5a));
    hako::pdu::msgs::sensor_msgs::PointCloud2 conv;
    const int size = conv.cpp2pdu(cloud, buffer.data(), static_cast<int>(buffer.size()));
    EXPECT_GT(size, 0);
    buffer.resize(size > 0 ? static_cast<std::size_t>(size) : 0);
    return buffer;
}

TEST(StringBoundsTest, LongStringIsCutInsideItsArray)
{
    for (std::size_t length : {kFrameIdSize - 2, kFrameIdSize - 1, kFrameIdSize, kFrameIdSize + 1, std::size_t{300}}) {
        HakoCpp_PointCloud2 cloud{};
        cloud.header.frame_id = std::string(length, 'f');
        cloud.height = 7;  // the field after the header: must not be overwritten
        std::vector<char> pdu = ToPdu(cloud);
        hako::pdu::msgs::sensor_msgs::PointCloud2 conv;
        HakoCpp_PointCloud2 back{};
        ASSERT_TRUE(conv.pdu2cpp(pdu.data(), back));
        const std::size_t kept = std::min(length, kFrameIdSize - 1);
        EXPECT_EQ(back.header.frame_id, std::string(kept, 'f')) << "length=" << length;
        EXPECT_EQ(back.height, 7u) << "length=" << length;
    }
}

TEST(StringBoundsTest, StringArrayElementIsCutInsideItsSlot)
{
    HakoCpp_JointState state{};
    state.name = {std::string(400, 'n'), "b"};
    std::vector<char> buffer(1 << 16);
    hako::pdu::msgs::sensor_msgs::JointState conv;
    ASSERT_GT(conv.cpp2pdu(state, buffer.data(), static_cast<int>(buffer.size())), 0);
    HakoCpp_JointState back{};
    ASSERT_TRUE(conv.pdu2cpp(buffer.data(), back));
    ASSERT_EQ(back.name.size(), 2u);
    EXPECT_LT(back.name[0].size(), static_cast<std::size_t>(HAKO_STRING_SIZE));
    EXPECT_EQ(back.name[1], "b");
}

TEST(StringBoundsTest, PduStringWithoutTerminatorIsReadToTheArrayEnd)
{
    // Another writer may fill the array to its end with no '\0'.
    HakoCpp_PointCloud2 cloud{};
    cloud.header.frame_id = "x";
    cloud.height = 9;
    std::vector<char> pdu = ToPdu(cloud);
    auto* meta = reinterpret_cast<HakoPduMetaDataType*>(pdu.data());
    char* frame_id = pdu.data() + meta->base_off + offsetof(Hako_PointCloud2, header) + offsetof(Hako_Header, frame_id);
    std::memset(frame_id, 'z', kFrameIdSize);
    hako::pdu::msgs::sensor_msgs::PointCloud2 conv;
    HakoCpp_PointCloud2 back{};
    ASSERT_TRUE(conv.pdu2cpp(pdu.data(), back));
    EXPECT_EQ(back.header.frame_id, std::string(kFrameIdSize, 'z'));
    EXPECT_EQ(back.height, 9u);
}

}  // namespace
