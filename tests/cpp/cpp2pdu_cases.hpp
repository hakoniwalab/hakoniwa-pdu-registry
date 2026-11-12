// The messages the cpp2pdu golden files are made from (cpp2pdu_golden_dump.cpp)
// and checked against (cpp2pdu_golden_test.cpp): every one a fixed value, so
// the same source gives the same PDU.
#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "sensor_msgs/pdu_cpptype_conv_JointState.hpp"
#include "sensor_msgs/pdu_cpptype_conv_PointCloud2.hpp"
#include "std_msgs/pdu_cpptype_conv_Float64MultiArray.hpp"
#include "trajectory_msgs/pdu_cpptype_conv_JointTrajectory.hpp"

namespace cpp2pdu_cases {

inline HakoCpp_PointCloud2 Cloud(std::size_t bytes)
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

inline HakoCpp_JointState Joints()
{
    HakoCpp_JointState state{};
    state.header.frame_id = "base_link";
    state.name = {"shoulder_pan", "shoulder_lift", "elbow_flex"};
    state.position = {0.1, -0.2, 0.3};
    state.velocity = {1.0, 2.0};
    return state;
}

inline HakoCpp_Float64MultiArray Matrix()
{
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
    array.data = {1, 2, 3, 4, 5, 6};
    return array;
}

// A struct array (points) whose elements hold variable arrays: `points`
// points, each with `values` positions, values - 1 velocities (none when 0).
inline HakoCpp_JointTrajectory Trajectory(int points, int values)
{
    HakoCpp_JointTrajectory trajectory{};
    trajectory.header.frame_id = "world";
    for (int j = 0; j < values; ++j) {
        trajectory.joint_names.push_back("joint_" + std::to_string(j));
    }
    for (int p = 0; p < points; ++p) {
        HakoCpp_JointTrajectoryPoint point{};
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

template <typename ConverterT, typename CppT>
std::vector<char> Pdu(CppT src, std::size_t capacity)
{
    std::vector<char> buffer(capacity, 0);
    ConverterT conv;
    const int size = conv.cpp2pdu(src, buffer.data(), static_cast<int>(buffer.size()));
    buffer.resize(size > 0 ? static_cast<std::size_t>(size) : 0);
    return buffer;
}

struct Case {
    std::string name;
    std::function<std::vector<char>()> make;
};

inline std::vector<Case> All()
{
    namespace sm = hako::pdu::msgs::sensor_msgs;
    std::vector<Case> cases = {
        {"point_cloud2_0", [] { return Pdu<sm::PointCloud2>(Cloud(0), 1 << 16); }},
        {"point_cloud2_12", [] { return Pdu<sm::PointCloud2>(Cloud(12), 1 << 16); }},
        {"point_cloud2_1001", [] { return Pdu<sm::PointCloud2>(Cloud(1001), 1 << 16); }},
        {"joint_state", [] { return Pdu<sm::JointState>(Joints(), 1 << 16); }},
        {"float64_multi_array", [] { return Pdu<hako::pdu::msgs::std_msgs::Float64MultiArray>(Matrix(), 1 << 16); }},
    };
    for (int points = 0; points <= 2; ++points) {
        for (int values = 0; values <= 2; ++values) {
            cases.push_back({"joint_trajectory_p" + std::to_string(points) + "_v" + std::to_string(values),
                             [points, values] {
                                 return Pdu<hako::pdu::msgs::trajectory_msgs::JointTrajectory>(
                                     Trajectory(points, values), 1 << 16);
                             }});
        }
    }
    return cases;
}

}  // namespace cpp2pdu_cases
