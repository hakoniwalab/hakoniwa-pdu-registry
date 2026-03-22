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
#include "std_msgs/pdu_conv_Header.hpp"

namespace hako::godot_pdu::sensor_msgs {

inline void binary_read_recursive_JointState(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::std_msgs::binary_read_recursive_Header(
            meta, binary_data, child, base_off + 0);
        obj["header"] = child;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 136);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 136 + 4);
        godot::Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_string(
                binary_data, meta.heap_off + offset_from_heap + (i * 128), 128));
        }
        obj["name"] = values;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 144);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 144 + 4);
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, meta.heap_off + offset_from_heap + (i * 8)));
        }
        obj["position"] = values;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 152);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 152 + 4);
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, meta.heap_off + offset_from_heap + (i * 8)));
        }
        obj["velocity"] = values;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 160);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 160 + 4);
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, meta.heap_off + offset_from_heap + (i * 8)));
        }
        obj["effort"] = values;
    }
}

inline godot::Dictionary pdu_to_godot_JointState(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_JointState(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_JointState(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 168);
    if (obj.has("header")) {
        hako::godot_pdu::std_msgs::binary_write_recursive_Header(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("name")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["name"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 136);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 136 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_string(hako::godot_runtime::variant_to_string(values[i]), 128));
        }
    }
    if (obj.has("position")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["position"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 144);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 144 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]));
        }
    }
    if (obj.has("velocity")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["velocity"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 152);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 152 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]));
        }
    }
    if (obj.has("effort")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["effort"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 160);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 160 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]));
        }
    }
}

inline godot::PackedByteArray godot_to_pdu_JointState(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_JointState(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::sensor_msgs
