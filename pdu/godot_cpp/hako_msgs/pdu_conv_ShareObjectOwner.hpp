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
#include "geometry_msgs/pdu_conv_Twist.hpp"

namespace hako::godot_pdu::hako_msgs {

inline void binary_read_recursive_ShareObjectOwner(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["object_name"] = hako::godot_runtime::read_string(
        binary_data, base_off + 0, 128);
    obj["owner_id"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 128);
    obj["last_update"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 136);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Twist(
            meta, binary_data, child, base_off + 144);
        obj["pos"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_ShareObjectOwner(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_ShareObjectOwner(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_ShareObjectOwner(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 192);
    if (obj.has("object_name")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["object_name"]), 128),
            parent_off + 0);
    }
    if (obj.has("owner_id")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["owner_id"])),
            parent_off + 128);
    }
    if (obj.has("last_update")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["last_update"])),
            parent_off + 136);
    }
    if (obj.has("pos")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Twist(
            parent_off + 144,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["pos"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_ShareObjectOwner(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_ShareObjectOwner(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
