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
#include "hako_msgs/pdu_conv_DisturbanceTemperature.hpp"
#include "hako_msgs/pdu_conv_DisturbanceWind.hpp"
#include "hako_msgs/pdu_conv_DisturbanceAtm.hpp"
#include "hako_msgs/pdu_conv_DisturbanceBoundary.hpp"
#include "hako_msgs/pdu_conv_DisturbanceUserCustom.hpp"

namespace hako::godot_pdu::hako_msgs {

inline void binary_read_recursive_Disturbance(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::hako_msgs::binary_read_recursive_DisturbanceTemperature(
            meta, binary_data, child, base_off + 0);
        obj["d_temp"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::hako_msgs::binary_read_recursive_DisturbanceWind(
            meta, binary_data, child, base_off + 8);
        obj["d_wind"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::hako_msgs::binary_read_recursive_DisturbanceAtm(
            meta, binary_data, child, base_off + 32);
        obj["d_atm"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::hako_msgs::binary_read_recursive_DisturbanceBoundary(
            meta, binary_data, child, base_off + 40);
        obj["d_boundary"] = child;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 88);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 88 + 4);
        godot::Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::hako_msgs::binary_read_recursive_DisturbanceUserCustom(
                meta, binary_data, child, meta.heap_off + offset_from_heap + (i * 8));
            values.append(child);
        }
        obj["d_user_custom"] = values;
    }
}

inline godot::Dictionary pdu_to_godot_Disturbance(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Disturbance(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Disturbance(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 96);
    if (obj.has("d_temp")) {
        hako::godot_pdu::hako_msgs::binary_write_recursive_DisturbanceTemperature(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["d_temp"]));
    }
    if (obj.has("d_wind")) {
        hako::godot_pdu::hako_msgs::binary_write_recursive_DisturbanceWind(
            parent_off + 8,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["d_wind"]));
    }
    if (obj.has("d_atm")) {
        hako::godot_pdu::hako_msgs::binary_write_recursive_DisturbanceAtm(
            parent_off + 32,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["d_atm"]));
    }
    if (obj.has("d_boundary")) {
        hako::godot_pdu::hako_msgs::binary_write_recursive_DisturbanceBoundary(
            parent_off + 40,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["d_boundary"]));
    }
    if (obj.has("d_user_custom")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["d_user_custom"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 88);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 88 + 4);
        writer.heap_allocator.add(hako::godot_runtime::zero_bytes(array_size * 8), offset_from_heap);
        for (int32_t i = 0; i < array_size; ++i) {
            hako::godot_pdu::hako_msgs::binary_write_recursive_DisturbanceUserCustom(
                offset_from_heap + (i * 8),
                writer,
                writer.heap_allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
}

inline godot::PackedByteArray godot_to_pdu_Disturbance(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Disturbance(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
