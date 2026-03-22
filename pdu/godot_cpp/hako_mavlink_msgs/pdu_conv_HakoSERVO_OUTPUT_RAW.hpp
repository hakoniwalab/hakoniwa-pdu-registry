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

inline void binary_read_recursive_HakoSERVO_OUTPUT_RAW(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["time_usec"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 0);
    obj["port"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 4);
    obj["servo1_raw"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 6);
    obj["servo2_raw"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 8);
    obj["servo3_raw"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 10);
    obj["servo4_raw"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 12);
    obj["servo5_raw"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 14);
    obj["servo6_raw"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 16);
    obj["servo7_raw"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 18);
    obj["servo8_raw"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 20);
}

inline godot::Dictionary pdu_to_godot_HakoSERVO_OUTPUT_RAW(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_HakoSERVO_OUTPUT_RAW(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_HakoSERVO_OUTPUT_RAW(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 22);
    if (obj.has("time_usec")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["time_usec"])),
            parent_off + 0);
    }
    if (obj.has("port")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["port"])),
            parent_off + 4);
    }
    if (obj.has("servo1_raw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["servo1_raw"])),
            parent_off + 6);
    }
    if (obj.has("servo2_raw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["servo2_raw"])),
            parent_off + 8);
    }
    if (obj.has("servo3_raw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["servo3_raw"])),
            parent_off + 10);
    }
    if (obj.has("servo4_raw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["servo4_raw"])),
            parent_off + 12);
    }
    if (obj.has("servo5_raw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["servo5_raw"])),
            parent_off + 14);
    }
    if (obj.has("servo6_raw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["servo6_raw"])),
            parent_off + 16);
    }
    if (obj.has("servo7_raw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["servo7_raw"])),
            parent_off + 18);
    }
    if (obj.has("servo8_raw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["servo8_raw"])),
            parent_off + 20);
    }
}

inline godot::PackedByteArray godot_to_pdu_HakoSERVO_OUTPUT_RAW(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_HakoSERVO_OUTPUT_RAW(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_mavlink_msgs
