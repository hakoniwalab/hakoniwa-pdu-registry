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
#include "geometry_msgs/pdu_conv_Vector3.hpp"

namespace hako::godot_pdu::mavros_msgs {

inline void binary_read_recursive_GlobalPositionTarget(
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
    obj["coordinate_frame"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 136);
    obj["type_mask"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 138);
    obj["latitude"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 144);
    obj["longitude"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 152);
    obj["altitude"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 160);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 168);
        obj["velocity"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 192);
        obj["acceleration_or_force"] = child;
    }
    obj["yaw"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 216);
    obj["yaw_rate"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 220);
}

inline godot::Dictionary pdu_to_godot_GlobalPositionTarget(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_GlobalPositionTarget(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_GlobalPositionTarget(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 224);
    if (obj.has("header")) {
        hako::godot_pdu::std_msgs::binary_write_recursive_Header(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("coordinate_frame")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["coordinate_frame"])),
            parent_off + 136);
    }
    if (obj.has("type_mask")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["type_mask"])),
            parent_off + 138);
    }
    if (obj.has("latitude")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["latitude"])),
            parent_off + 144);
    }
    if (obj.has("longitude")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["longitude"])),
            parent_off + 152);
    }
    if (obj.has("altitude")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["altitude"])),
            parent_off + 160);
    }
    if (obj.has("velocity")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 168,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["velocity"]));
    }
    if (obj.has("acceleration_or_force")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 192,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["acceleration_or_force"]));
    }
    if (obj.has("yaw")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["yaw"])),
            parent_off + 216);
    }
    if (obj.has("yaw_rate")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["yaw_rate"])),
            parent_off + 220);
    }
}

inline godot::PackedByteArray godot_to_pdu_GlobalPositionTarget(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_GlobalPositionTarget(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::mavros_msgs
