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

inline void binary_read_recursive_ExecutionUnitRuntimeContext(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["config_hash"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 0);
    obj["epoch"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 4);
    obj["owner_id"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 5);
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 8);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 8 + 4);
        godot::PackedByteArray values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_uint8(
                binary_data, meta.heap_off + offset_from_heap + (i * 1)));
        }
        obj["context"] = values;
    }
}

inline godot::Dictionary pdu_to_godot_ExecutionUnitRuntimeContext(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_ExecutionUnitRuntimeContext(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_ExecutionUnitRuntimeContext(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 9);
    if (obj.has("config_hash")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["config_hash"])),
            parent_off + 0);
    }
    if (obj.has("epoch")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["epoch"])),
            parent_off + 4);
    }
    if (obj.has("owner_id")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["owner_id"])),
            parent_off + 5);
    }
    if (obj.has("context")) {
        godot::PackedByteArray values = hako::godot_runtime::variant_to_packed_byte_array(obj["context"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 8);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 8 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_uint8(values[i]));
        }
    }
}

inline godot::PackedByteArray godot_to_pdu_ExecutionUnitRuntimeContext(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_ExecutionUnitRuntimeContext(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
