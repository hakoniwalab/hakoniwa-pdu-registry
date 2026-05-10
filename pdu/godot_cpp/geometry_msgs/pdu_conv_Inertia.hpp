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
#include "geometry_msgs/pdu_conv_Vector3.hpp"

namespace hako::godot_pdu::geometry_msgs {

inline void binary_read_recursive_Inertia(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["m"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 0);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 8);
        obj["com"] = child;
    }
    obj["ixx"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 32);
    obj["ixy"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 40);
    obj["ixz"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 48);
    obj["iyy"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 56);
    obj["iyz"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 64);
    obj["izz"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 72);
}

inline godot::Dictionary pdu_to_godot_Inertia(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Inertia(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Inertia(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 80);
    if (obj.has("m")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["m"])),
            parent_off + 0);
    }
    if (obj.has("com")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 8,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["com"]));
    }
    if (obj.has("ixx")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["ixx"])),
            parent_off + 32);
    }
    if (obj.has("ixy")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["ixy"])),
            parent_off + 40);
    }
    if (obj.has("ixz")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["ixz"])),
            parent_off + 48);
    }
    if (obj.has("iyy")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["iyy"])),
            parent_off + 56);
    }
    if (obj.has("iyz")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["iyz"])),
            parent_off + 64);
    }
    if (obj.has("izz")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["izz"])),
            parent_off + 72);
    }
}

inline godot::PackedByteArray godot_to_pdu_Inertia(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Inertia(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::geometry_msgs
