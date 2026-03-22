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

inline void binary_read_recursive_DroneTakeOffRequest(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["alt_m"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 0);
    obj["drone_name"] = hako::godot_runtime::read_string(
        binary_data, base_off + 8, 128);
}

inline godot::Dictionary pdu_to_godot_DroneTakeOffRequest(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_DroneTakeOffRequest(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_DroneTakeOffRequest(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 136);
    if (obj.has("alt_m")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["alt_m"])),
            parent_off + 0);
    }
    if (obj.has("drone_name")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["drone_name"]), 128),
            parent_off + 8);
    }
}

inline godot::PackedByteArray godot_to_pdu_DroneTakeOffRequest(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_DroneTakeOffRequest(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::drone_srv_msgs
