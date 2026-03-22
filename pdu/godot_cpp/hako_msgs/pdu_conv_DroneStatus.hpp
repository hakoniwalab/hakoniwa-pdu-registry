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

namespace hako::godot_pdu::hako_msgs {

inline void binary_read_recursive_DroneStatus(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["flight_mode"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 0);
    obj["internal_state"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 4);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 8);
        obj["propeller_wind"] = child;
    }
    obj["collided_counts"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 32);
}

inline godot::Dictionary pdu_to_godot_DroneStatus(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_DroneStatus(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_DroneStatus(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 36);
    if (obj.has("flight_mode")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["flight_mode"])),
            parent_off + 0);
    }
    if (obj.has("internal_state")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["internal_state"])),
            parent_off + 4);
    }
    if (obj.has("propeller_wind")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 8,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["propeller_wind"]));
    }
    if (obj.has("collided_counts")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["collided_counts"])),
            parent_off + 32);
    }
}

inline godot::PackedByteArray godot_to_pdu_DroneStatus(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_DroneStatus(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
