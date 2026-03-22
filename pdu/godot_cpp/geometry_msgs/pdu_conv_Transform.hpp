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
#include "geometry_msgs/pdu_conv_Quaternion.hpp"

namespace hako::godot_pdu::geometry_msgs {

inline void binary_read_recursive_Transform(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 0);
        obj["translation"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Quaternion(
            meta, binary_data, child, base_off + 24);
        obj["rotation"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_Transform(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Transform(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Transform(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 56);
    if (obj.has("translation")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["translation"]));
    }
    if (obj.has("rotation")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Quaternion(
            parent_off + 24,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["rotation"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_Transform(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Transform(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::geometry_msgs
