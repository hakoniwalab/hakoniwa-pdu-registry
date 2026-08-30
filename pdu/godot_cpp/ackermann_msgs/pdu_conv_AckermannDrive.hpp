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

namespace hako::godot_pdu::ackermann_msgs {

inline void binary_read_recursive_AckermannDrive(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["steering_angle"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 0);
    obj["steering_angle_velocity"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 4);
    obj["speed"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 8);
    obj["acceleration"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 12);
    obj["jerk"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 16);
}

inline godot::Dictionary pdu_to_godot_AckermannDrive(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_AckermannDrive(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_AckermannDrive(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 20);
    if (obj.has("steering_angle")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["steering_angle"])),
            parent_off + 0);
    }
    if (obj.has("steering_angle_velocity")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["steering_angle_velocity"])),
            parent_off + 4);
    }
    if (obj.has("speed")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["speed"])),
            parent_off + 8);
    }
    if (obj.has("acceleration")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["acceleration"])),
            parent_off + 12);
    }
    if (obj.has("jerk")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["jerk"])),
            parent_off + 16);
    }
}

inline godot::PackedByteArray godot_to_pdu_AckermannDrive(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_AckermannDrive(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::ackermann_msgs
