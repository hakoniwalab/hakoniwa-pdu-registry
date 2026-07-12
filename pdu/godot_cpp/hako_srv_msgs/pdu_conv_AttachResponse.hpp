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
#include "hako_srv_msgs/pdu_conv_LogicalTime.hpp"

namespace hako::godot_pdu::hako_srv_msgs {

inline void binary_read_recursive_AttachResponse(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["result_code"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 0);
    obj["session_id"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 8);
    {
        godot::Dictionary child;
        hako::godot_pdu::hako_srv_msgs::binary_read_recursive_LogicalTime(
            meta, binary_data, child, base_off + 16);
        obj["world_time"] = child;
    }
    obj["delta_asset_tick"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 32);
}

inline godot::Dictionary pdu_to_godot_AttachResponse(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_AttachResponse(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_AttachResponse(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 40);
    if (obj.has("result_code")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["result_code"])),
            parent_off + 0);
    }
    if (obj.has("session_id")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["session_id"])),
            parent_off + 8);
    }
    if (obj.has("world_time")) {
        hako::godot_pdu::hako_srv_msgs::binary_write_recursive_LogicalTime(
            parent_off + 16,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["world_time"]));
    }
    if (obj.has("delta_asset_tick")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["delta_asset_tick"])),
            parent_off + 32);
    }
}

inline godot::PackedByteArray godot_to_pdu_AttachResponse(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_AttachResponse(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_srv_msgs
