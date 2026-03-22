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
#include "hako_srv_msgs/pdu_conv_ServiceRequestHeader.hpp"
#include "drone_srv_msgs/pdu_conv_MagnetGrabRequest.hpp"

namespace hako::godot_pdu::drone_srv_msgs {

inline void binary_read_recursive_MagnetGrabRequestPacket(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::hako_srv_msgs::binary_read_recursive_ServiceRequestHeader(
            meta, binary_data, child, base_off + 0);
        obj["header"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::drone_srv_msgs::binary_read_recursive_MagnetGrabRequest(
            meta, binary_data, child, base_off + 268);
        obj["body"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_MagnetGrabRequestPacket(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_MagnetGrabRequestPacket(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_MagnetGrabRequestPacket(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 404);
    if (obj.has("header")) {
        hako::godot_pdu::hako_srv_msgs::binary_write_recursive_ServiceRequestHeader(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("body")) {
        hako::godot_pdu::drone_srv_msgs::binary_write_recursive_MagnetGrabRequest(
            parent_off + 268,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["body"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_MagnetGrabRequestPacket(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_MagnetGrabRequestPacket(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::drone_srv_msgs
