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
#include "std_msgs/pdu_conv_Header.hpp"
#include "geometry_msgs/pdu_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_conv_Vector3.hpp"

namespace hako::godot_pdu::mavros_msgs {

inline void binary_read_recursive_AttitudeTarget(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::std_msgs::binary_read_recursive_Header(
            meta, binary_data, child, base_off + 0);
        obj["header"] = child;
    }
    obj["type_mask"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 136);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Quaternion(
            meta, binary_data, child, base_off + 144);
        obj["orientation"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 176);
        obj["body_rate"] = child;
    }
    obj["thrust"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 200);
}

inline godot::Dictionary pdu_to_godot_AttitudeTarget(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_AttitudeTarget(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_AttitudeTarget(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 204);
    if (obj.has("header")) {
        hako::godot_pdu::std_msgs::binary_write_recursive_Header(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("type_mask")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["type_mask"])),
            parent_off + 136);
    }
    if (obj.has("orientation")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Quaternion(
            parent_off + 144,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["orientation"]));
    }
    if (obj.has("body_rate")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 176,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["body_rate"]));
    }
    if (obj.has("thrust")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["thrust"])),
            parent_off + 200);
    }
}

inline godot::PackedByteArray godot_to_pdu_AttitudeTarget(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_AttitudeTarget(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::mavros_msgs
