// The ROS 2 <-> PDU converters (pdu_ctype_conv_*.hpp), built only where the ROS 2
// message packages are found: the same messages as cpp2pdu_cases.hpp, as ROS 2
// messages, give byte for byte the golden PDUs of the old converters, through
// both hako_convert_ros2pdu_<T>() (an allocated PDU) and
// hako_convert_ros2pdu_into_<T>() (the caller's buffer); a reused destination
// equals a fresh one; long strings stay inside their arrays.
#include <gtest/gtest.h>

#include <cstring>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "sensor_msgs/pdu_ctype_conv_JointState.hpp"
#include "sensor_msgs/pdu_ctype_conv_PointCloud2.hpp"
#include "std_msgs/pdu_ctype_conv_Float64MultiArray.hpp"
#include "trajectory_msgs/pdu_ctype_conv_JointTrajectory.hpp"

#ifndef CPP2PDU_GOLDEN_DIR
#error "CPP2PDU_GOLDEN_DIR must name tests/fixtures/cpp2pdu_golden"
#endif

namespace {

std::vector<char> ReadFile(const std::string& path)
{
    std::ifstream in(path, std::ios::binary);
    return std::vector<char>(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
}

sensor_msgs::msg::PointCloud2 Cloud(std::size_t bytes)
{
    sensor_msgs::msg::PointCloud2 cloud;
    cloud.header.stamp.sec = 12;
    cloud.header.stamp.nanosec = 345;
    cloud.header.frame_id = "overhead_lidar";
    const char* names[] = {"x", "y", "z"};
    for (int i = 0; i < 3; ++i) {
        sensor_msgs::msg::PointField field;
        field.name = names[i];
        field.offset = 4 * i;
        field.datatype = 7;
        field.count = 1;
        cloud.fields.push_back(field);
    }
    cloud.height = 1;
    cloud.width = static_cast<uint32_t>(bytes / 12);
    cloud.point_step = 12;
    cloud.row_step = static_cast<uint32_t>(bytes);
    cloud.data.resize(bytes);
    for (std::size_t i = 0; i < bytes; ++i) {
        cloud.data[i] = static_cast<uint8_t>((i * 31u + 7u) & 0xffu);
    }
    cloud.is_dense = true;
    return cloud;
}

sensor_msgs::msg::JointState Joints()
{
    sensor_msgs::msg::JointState state;
    state.header.frame_id = "base_link";
    state.name = {"shoulder_pan", "shoulder_lift", "elbow_flex"};
    state.position = {0.1, -0.2, 0.3};
    state.velocity = {1.0, 2.0};
    return state;
}

std_msgs::msg::Float64MultiArray Matrix()
{
    std_msgs::msg::Float64MultiArray array;
    std_msgs::msg::MultiArrayDimension dim;
    dim.label = "rows";
    dim.size = 2;
    dim.stride = 6;
    array.layout.dim.push_back(dim);
    dim.label = "cols";
    dim.size = 3;
    dim.stride = 3;
    array.layout.dim.push_back(dim);
    array.data = {1, 2, 3, 4, 5, 6};
    return array;
}

trajectory_msgs::msg::JointTrajectory Trajectory(int points, int values)
{
    trajectory_msgs::msg::JointTrajectory trajectory;
    trajectory.header.frame_id = "world";
    for (int j = 0; j < values; ++j) {
        trajectory.joint_names.push_back("joint_" + std::to_string(j));
    }
    for (int p = 0; p < points; ++p) {
        trajectory_msgs::msg::JointTrajectoryPoint point;
        for (int j = 0; j < values; ++j) {
            point.positions.push_back(0.5 * p + 0.1 * j);
        }
        for (int j = 0; j + 1 < values; ++j) {
            point.velocities.push_back(-0.25 * j);
        }
        point.time_from_start.sec = p + 1;
        trajectory.points.push_back(point);
    }
    return trajectory;
}

// Both ways of making the PDU must give the golden bytes.
template <typename MsgT, typename HakoT, typename AllocFn, typename IntoFn>
void ExpectGolden(const std::string& name, MsgT msg, AllocFn alloc, IntoFn into)
{
    const std::vector<char> golden = ReadFile(std::string(CPP2PDU_GOLDEN_DIR) + "/" + name + ".bin");
    ASSERT_FALSE(golden.empty()) << name;

    HakoT* base = nullptr;
    const int size = alloc(msg, &base);
    ASSERT_EQ(size, static_cast<int>(golden.size())) << name;
    const char* top = static_cast<const char*>(hako_get_top_ptr_pdu(base));
    EXPECT_EQ(0, std::memcmp(top, golden.data(), golden.size())) << name << " (allocated)";
    hako_destroy_pdu(base);

    std::vector<char> buffer(golden.size() + 3, static_cast<char>(0xab));
    char* out = buffer.data() + 1;  // unaligned
    ASSERT_EQ(static_cast<int>(golden.size()), into(msg, out, static_cast<int>(golden.size()))) << name;
    EXPECT_EQ(0, std::memcmp(out, golden.data(), golden.size())) << name << " (into)";
}

TEST(Ros2PduTest, SameBytesAsTheGoldenPdus)
{
    for (std::size_t bytes : {std::size_t{0}, std::size_t{12}, std::size_t{1001}}) {
        ExpectGolden<sensor_msgs::msg::PointCloud2, Hako_PointCloud2>(
            "point_cloud2_" + std::to_string(bytes), Cloud(bytes),
            hako_convert_ros2pdu_PointCloud2, hako_convert_ros2pdu_into_PointCloud2);
    }
    ExpectGolden<sensor_msgs::msg::JointState, Hako_JointState>(
        "joint_state", Joints(), hako_convert_ros2pdu_JointState, hako_convert_ros2pdu_into_JointState);
    ExpectGolden<std_msgs::msg::Float64MultiArray, Hako_Float64MultiArray>(
        "float64_multi_array", Matrix(), hako_convert_ros2pdu_Float64MultiArray,
        hako_convert_ros2pdu_into_Float64MultiArray);
    for (int points = 0; points <= 2; ++points) {
        for (int values = 0; values <= 2; ++values) {
            ExpectGolden<trajectory_msgs::msg::JointTrajectory, Hako_JointTrajectory>(
                "joint_trajectory_p" + std::to_string(points) + "_v" + std::to_string(values),
                Trajectory(points, values), hako_convert_ros2pdu_JointTrajectory,
                hako_convert_ros2pdu_into_JointTrajectory);
        }
    }
}

sensor_msgs::msg::PointCloud2 Back(const std::vector<char>& pdu, sensor_msgs::msg::PointCloud2& dst)
{
    auto* base = static_cast<Hako_PointCloud2*>(hako_get_base_ptr_pdu(const_cast<char*>(pdu.data())));
    EXPECT_NE(base, nullptr);
    EXPECT_EQ(0, hako_convert_pdu2ros_PointCloud2(*base, dst));
    return dst;
}

TEST(Ros2PduTest, ReusedDestinationEqualsFreshAndRoundTrips)
{
    sensor_msgs::msg::PointCloud2 reused;
    for (std::size_t bytes : {std::size_t{1200}, std::size_t{0}, std::size_t{36}}) {
        sensor_msgs::msg::PointCloud2 cloud = Cloud(bytes);
        if (bytes == 0) {
            cloud.fields.clear();
        }
        std::vector<char> pdu(bytes + 4096);
        const int size = hako_convert_ros2pdu_into_PointCloud2(cloud, pdu.data(), static_cast<int>(pdu.size()));
        ASSERT_GT(size, 0);
        sensor_msgs::msg::PointCloud2 fresh;
        Back(pdu, fresh);
        Back(pdu, reused);
        EXPECT_EQ(fresh, cloud) << "bytes=" << bytes;
        EXPECT_EQ(reused, cloud) << "bytes=" << bytes;
    }
}

TEST(Ros2PduTest, LongStringsStayInsideTheirArrays)
{
    sensor_msgs::msg::JointState state = Joints();
    state.header.frame_id = std::string(300, 'f');
    state.name = {std::string(400, 'n'), "b"};
    std::vector<char> pdu(1 << 16);
    ASSERT_GT(hako_convert_ros2pdu_into_JointState(state, pdu.data(), static_cast<int>(pdu.size())), 0);
    auto* base = static_cast<Hako_JointState*>(hako_get_base_ptr_pdu(pdu.data()));
    sensor_msgs::msg::JointState back;
    ASSERT_EQ(0, hako_convert_pdu2ros_JointState(*base, back));
    EXPECT_EQ(back.header.frame_id, std::string(M_SIZE(Hako_Header, frame_id) - 1, 'f'));
    ASSERT_EQ(back.name.size(), 2u);
    EXPECT_EQ(back.name[1], "b");
    EXPECT_EQ(back.position, state.position);
}

}  // namespace
