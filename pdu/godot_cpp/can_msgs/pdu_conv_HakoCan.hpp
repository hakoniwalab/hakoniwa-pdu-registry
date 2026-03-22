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
#include "can_msgs/pdu_conv_HakoCanHead.hpp"
#include "can_msgs/pdu_conv_HakoCanBody.hpp"

namespace hako::godot_pdu::can_msgs {

inline void binary_read_recursive_HakoCan(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::can_msgs::binary_read_recursive_HakoCanHead(
            meta, binary_data, child, base_off + 0);
        obj["head"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::can_msgs::binary_read_recursive_HakoCanBody(
            meta, binary_data, child, base_off + 20);
        obj["body"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_HakoCan(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_HakoCan(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_HakoCan(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 28);
    if (obj.has("head")) {
        hako::godot_pdu::can_msgs::binary_write_recursive_HakoCanHead(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["head"]));
    }
    if (obj.has("body")) {
        hako::godot_pdu::can_msgs::binary_write_recursive_HakoCanBody(
            parent_off + 20,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["body"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_HakoCan(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_HakoCan(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::can_msgs
