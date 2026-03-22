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
#include "hako_msgs/pdu_conv_HakoDroneCmdHeader.hpp"

namespace hako::godot_pdu::hako_msgs {

inline void binary_read_recursive_HakoDroneCmdTakeoff(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::hako_msgs::binary_read_recursive_HakoDroneCmdHeader(
            meta, binary_data, child, base_off + 0);
        obj["header"] = child;
    }
    obj["height"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 16);
    obj["speed"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 24);
    obj["yaw_deg"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 32);
}

inline godot::Dictionary pdu_to_godot_HakoDroneCmdTakeoff(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_HakoDroneCmdTakeoff(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_HakoDroneCmdTakeoff(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 40);
    if (obj.has("header")) {
        hako::godot_pdu::hako_msgs::binary_write_recursive_HakoDroneCmdHeader(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("height")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["height"])),
            parent_off + 16);
    }
    if (obj.has("speed")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["speed"])),
            parent_off + 24);
    }
    if (obj.has("yaw_deg")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["yaw_deg"])),
            parent_off + 32);
    }
}

inline godot::PackedByteArray godot_to_pdu_HakoDroneCmdTakeoff(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_HakoDroneCmdTakeoff(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
