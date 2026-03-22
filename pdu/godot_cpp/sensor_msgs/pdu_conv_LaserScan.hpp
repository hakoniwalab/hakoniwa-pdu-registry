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
#include "std_msgs/pdu_conv_Header.hpp"

namespace hako::godot_pdu::sensor_msgs {

inline void binary_read_recursive_LaserScan(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::std_msgs::binary_read_recursive_Header(
            meta, binary_data, child, base_off + 0);
        obj["header"] = child;
    }
    obj["angle_min"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 136);
    obj["angle_max"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 140);
    obj["angle_increment"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 144);
    obj["time_increment"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 148);
    obj["scan_time"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 152);
    obj["range_min"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 156);
    obj["range_max"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 160);
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 164);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 164 + 4);
        godot::PackedFloat32Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float32(
                binary_data, meta.heap_off + offset_from_heap + (i * 4)));
        }
        obj["ranges"] = values;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 172);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 172 + 4);
        godot::PackedFloat32Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float32(
                binary_data, meta.heap_off + offset_from_heap + (i * 4)));
        }
        obj["intensities"] = values;
    }
}

inline godot::Dictionary pdu_to_godot_LaserScan(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_LaserScan(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_LaserScan(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 176);
    if (obj.has("header")) {
        hako::godot_pdu::std_msgs::binary_write_recursive_Header(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("angle_min")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["angle_min"])),
            parent_off + 136);
    }
    if (obj.has("angle_max")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["angle_max"])),
            parent_off + 140);
    }
    if (obj.has("angle_increment")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["angle_increment"])),
            parent_off + 144);
    }
    if (obj.has("time_increment")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["time_increment"])),
            parent_off + 148);
    }
    if (obj.has("scan_time")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["scan_time"])),
            parent_off + 152);
    }
    if (obj.has("range_min")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["range_min"])),
            parent_off + 156);
    }
    if (obj.has("range_max")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["range_max"])),
            parent_off + 160);
    }
    if (obj.has("ranges")) {
        godot::PackedFloat32Array values = hako::godot_runtime::variant_to_packed_float32_array(obj["ranges"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 164);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 164 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float32(values[i]));
        }
    }
    if (obj.has("intensities")) {
        godot::PackedFloat32Array values = hako::godot_runtime::variant_to_packed_float32_array(obj["intensities"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 172);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 172 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float32(values[i]));
        }
    }
}

inline godot::PackedByteArray godot_to_pdu_LaserScan(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_LaserScan(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::sensor_msgs
