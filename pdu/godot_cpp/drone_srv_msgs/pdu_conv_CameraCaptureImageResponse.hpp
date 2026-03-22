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

namespace hako::godot_pdu::drone_srv_msgs {

inline void binary_read_recursive_CameraCaptureImageResponse(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["ok"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 0);
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 4);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 4 + 4);
        godot::PackedByteArray values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_uint8(
                binary_data, meta.heap_off + offset_from_heap + (i * 1)));
        }
        obj["data"] = values;
    }
    obj["message"] = hako::godot_runtime::read_string(
        binary_data, base_off + 12, 128);
}

inline godot::Dictionary pdu_to_godot_CameraCaptureImageResponse(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_CameraCaptureImageResponse(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_CameraCaptureImageResponse(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 140);
    if (obj.has("ok")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["ok"])),
            parent_off + 0);
    }
    if (obj.has("data")) {
        godot::PackedByteArray values = hako::godot_runtime::variant_to_packed_byte_array(obj["data"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 4);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 4 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_uint8(values[i]));
        }
    }
    if (obj.has("message")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["message"]), 128),
            parent_off + 12);
    }
}

inline godot::PackedByteArray godot_to_pdu_CameraCaptureImageResponse(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_CameraCaptureImageResponse(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::drone_srv_msgs
