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
#include "builtin_interfaces/pdu_conv_Time.hpp"
#include "geometry_msgs/pdu_conv_Pose.hpp"

namespace hako::godot_pdu::nav_msgs {

inline void binary_read_recursive_MapMetaData(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::builtin_interfaces::binary_read_recursive_Time(
            meta, binary_data, child, base_off + 0);
        obj["map_load_time"] = child;
    }
    obj["resolution"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 8);
    obj["width"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 12);
    obj["height"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 16);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Pose(
            meta, binary_data, child, base_off + 24);
        obj["origin"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_MapMetaData(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_MapMetaData(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_MapMetaData(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 80);
    if (obj.has("map_load_time")) {
        hako::godot_pdu::builtin_interfaces::binary_write_recursive_Time(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["map_load_time"]));
    }
    if (obj.has("resolution")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["resolution"])),
            parent_off + 8);
    }
    if (obj.has("width")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["width"])),
            parent_off + 12);
    }
    if (obj.has("height")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["height"])),
            parent_off + 16);
    }
    if (obj.has("origin")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Pose(
            parent_off + 24,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["origin"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_MapMetaData(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_MapMetaData(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::nav_msgs
