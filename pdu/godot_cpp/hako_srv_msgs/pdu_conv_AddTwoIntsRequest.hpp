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

namespace hako::godot_pdu::hako_srv_msgs {

inline void binary_read_recursive_AddTwoIntsRequest(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["a"] = hako::godot_runtime::read_int64(
        binary_data, base_off + 0);
    obj["b"] = hako::godot_runtime::read_int64(
        binary_data, base_off + 8);
}

inline godot::Dictionary pdu_to_godot_AddTwoIntsRequest(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_AddTwoIntsRequest(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_AddTwoIntsRequest(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 16);
    if (obj.has("a")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int64(
                hako::godot_runtime::variant_to_int64(obj["a"])),
            parent_off + 0);
    }
    if (obj.has("b")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int64(
                hako::godot_runtime::variant_to_int64(obj["b"])),
            parent_off + 8);
    }
}

inline godot::PackedByteArray godot_to_pdu_AddTwoIntsRequest(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_AddTwoIntsRequest(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_srv_msgs
