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

inline void binary_read_recursive_HakoHeartbeat(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["type"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 0);
    obj["autopilot"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 1);
    obj["base_mode"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 2);
    obj["custom_mode"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 4);
    obj["system_status"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 8);
    obj["mavlink_version"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 9);
}

inline godot::Dictionary pdu_to_godot_HakoHeartbeat(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_HakoHeartbeat(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_HakoHeartbeat(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 10);
    if (obj.has("type")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["type"])),
            parent_off + 0);
    }
    if (obj.has("autopilot")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["autopilot"])),
            parent_off + 1);
    }
    if (obj.has("base_mode")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["base_mode"])),
            parent_off + 2);
    }
    if (obj.has("custom_mode")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["custom_mode"])),
            parent_off + 4);
    }
    if (obj.has("system_status")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["system_status"])),
            parent_off + 8);
    }
    if (obj.has("mavlink_version")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["mavlink_version"])),
            parent_off + 9);
    }
}

inline godot::PackedByteArray godot_to_pdu_HakoHeartbeat(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_HakoHeartbeat(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_mavlink_msgs
