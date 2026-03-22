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

inline void binary_read_recursive_HakoGLOBAL_POSITION_INT(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["time_boot_ms"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 0);
    obj["lat"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 4);
    obj["lon"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 8);
    obj["alt"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 12);
    obj["relative_alt"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 16);
    obj["vx"] = hako::godot_runtime::read_int16(
        binary_data, base_off + 20);
    obj["vy"] = hako::godot_runtime::read_int16(
        binary_data, base_off + 22);
    obj["vz"] = hako::godot_runtime::read_int16(
        binary_data, base_off + 24);
    obj["hdg"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 26);
}

inline godot::Dictionary pdu_to_godot_HakoGLOBAL_POSITION_INT(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_HakoGLOBAL_POSITION_INT(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_HakoGLOBAL_POSITION_INT(
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
    if (obj.has("lat")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["lat"])),
            parent_off + 4);
    }
    if (obj.has("lon")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["lon"])),
            parent_off + 8);
    }
    if (obj.has("alt")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["alt"])),
            parent_off + 12);
    }
    if (obj.has("relative_alt")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["relative_alt"])),
            parent_off + 16);
    }
    if (obj.has("vx")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int16(
                hako::godot_runtime::variant_to_int16(obj["vx"])),
            parent_off + 20);
    }
    if (obj.has("vy")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int16(
                hako::godot_runtime::variant_to_int16(obj["vy"])),
            parent_off + 22);
    }
    if (obj.has("vz")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int16(
                hako::godot_runtime::variant_to_int16(obj["vz"])),
            parent_off + 24);
    }
    if (obj.has("hdg")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["hdg"])),
            parent_off + 26);
    }
}

inline godot::PackedByteArray godot_to_pdu_HakoGLOBAL_POSITION_INT(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_HakoGLOBAL_POSITION_INT(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_mavlink_msgs
