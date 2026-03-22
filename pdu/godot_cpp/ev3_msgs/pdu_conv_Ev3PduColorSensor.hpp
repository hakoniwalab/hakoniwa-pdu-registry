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

namespace hako::godot_pdu::ev3_msgs {

inline void binary_read_recursive_Ev3PduColorSensor(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["color"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 0);
    obj["reflect"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 4);
    obj["rgb_r"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 8);
    obj["rgb_g"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 12);
    obj["rgb_b"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 16);
}

inline godot::Dictionary pdu_to_godot_Ev3PduColorSensor(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Ev3PduColorSensor(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Ev3PduColorSensor(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 20);
    if (obj.has("color")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["color"])),
            parent_off + 0);
    }
    if (obj.has("reflect")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["reflect"])),
            parent_off + 4);
    }
    if (obj.has("rgb_r")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["rgb_r"])),
            parent_off + 8);
    }
    if (obj.has("rgb_g")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["rgb_g"])),
            parent_off + 12);
    }
    if (obj.has("rgb_b")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["rgb_b"])),
            parent_off + 16);
    }
}

inline godot::PackedByteArray godot_to_pdu_Ev3PduColorSensor(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Ev3PduColorSensor(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::ev3_msgs
