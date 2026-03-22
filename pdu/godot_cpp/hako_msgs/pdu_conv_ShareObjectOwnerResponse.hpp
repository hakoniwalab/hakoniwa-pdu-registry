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

inline void binary_read_recursive_ShareObjectOwnerResponse(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["object_name"] = hako::godot_runtime::read_string(
        binary_data, base_off + 0, 128);
    obj["request_type"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 128);
    obj["owner_id"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 132);
    obj["accepted"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 136);
}

inline godot::Dictionary pdu_to_godot_ShareObjectOwnerResponse(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_ShareObjectOwnerResponse(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_ShareObjectOwnerResponse(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 140);
    if (obj.has("object_name")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["object_name"]), 128),
            parent_off + 0);
    }
    if (obj.has("request_type")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["request_type"])),
            parent_off + 128);
    }
    if (obj.has("owner_id")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["owner_id"])),
            parent_off + 132);
    }
    if (obj.has("accepted")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["accepted"])),
            parent_off + 136);
    }
}

inline godot::PackedByteArray godot_to_pdu_ShareObjectOwnerResponse(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_ShareObjectOwnerResponse(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
