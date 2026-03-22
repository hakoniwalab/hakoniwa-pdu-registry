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

namespace hako::godot_pdu::sensor_msgs {

inline void binary_read_recursive_RegionOfInterest(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["x_offset"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 0);
    obj["y_offset"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 4);
    obj["height"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 8);
    obj["width"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 12);
    obj["do_rectify"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 16);
}

inline godot::Dictionary pdu_to_godot_RegionOfInterest(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_RegionOfInterest(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_RegionOfInterest(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 20);
    if (obj.has("x_offset")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["x_offset"])),
            parent_off + 0);
    }
    if (obj.has("y_offset")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["y_offset"])),
            parent_off + 4);
    }
    if (obj.has("height")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["height"])),
            parent_off + 8);
    }
    if (obj.has("width")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["width"])),
            parent_off + 12);
    }
    if (obj.has("do_rectify")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["do_rectify"])),
            parent_off + 16);
    }
}

inline godot::PackedByteArray godot_to_pdu_RegionOfInterest(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_RegionOfInterest(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::sensor_msgs
