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
#include "geometry_msgs/pdu_conv_Pose.hpp"
#include "hako_msgs/pdu_conv_HakoBatteryStatus.hpp"

namespace hako::godot_pdu::drone_srv_msgs {

inline void binary_read_recursive_DroneGetStateResponse(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["ok"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 0);
    obj["is_ready"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 4);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Pose(
            meta, binary_data, child, base_off + 8);
        obj["current_pose"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::hako_msgs::binary_read_recursive_HakoBatteryStatus(
            meta, binary_data, child, base_off + 64);
        obj["battery_status"] = child;
    }
    obj["mode"] = hako::godot_runtime::read_string(
        binary_data, base_off + 96, 128);
    obj["message"] = hako::godot_runtime::read_string(
        binary_data, base_off + 224, 128);
}

inline godot::Dictionary pdu_to_godot_DroneGetStateResponse(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_DroneGetStateResponse(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_DroneGetStateResponse(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 352);
    if (obj.has("ok")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["ok"])),
            parent_off + 0);
    }
    if (obj.has("is_ready")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["is_ready"])),
            parent_off + 4);
    }
    if (obj.has("current_pose")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Pose(
            parent_off + 8,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["current_pose"]));
    }
    if (obj.has("battery_status")) {
        hako::godot_pdu::hako_msgs::binary_write_recursive_HakoBatteryStatus(
            parent_off + 64,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["battery_status"]));
    }
    if (obj.has("mode")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["mode"]), 128),
            parent_off + 96);
    }
    if (obj.has("message")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["message"]), 128),
            parent_off + 224);
    }
}

inline godot::PackedByteArray godot_to_pdu_DroneGetStateResponse(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_DroneGetStateResponse(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::drone_srv_msgs
