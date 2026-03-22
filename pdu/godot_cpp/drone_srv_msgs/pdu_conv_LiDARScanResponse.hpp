#pragma once

#include <algorithm>

#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/variant/packed_float64_array.hpp>
#include <godot_cpp/variant/packed_int32_array.hpp>
#include <godot_cpp/variant/packed_int64_array.hpp>

#include "godot_cpp_runtime/PduRuntime.hpp"
#include "sensor_msgs/pdu_conv_PointCloud2.hpp"
#include "geometry_msgs/pdu_conv_Pose.hpp"

namespace hako::godot_pdu::drone_srv_msgs {

inline void binary_read_recursive_LiDARScanResponse(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["ok"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 0);
    {
        godot::Dictionary child;
        hako::godot_pdu::sensor_msgs::binary_read_recursive_PointCloud2(
            meta, binary_data, child, base_off + 4);
        obj["point_cloud"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Pose(
            meta, binary_data, child, base_off + 184);
        obj["lidar_pose"] = child;
    }
    obj["message"] = hako::godot_runtime::read_string(
        binary_data, base_off + 240, 128);
}

inline godot::Dictionary pdu_to_godot_LiDARScanResponse(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_LiDARScanResponse(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_LiDARScanResponse(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 368);
    if (obj.has("ok")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["ok"])),
            parent_off + 0);
    }
    if (obj.has("point_cloud")) {
        hako::godot_pdu::sensor_msgs::binary_write_recursive_PointCloud2(
            parent_off + 4,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["point_cloud"]));
    }
    if (obj.has("lidar_pose")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Pose(
            parent_off + 184,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["lidar_pose"]));
    }
    if (obj.has("message")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["message"]), 128),
            parent_off + 240);
    }
}

inline godot::PackedByteArray godot_to_pdu_LiDARScanResponse(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_LiDARScanResponse(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::drone_srv_msgs
