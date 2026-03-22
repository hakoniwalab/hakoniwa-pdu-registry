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
#include "std_msgs/pdu_conv_Header.hpp"
#include "geometry_msgs/pdu_conv_PoseWithCovariance.hpp"
#include "geometry_msgs/pdu_conv_TwistWithCovariance.hpp"

namespace hako::godot_pdu::nav_msgs {

inline void binary_read_recursive_Odometry(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::std_msgs::binary_read_recursive_Header(
            meta, binary_data, child, base_off + 0);
        obj["header"] = child;
    }
    obj["child_frame_id"] = hako::godot_runtime::read_string(
        binary_data, base_off + 136, 128);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_PoseWithCovariance(
            meta, binary_data, child, base_off + 264);
        obj["pose"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_TwistWithCovariance(
            meta, binary_data, child, base_off + 608);
        obj["twist"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_Odometry(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Odometry(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Odometry(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 944);
    if (obj.has("header")) {
        hako::godot_pdu::std_msgs::binary_write_recursive_Header(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("child_frame_id")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["child_frame_id"]), 128),
            parent_off + 136);
    }
    if (obj.has("pose")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_PoseWithCovariance(
            parent_off + 264,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["pose"]));
    }
    if (obj.has("twist")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_TwistWithCovariance(
            parent_off + 608,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["twist"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_Odometry(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Odometry(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::nav_msgs
