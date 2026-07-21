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
#include "geometry_msgs/pdu_conv_Transform.hpp"
#include "geometry_msgs/pdu_conv_Twist.hpp"
#include "builtin_interfaces/pdu_conv_Duration.hpp"

namespace hako::godot_pdu::trajectory_msgs {

inline void binary_read_recursive_MultiDOFJointTrajectoryPoint(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 0);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 0 + 4);
        godot::Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::geometry_msgs::binary_read_recursive_Transform(
                meta, binary_data, child, meta.heap_off + offset_from_heap + (i * 56));
            values.append(child);
        }
        obj["transforms"] = values;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 8);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 8 + 4);
        godot::Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::geometry_msgs::binary_read_recursive_Twist(
                meta, binary_data, child, meta.heap_off + offset_from_heap + (i * 48));
            values.append(child);
        }
        obj["velocities"] = values;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 16);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 16 + 4);
        godot::Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::geometry_msgs::binary_read_recursive_Twist(
                meta, binary_data, child, meta.heap_off + offset_from_heap + (i * 48));
            values.append(child);
        }
        obj["accelerations"] = values;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::builtin_interfaces::binary_read_recursive_Duration(
            meta, binary_data, child, base_off + 24);
        obj["time_from_start"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_MultiDOFJointTrajectoryPoint(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_MultiDOFJointTrajectoryPoint(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_MultiDOFJointTrajectoryPoint(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 32);
    if (obj.has("transforms")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["transforms"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 0);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 0 + 4);
        writer.heap_allocator.add(hako::godot_runtime::zero_bytes(array_size * 56), offset_from_heap);
        for (int32_t i = 0; i < array_size; ++i) {
            hako::godot_pdu::geometry_msgs::binary_write_recursive_Transform(
                offset_from_heap + (i * 56),
                writer,
                writer.heap_allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
    if (obj.has("velocities")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["velocities"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 8);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 8 + 4);
        writer.heap_allocator.add(hako::godot_runtime::zero_bytes(array_size * 48), offset_from_heap);
        for (int32_t i = 0; i < array_size; ++i) {
            hako::godot_pdu::geometry_msgs::binary_write_recursive_Twist(
                offset_from_heap + (i * 48),
                writer,
                writer.heap_allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
    if (obj.has("accelerations")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["accelerations"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 16);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 16 + 4);
        writer.heap_allocator.add(hako::godot_runtime::zero_bytes(array_size * 48), offset_from_heap);
        for (int32_t i = 0; i < array_size; ++i) {
            hako::godot_pdu::geometry_msgs::binary_write_recursive_Twist(
                offset_from_heap + (i * 48),
                writer,
                writer.heap_allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
    if (obj.has("time_from_start")) {
        hako::godot_pdu::builtin_interfaces::binary_write_recursive_Duration(
            parent_off + 24,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["time_from_start"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_MultiDOFJointTrajectoryPoint(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_MultiDOFJointTrajectoryPoint(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::trajectory_msgs
