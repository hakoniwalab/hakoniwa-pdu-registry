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

inline void binary_read_recursive_GetSimStateResponse(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["sim_state"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 0);
    obj["master_time"] = hako::godot_runtime::read_int64(
        binary_data, base_off + 8);
    obj["is_pdu_created"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 16);
    obj["is_simulation_mode"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 20);
    obj["is_pdu_sync_mode"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 24);
}

inline godot::Dictionary pdu_to_godot_GetSimStateResponse(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_GetSimStateResponse(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_GetSimStateResponse(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 28);
    if (obj.has("sim_state")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["sim_state"])),
            parent_off + 0);
    }
    if (obj.has("master_time")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int64(
                hako::godot_runtime::variant_to_int64(obj["master_time"])),
            parent_off + 8);
    }
    if (obj.has("is_pdu_created")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["is_pdu_created"])),
            parent_off + 16);
    }
    if (obj.has("is_simulation_mode")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["is_simulation_mode"])),
            parent_off + 20);
    }
    if (obj.has("is_pdu_sync_mode")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["is_pdu_sync_mode"])),
            parent_off + 24);
    }
}

inline godot::PackedByteArray godot_to_pdu_GetSimStateResponse(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_GetSimStateResponse(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_srv_msgs
