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
#include "hako_srv_msgs/pdu_conv_RenderObject.hpp"

namespace hako::godot_pdu::hako_srv_msgs {

inline void binary_read_recursive_RenderCameraFrameRequest(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["camera_name"] = hako::godot_runtime::read_string(
        binary_data, base_off + 0, 128);
    obj["sim_time_usec"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 128);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Pose(
            meta, binary_data, child, base_off + 136);
        obj["camera_pose"] = child;
    }
    obj["outputs"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 192);
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 196);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 196 + 4);
        godot::Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::hako_srv_msgs::binary_read_recursive_RenderObject(
                meta, binary_data, child, meta.heap_off + offset_from_heap + (i * 312));
            values.append(child);
        }
        obj["objects"] = values;
    }
}

inline godot::Dictionary pdu_to_godot_RenderCameraFrameRequest(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_RenderCameraFrameRequest(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_RenderCameraFrameRequest(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 508);
    if (obj.has("camera_name")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["camera_name"]), 128),
            parent_off + 0);
    }
    if (obj.has("sim_time_usec")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["sim_time_usec"])),
            parent_off + 128);
    }
    if (obj.has("camera_pose")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Pose(
            parent_off + 136,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["camera_pose"]));
    }
    if (obj.has("outputs")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["outputs"])),
            parent_off + 192);
    }
    if (obj.has("objects")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["objects"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 196);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 196 + 4);
        writer.heap_allocator.add(hako::godot_runtime::zero_bytes(array_size * 312), offset_from_heap);
        for (int32_t i = 0; i < array_size; ++i) {
            hako::godot_pdu::hako_srv_msgs::binary_write_recursive_RenderObject(
                offset_from_heap + (i * 312),
                writer,
                writer.heap_allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
}

inline godot::PackedByteArray godot_to_pdu_RenderCameraFrameRequest(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_RenderCameraFrameRequest(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_srv_msgs
