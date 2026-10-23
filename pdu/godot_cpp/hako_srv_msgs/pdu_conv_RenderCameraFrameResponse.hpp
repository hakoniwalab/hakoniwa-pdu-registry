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
#include "sensor_msgs/pdu_conv_Image.hpp"

namespace hako::godot_pdu::hako_srv_msgs {

inline void binary_read_recursive_RenderCameraFrameResponse(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["result_code"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 0);
    obj["sim_time_usec"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 8);
    {
        godot::Dictionary child;
        hako::godot_pdu::sensor_msgs::binary_read_recursive_Image(
            meta, binary_data, child, base_off + 16);
        obj["rgb"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::sensor_msgs::binary_read_recursive_Image(
            meta, binary_data, child, base_off + 304);
        obj["depth"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::sensor_msgs::binary_read_recursive_Image(
            meta, binary_data, child, base_off + 592);
        obj["segmentation"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_RenderCameraFrameResponse(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_RenderCameraFrameResponse(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_RenderCameraFrameResponse(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 880);
    if (obj.has("result_code")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["result_code"])),
            parent_off + 0);
    }
    if (obj.has("sim_time_usec")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["sim_time_usec"])),
            parent_off + 8);
    }
    if (obj.has("rgb")) {
        hako::godot_pdu::sensor_msgs::binary_write_recursive_Image(
            parent_off + 16,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["rgb"]));
    }
    if (obj.has("depth")) {
        hako::godot_pdu::sensor_msgs::binary_write_recursive_Image(
            parent_off + 304,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["depth"]));
    }
    if (obj.has("segmentation")) {
        hako::godot_pdu::sensor_msgs::binary_write_recursive_Image(
            parent_off + 592,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["segmentation"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_RenderCameraFrameResponse(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_RenderCameraFrameResponse(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_srv_msgs
