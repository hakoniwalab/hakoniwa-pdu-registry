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
#include "geometry_msgs/pdu_conv_Point.hpp"
#include "geometry_msgs/pdu_conv_Quaternion.hpp"

namespace hako::godot_pdu::geometry_msgs {

inline void binary_read_recursive_Pose(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Point(
            meta, binary_data, child, base_off + 0);
        obj["position"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Quaternion(
            meta, binary_data, child, base_off + 24);
        obj["orientation"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_Pose(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Pose(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Pose(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 56);
    if (obj.has("position")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Point(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["position"]));
    }
    if (obj.has("orientation")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Quaternion(
            parent_off + 24,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["orientation"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_Pose(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Pose(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::geometry_msgs
