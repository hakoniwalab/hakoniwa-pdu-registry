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

inline void binary_read_recursive_HakoHilActuatorControls(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["time_usec"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 0);
    {
        godot::PackedFloat32Array values;
        for (int32_t i = 0; i < 16; ++i) {
            values.append(hako::godot_runtime::read_float32(
                binary_data, base_off + 8 + (i * 4)));
        }
        obj["controls"] = values;
    }
    obj["mode"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 72);
    obj["flags"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 80);
}

inline godot::Dictionary pdu_to_godot_HakoHilActuatorControls(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_HakoHilActuatorControls(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_HakoHilActuatorControls(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 88);
    if (obj.has("time_usec")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["time_usec"])),
            parent_off + 0);
    }
    if (obj.has("controls")) {
        godot::PackedFloat32Array values = hako::godot_runtime::variant_to_packed_float32_array(obj["controls"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 16);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_float32(values[i]),
                parent_off + 8 + (i * 4));
        }
    }
    if (obj.has("mode")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["mode"])),
            parent_off + 72);
    }
    if (obj.has("flags")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["flags"])),
            parent_off + 80);
    }
}

inline godot::PackedByteArray godot_to_pdu_HakoHilActuatorControls(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_HakoHilActuatorControls(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_mavlink_msgs
