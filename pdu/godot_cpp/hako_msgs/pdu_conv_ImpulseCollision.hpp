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
#include "geometry_msgs/pdu_conv_Point.hpp"
#include "geometry_msgs/pdu_conv_Vector3.hpp"

namespace hako::godot_pdu::hako_msgs {

inline void binary_read_recursive_ImpulseCollision(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["collision"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 0);
    obj["is_target_static"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 4);
    obj["restitution_coefficient"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 8);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Point(
            meta, binary_data, child, base_off + 16);
        obj["self_contact_vector"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 40);
        obj["normal"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Point(
            meta, binary_data, child, base_off + 64);
        obj["target_contact_vector"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 88);
        obj["target_velocity"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 112);
        obj["target_angular_velocity"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 136);
        obj["target_euler"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 160);
        obj["target_inertia"] = child;
    }
    obj["target_mass"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 184);
}

inline godot::Dictionary pdu_to_godot_ImpulseCollision(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_ImpulseCollision(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_ImpulseCollision(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 192);
    if (obj.has("collision")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["collision"])),
            parent_off + 0);
    }
    if (obj.has("is_target_static")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["is_target_static"])),
            parent_off + 4);
    }
    if (obj.has("restitution_coefficient")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["restitution_coefficient"])),
            parent_off + 8);
    }
    if (obj.has("self_contact_vector")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Point(
            parent_off + 16,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["self_contact_vector"]));
    }
    if (obj.has("normal")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 40,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["normal"]));
    }
    if (obj.has("target_contact_vector")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Point(
            parent_off + 64,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["target_contact_vector"]));
    }
    if (obj.has("target_velocity")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 88,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["target_velocity"]));
    }
    if (obj.has("target_angular_velocity")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 112,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["target_angular_velocity"]));
    }
    if (obj.has("target_euler")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 136,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["target_euler"]));
    }
    if (obj.has("target_inertia")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 160,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["target_inertia"]));
    }
    if (obj.has("target_mass")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["target_mass"])),
            parent_off + 184);
    }
}

inline godot::PackedByteArray godot_to_pdu_ImpulseCollision(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_ImpulseCollision(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
