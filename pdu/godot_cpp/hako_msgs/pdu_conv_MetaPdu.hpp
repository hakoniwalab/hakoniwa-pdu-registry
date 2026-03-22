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

inline void binary_read_recursive_MetaPdu(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["total_len"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 0);
    obj["magicno"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 4);
    obj["version"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 8);
    obj["flags"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 10);
    obj["meta_request_type"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 12);
    obj["hako_time_us"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 16);
    obj["asset_time_us"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 24);
    obj["real_time_us"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 32);
    obj["robot_name"] = hako::godot_runtime::read_string(
        binary_data, base_off + 40, 128);
    obj["channel_id"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 168);
    obj["body_len"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 172);
}

inline godot::Dictionary pdu_to_godot_MetaPdu(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_MetaPdu(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_MetaPdu(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 176);
    if (obj.has("total_len")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["total_len"])),
            parent_off + 0);
    }
    if (obj.has("magicno")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["magicno"])),
            parent_off + 4);
    }
    if (obj.has("version")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["version"])),
            parent_off + 8);
    }
    if (obj.has("flags")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["flags"])),
            parent_off + 10);
    }
    if (obj.has("meta_request_type")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["meta_request_type"])),
            parent_off + 12);
    }
    if (obj.has("hako_time_us")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["hako_time_us"])),
            parent_off + 16);
    }
    if (obj.has("asset_time_us")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["asset_time_us"])),
            parent_off + 24);
    }
    if (obj.has("real_time_us")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["real_time_us"])),
            parent_off + 32);
    }
    if (obj.has("robot_name")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["robot_name"]), 128),
            parent_off + 40);
    }
    if (obj.has("channel_id")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["channel_id"])),
            parent_off + 168);
    }
    if (obj.has("body_len")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["body_len"])),
            parent_off + 172);
    }
}

inline godot::PackedByteArray godot_to_pdu_MetaPdu(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_MetaPdu(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
