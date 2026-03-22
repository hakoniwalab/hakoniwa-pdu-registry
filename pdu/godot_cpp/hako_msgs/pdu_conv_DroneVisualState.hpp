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

namespace hako::godot_pdu::hako_msgs {

inline void binary_read_recursive_DroneVisualState(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["x"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 0);
    obj["y"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 4);
    obj["z"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 8);
    obj["roll"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 12);
    obj["pitch"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 16);
    obj["yaw"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 20);
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 24);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 24 + 4);
        godot::PackedFloat32Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float32(
                binary_data, meta.heap_off + offset_from_heap + (i * 4)));
        }
        obj["pwm_duty"] = values;
    }
}

inline godot::Dictionary pdu_to_godot_DroneVisualState(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_DroneVisualState(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_DroneVisualState(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 28);
    if (obj.has("x")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["x"])),
            parent_off + 0);
    }
    if (obj.has("y")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["y"])),
            parent_off + 4);
    }
    if (obj.has("z")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["z"])),
            parent_off + 8);
    }
    if (obj.has("roll")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["roll"])),
            parent_off + 12);
    }
    if (obj.has("pitch")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["pitch"])),
            parent_off + 16);
    }
    if (obj.has("yaw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["yaw"])),
            parent_off + 20);
    }
    if (obj.has("pwm_duty")) {
        godot::PackedFloat32Array values = hako::godot_runtime::variant_to_packed_float32_array(obj["pwm_duty"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 24);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 24 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float32(values[i]));
        }
    }
}

inline godot::PackedByteArray godot_to_pdu_DroneVisualState(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_DroneVisualState(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
