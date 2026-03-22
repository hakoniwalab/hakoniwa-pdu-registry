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
#include "hako_msgs/pdu_conv_SimpleVarray.hpp"

namespace hako::godot_pdu::hako_msgs {

inline void binary_read_recursive_SimpleStructVarray(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["aaa"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 0);
    {
        godot::Array values;
        for (int32_t i = 0; i < 2; ++i) {
            values.append(hako::godot_runtime::read_string(
                binary_data, base_off + 4 + (i * 128), 128));
        }
        obj["fixed_str"] = values;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 260);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 260 + 4);
        godot::Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_string(
                binary_data, meta.heap_off + offset_from_heap + (i * 128), 128));
        }
        obj["varray_str"] = values;
    }
    {
        godot::Array values;
        for (int32_t i = 0; i < 5; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::hako_msgs::binary_read_recursive_SimpleVarray(
                meta, binary_data, child, base_off + 268 + (i * 24));
            values.append(child);
        }
        obj["fixed_array"] = values;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 388);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 388 + 4);
        godot::Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::hako_msgs::binary_read_recursive_SimpleVarray(
                meta, binary_data, child, meta.heap_off + offset_from_heap + (i * 24));
            values.append(child);
        }
        obj["data"] = values;
    }
}

inline godot::Dictionary pdu_to_godot_SimpleStructVarray(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_SimpleStructVarray(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_SimpleStructVarray(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 412);
    if (obj.has("aaa")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["aaa"])),
            parent_off + 0);
    }
    if (obj.has("fixed_str")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["fixed_str"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 2);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_string(hako::godot_runtime::variant_to_string(values[i]), 128),
                parent_off + 4 + (i * 128));
        }
    }
    if (obj.has("varray_str")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["varray_str"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 260);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 260 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_string(hako::godot_runtime::variant_to_string(values[i]), 128));
        }
    }
    if (obj.has("fixed_array")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["fixed_array"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 5);
        for (int32_t i = 0; i < value_count; ++i) {
            hako::godot_pdu::hako_msgs::binary_write_recursive_SimpleVarray(
                parent_off + 268 + (i * 24),
                writer,
                allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
    if (obj.has("data")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["data"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 388);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 388 + 4);
        writer.heap_allocator.add(hako::godot_runtime::zero_bytes(array_size * 24), offset_from_heap);
        for (int32_t i = 0; i < array_size; ++i) {
            hako::godot_pdu::hako_msgs::binary_write_recursive_SimpleVarray(
                offset_from_heap + (i * 24),
                writer,
                writer.heap_allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
}

inline godot::PackedByteArray godot_to_pdu_SimpleStructVarray(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_SimpleStructVarray(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
