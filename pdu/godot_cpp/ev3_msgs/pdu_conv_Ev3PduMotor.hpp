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

inline void binary_read_recursive_Ev3PduMotor(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["power"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 0);
    obj["stop"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 4);
    obj["reset_angle"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 8);
}

inline godot::Dictionary pdu_to_godot_Ev3PduMotor(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Ev3PduMotor(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Ev3PduMotor(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 12);
    if (obj.has("power")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["power"])),
            parent_off + 0);
    }
    if (obj.has("stop")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["stop"])),
            parent_off + 4);
    }
    if (obj.has("reset_angle")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["reset_angle"])),
            parent_off + 8);
    }
}

inline godot::PackedByteArray godot_to_pdu_Ev3PduMotor(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Ev3PduMotor(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::ev3_msgs
