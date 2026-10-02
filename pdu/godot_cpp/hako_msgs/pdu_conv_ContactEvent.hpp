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
#include "builtin_interfaces/pdu_conv_Time.hpp"
#include "geometry_msgs/pdu_conv_Point.hpp"

namespace hako::godot_pdu::hako_msgs {

inline void binary_read_recursive_ContactEvent(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::builtin_interfaces::binary_read_recursive_Time(
            meta, binary_data, child, base_off + 0);
        obj["stamp"] = child;
    }
    obj["self_name"] = hako::godot_runtime::read_string(
        binary_data, base_off + 8, 128);
    obj["other_name"] = hako::godot_runtime::read_string(
        binary_data, base_off + 136, 128);
    obj["other_kind"] = hako::godot_runtime::read_string(
        binary_data, base_off + 264, 128);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Point(
            meta, binary_data, child, base_off + 392);
        obj["position"] = child;
    }
    obj["relative_speed"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 416);
    obj["started"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 424);
}

inline godot::Dictionary pdu_to_godot_ContactEvent(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_ContactEvent(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_ContactEvent(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 428);
    if (obj.has("stamp")) {
        hako::godot_pdu::builtin_interfaces::binary_write_recursive_Time(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["stamp"]));
    }
    if (obj.has("self_name")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["self_name"]), 128),
            parent_off + 8);
    }
    if (obj.has("other_name")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["other_name"]), 128),
            parent_off + 136);
    }
    if (obj.has("other_kind")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["other_kind"]), 128),
            parent_off + 264);
    }
    if (obj.has("position")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Point(
            parent_off + 392,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["position"]));
    }
    if (obj.has("relative_speed")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["relative_speed"])),
            parent_off + 416);
    }
    if (obj.has("started")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["started"])),
            parent_off + 424);
    }
}

inline godot::PackedByteArray godot_to_pdu_ContactEvent(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_ContactEvent(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
