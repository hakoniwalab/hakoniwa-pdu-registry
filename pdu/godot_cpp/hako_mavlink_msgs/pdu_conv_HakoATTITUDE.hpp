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

namespace hako::godot_pdu::hako_mavlink_msgs {

inline void binary_read_recursive_HakoATTITUDE(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["time_boot_ms"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 0);
    obj["roll"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 4);
    obj["pitch"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 8);
    obj["yaw"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 12);
    obj["rollspeed"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 16);
    obj["pitchspeed"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 20);
    obj["yawspeed"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 24);
}

inline godot::Dictionary pdu_to_godot_HakoATTITUDE(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_HakoATTITUDE(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_HakoATTITUDE(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 28);
    if (obj.has("time_boot_ms")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["time_boot_ms"])),
            parent_off + 0);
    }
    if (obj.has("roll")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["roll"])),
            parent_off + 4);
    }
    if (obj.has("pitch")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["pitch"])),
            parent_off + 8);
    }
    if (obj.has("yaw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["yaw"])),
            parent_off + 12);
    }
    if (obj.has("rollspeed")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["rollspeed"])),
            parent_off + 16);
    }
    if (obj.has("pitchspeed")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["pitchspeed"])),
            parent_off + 20);
    }
    if (obj.has("yawspeed")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["yawspeed"])),
            parent_off + 24);
    }
}

inline godot::PackedByteArray godot_to_pdu_HakoATTITUDE(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_HakoATTITUDE(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_mavlink_msgs
