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

namespace hako::godot_pdu::geometry_msgs {

inline void binary_read_recursive_Quaternion(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["x"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 0);
    obj["y"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 8);
    obj["z"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 16);
    obj["w"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 24);
}

inline godot::Dictionary pdu_to_godot_Quaternion(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Quaternion(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Quaternion(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 32);
    if (obj.has("x")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["x"])),
            parent_off + 0);
    }
    if (obj.has("y")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["y"])),
            parent_off + 8);
    }
    if (obj.has("z")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["z"])),
            parent_off + 16);
    }
    if (obj.has("w")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["w"])),
            parent_off + 24);
    }
}

inline godot::PackedByteArray godot_to_pdu_Quaternion(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Quaternion(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::geometry_msgs
