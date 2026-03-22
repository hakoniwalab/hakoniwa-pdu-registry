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

inline void binary_read_recursive_HakoHilGps(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["time_usec"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 0);
    obj["lat"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 8);
    obj["lon"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 12);
    obj["alt"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 16);
    obj["eph"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 20);
    obj["epv"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 22);
    obj["vel"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 24);
    obj["vn"] = hako::godot_runtime::read_int16(
        binary_data, base_off + 26);
    obj["ve"] = hako::godot_runtime::read_int16(
        binary_data, base_off + 28);
    obj["vd"] = hako::godot_runtime::read_int16(
        binary_data, base_off + 30);
    obj["cog"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 32);
    obj["satellites_visible"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 34);
    obj["id"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 35);
    obj["yaw"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 36);
    obj["fix_type"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 37);
}

inline godot::Dictionary pdu_to_godot_HakoHilGps(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_HakoHilGps(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_HakoHilGps(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 38);
    if (obj.has("time_usec")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["time_usec"])),
            parent_off + 0);
    }
    if (obj.has("lat")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["lat"])),
            parent_off + 8);
    }
    if (obj.has("lon")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["lon"])),
            parent_off + 12);
    }
    if (obj.has("alt")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["alt"])),
            parent_off + 16);
    }
    if (obj.has("eph")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["eph"])),
            parent_off + 20);
    }
    if (obj.has("epv")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["epv"])),
            parent_off + 22);
    }
    if (obj.has("vel")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["vel"])),
            parent_off + 24);
    }
    if (obj.has("vn")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int16(
                hako::godot_runtime::variant_to_int16(obj["vn"])),
            parent_off + 26);
    }
    if (obj.has("ve")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int16(
                hako::godot_runtime::variant_to_int16(obj["ve"])),
            parent_off + 28);
    }
    if (obj.has("vd")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int16(
                hako::godot_runtime::variant_to_int16(obj["vd"])),
            parent_off + 30);
    }
    if (obj.has("cog")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["cog"])),
            parent_off + 32);
    }
    if (obj.has("satellites_visible")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["satellites_visible"])),
            parent_off + 34);
    }
    if (obj.has("id")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["id"])),
            parent_off + 35);
    }
    if (obj.has("yaw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["yaw"])),
            parent_off + 36);
    }
    if (obj.has("fix_type")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["fix_type"])),
            parent_off + 37);
    }
}

inline godot::PackedByteArray godot_to_pdu_HakoHilGps(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_HakoHilGps(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_mavlink_msgs
