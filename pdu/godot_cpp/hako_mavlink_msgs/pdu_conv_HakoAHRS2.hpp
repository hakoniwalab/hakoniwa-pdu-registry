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

inline void binary_read_recursive_HakoAHRS2(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["roll"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 0);
    obj["pitch"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 4);
    obj["yaw"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 8);
    obj["altitude"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 12);
    obj["lat"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 16);
    obj["lng"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 20);
}

inline godot::Dictionary pdu_to_godot_HakoAHRS2(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_HakoAHRS2(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_HakoAHRS2(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 24);
    if (obj.has("roll")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["roll"])),
            parent_off + 0);
    }
    if (obj.has("pitch")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["pitch"])),
            parent_off + 4);
    }
    if (obj.has("yaw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["yaw"])),
            parent_off + 8);
    }
    if (obj.has("altitude")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["altitude"])),
            parent_off + 12);
    }
    if (obj.has("lat")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["lat"])),
            parent_off + 16);
    }
    if (obj.has("lng")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["lng"])),
            parent_off + 20);
    }
}

inline godot::PackedByteArray godot_to_pdu_HakoAHRS2(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_HakoAHRS2(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_mavlink_msgs
