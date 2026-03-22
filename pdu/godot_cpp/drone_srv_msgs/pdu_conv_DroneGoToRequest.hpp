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

namespace hako::godot_pdu::drone_srv_msgs {

inline void binary_read_recursive_DroneGoToRequest(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["drone_name"] = hako::godot_runtime::read_string(
        binary_data, base_off + 0, 128);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 128);
        obj["target_pose"] = child;
    }
    obj["speed_m_s"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 152);
    obj["yaw_deg"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 156);
    obj["tolerance_m"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 160);
    obj["timeout_sec"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 164);
}

inline godot::Dictionary pdu_to_godot_DroneGoToRequest(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_DroneGoToRequest(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_DroneGoToRequest(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 168);
    if (obj.has("drone_name")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["drone_name"]), 128),
            parent_off + 0);
    }
    if (obj.has("target_pose")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 128,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["target_pose"]));
    }
    if (obj.has("speed_m_s")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["speed_m_s"])),
            parent_off + 152);
    }
    if (obj.has("yaw_deg")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["yaw_deg"])),
            parent_off + 156);
    }
    if (obj.has("tolerance_m")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["tolerance_m"])),
            parent_off + 160);
    }
    if (obj.has("timeout_sec")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["timeout_sec"])),
            parent_off + 164);
    }
}

inline godot::PackedByteArray godot_to_pdu_DroneGoToRequest(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_DroneGoToRequest(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::drone_srv_msgs
