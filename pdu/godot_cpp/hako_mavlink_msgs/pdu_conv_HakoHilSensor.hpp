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

inline void binary_read_recursive_HakoHilSensor(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["time_usec"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 0);
    obj["xacc"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 8);
    obj["yacc"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 12);
    obj["zacc"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 16);
    obj["xgyro"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 20);
    obj["ygyro"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 24);
    obj["zgyro"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 28);
    obj["xmag"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 32);
    obj["ymag"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 36);
    obj["zmag"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 40);
    obj["abs_pressure"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 44);
    obj["diff_pressure"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 48);
    obj["pressure_alt"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 52);
    obj["temperature"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 56);
    obj["fields_updated"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 60);
    obj["id"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 64);
}

inline godot::Dictionary pdu_to_godot_HakoHilSensor(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_HakoHilSensor(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_HakoHilSensor(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 65);
    if (obj.has("time_usec")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["time_usec"])),
            parent_off + 0);
    }
    if (obj.has("xacc")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["xacc"])),
            parent_off + 8);
    }
    if (obj.has("yacc")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["yacc"])),
            parent_off + 12);
    }
    if (obj.has("zacc")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["zacc"])),
            parent_off + 16);
    }
    if (obj.has("xgyro")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["xgyro"])),
            parent_off + 20);
    }
    if (obj.has("ygyro")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["ygyro"])),
            parent_off + 24);
    }
    if (obj.has("zgyro")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["zgyro"])),
            parent_off + 28);
    }
    if (obj.has("xmag")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["xmag"])),
            parent_off + 32);
    }
    if (obj.has("ymag")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["ymag"])),
            parent_off + 36);
    }
    if (obj.has("zmag")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["zmag"])),
            parent_off + 40);
    }
    if (obj.has("abs_pressure")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["abs_pressure"])),
            parent_off + 44);
    }
    if (obj.has("diff_pressure")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["diff_pressure"])),
            parent_off + 48);
    }
    if (obj.has("pressure_alt")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["pressure_alt"])),
            parent_off + 52);
    }
    if (obj.has("temperature")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["temperature"])),
            parent_off + 56);
    }
    if (obj.has("fields_updated")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["fields_updated"])),
            parent_off + 60);
    }
    if (obj.has("id")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["id"])),
            parent_off + 64);
    }
}

inline godot::PackedByteArray godot_to_pdu_HakoHilSensor(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_HakoHilSensor(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_mavlink_msgs
