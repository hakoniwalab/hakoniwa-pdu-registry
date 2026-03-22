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
#include "geometry_msgs/pdu_conv_Twist.hpp"

namespace hako::godot_pdu::hako_msgs {

inline void binary_read_recursive_ManualPosAttControl(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["do_operation"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 0);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Twist(
            meta, binary_data, child, base_off + 8);
        obj["posatt"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_ManualPosAttControl(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_ManualPosAttControl(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_ManualPosAttControl(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 56);
    if (obj.has("do_operation")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["do_operation"])),
            parent_off + 0);
    }
    if (obj.has("posatt")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Twist(
            parent_off + 8,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["posatt"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_ManualPosAttControl(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_ManualPosAttControl(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
