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
#include "builtin_interfaces/pdu_conv_Duration.hpp"

namespace hako::godot_pdu::trajectory_msgs {

inline void binary_read_recursive_JointTrajectoryPoint(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 0);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 0 + 4);
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, meta.heap_off + offset_from_heap + (i * 8)));
        }
        obj["positions"] = values;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 8);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 8 + 4);
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, meta.heap_off + offset_from_heap + (i * 8)));
        }
        obj["velocities"] = values;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 16);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 16 + 4);
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, meta.heap_off + offset_from_heap + (i * 8)));
        }
        obj["accelerations"] = values;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 24);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 24 + 4);
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, meta.heap_off + offset_from_heap + (i * 8)));
        }
        obj["effort"] = values;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::builtin_interfaces::binary_read_recursive_Duration(
            meta, binary_data, child, base_off + 32);
        obj["time_from_start"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_JointTrajectoryPoint(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_JointTrajectoryPoint(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_JointTrajectoryPoint(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 40);
    if (obj.has("positions")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["positions"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 0);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 0 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]));
        }
    }
    if (obj.has("velocities")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["velocities"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 8);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 8 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]));
        }
    }
    if (obj.has("accelerations")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["accelerations"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 16);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 16 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]));
        }
    }
    if (obj.has("effort")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["effort"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 24);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 24 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]));
        }
    }
    if (obj.has("time_from_start")) {
        hako::godot_pdu::builtin_interfaces::binary_write_recursive_Duration(
            parent_off + 32,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["time_from_start"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_JointTrajectoryPoint(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_JointTrajectoryPoint(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::trajectory_msgs
