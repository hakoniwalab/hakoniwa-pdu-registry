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
#include "sensor_msgs/pdu_conv_CompressedImage.hpp"

namespace hako::godot_pdu::hako_msgs {

inline void binary_read_recursive_MonitorCameraData(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["request_id"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 0);
    obj["image_data_length"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 4);
    {
        godot::Dictionary child;
        hako::godot_pdu::sensor_msgs::binary_read_recursive_CompressedImage(
            meta, binary_data, child, base_off + 8);
        obj["image"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_MonitorCameraData(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_MonitorCameraData(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_MonitorCameraData(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 280);
    if (obj.has("request_id")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["request_id"])),
            parent_off + 0);
    }
    if (obj.has("image_data_length")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["image_data_length"])),
            parent_off + 4);
    }
    if (obj.has("image")) {
        hako::godot_pdu::sensor_msgs::binary_write_recursive_CompressedImage(
            parent_off + 8,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["image"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_MonitorCameraData(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_MonitorCameraData(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
