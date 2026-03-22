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

inline void binary_read_recursive_SimpleVarray(
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
            values.append(hako::godot_runtime::read_int8(
                binary_data, meta.heap_off + offset_from_heap + (i * 1)));
        }
        obj["data"] = values;
    }
    {
        godot::Array values;
        for (int32_t i = 0; i < 10; ++i) {
            values.append(hako::godot_runtime::read_int8(
                binary_data, base_off + 8 + (i * 1)));
        }
        obj["fixed_array"] = values;
    }
    obj["p_mem1"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 20);
}

inline godot::Dictionary pdu_to_godot_SimpleVarray(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_SimpleVarray(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_SimpleVarray(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 24);
    if (obj.has("data")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["data"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 0);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 0 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_int8(hako::godot_runtime::variant_to_int8(values[i])));
        }
    }
    if (obj.has("fixed_array")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["fixed_array"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 10);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_int8(hako::godot_runtime::variant_to_int8(values[i])),
                parent_off + 8 + (i * 1));
        }
    }
    if (obj.has("p_mem1")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["p_mem1"])),
            parent_off + 20);
    }
}

inline godot::PackedByteArray godot_to_pdu_SimpleVarray(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_SimpleVarray(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
