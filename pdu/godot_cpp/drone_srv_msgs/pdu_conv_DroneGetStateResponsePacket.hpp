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
#include "hako_srv_msgs/pdu_conv_ServiceResponseHeader.hpp"
#include "drone_srv_msgs/pdu_conv_DroneGetStateResponse.hpp"

namespace hako::godot_pdu::drone_srv_msgs {

inline void binary_read_recursive_DroneGetStateResponsePacket(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::hako_srv_msgs::binary_read_recursive_ServiceResponseHeader(
            meta, binary_data, child, base_off + 0);
        obj["header"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::drone_srv_msgs::binary_read_recursive_DroneGetStateResponse(
            meta, binary_data, child, base_off + 272);
        obj["body"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_DroneGetStateResponsePacket(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_DroneGetStateResponsePacket(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_DroneGetStateResponsePacket(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 624);
    if (obj.has("header")) {
        hako::godot_pdu::hako_srv_msgs::binary_write_recursive_ServiceResponseHeader(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("body")) {
        hako::godot_pdu::drone_srv_msgs::binary_write_recursive_DroneGetStateResponse(
            parent_off + 272,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["body"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_DroneGetStateResponsePacket(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_DroneGetStateResponsePacket(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::drone_srv_msgs
