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

inline void binary_read_recursive_ServiceRequestHeader(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["request_id"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 0);
    obj["service_name"] = hako::godot_runtime::read_string(
        binary_data, base_off + 4, 128);
    obj["client_name"] = hako::godot_runtime::read_string(
        binary_data, base_off + 132, 128);
    obj["opcode"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 260);
    obj["status_poll_interval_msec"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 264);
}

inline godot::Dictionary pdu_to_godot_ServiceRequestHeader(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_ServiceRequestHeader(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_ServiceRequestHeader(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 268);
    if (obj.has("request_id")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["request_id"])),
            parent_off + 0);
    }
    if (obj.has("service_name")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["service_name"]), 128),
            parent_off + 4);
    }
    if (obj.has("client_name")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["client_name"]), 128),
            parent_off + 132);
    }
    if (obj.has("opcode")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["opcode"])),
            parent_off + 260);
    }
    if (obj.has("status_poll_interval_msec")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["status_poll_interval_msec"])),
            parent_off + 264);
    }
}

inline godot::PackedByteArray godot_to_pdu_ServiceRequestHeader(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_ServiceRequestHeader(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_srv_msgs
