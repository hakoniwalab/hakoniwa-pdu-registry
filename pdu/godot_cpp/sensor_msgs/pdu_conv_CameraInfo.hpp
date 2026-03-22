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
#include "sensor_msgs/pdu_conv_RegionOfInterest.hpp"

namespace hako::godot_pdu::sensor_msgs {

inline void binary_read_recursive_CameraInfo(
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
    obj["height"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 136);
    obj["width"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 140);
    obj["distortion_model"] = hako::godot_runtime::read_string(
        binary_data, base_off + 144, 128);
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 272);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 272 + 4);
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, meta.heap_off + offset_from_heap + (i * 8)));
        }
        obj["d"] = values;
    }
    {
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < 9; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, base_off + 280 + (i * 8)));
        }
        obj["k"] = values;
    }
    {
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < 9; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, base_off + 352 + (i * 8)));
        }
        obj["r"] = values;
    }
    {
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < 12; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, base_off + 424 + (i * 8)));
        }
        obj["p"] = values;
    }
    obj["binning_x"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 520);
    obj["binning_y"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 524);
    {
        godot::Dictionary child;
        hako::godot_pdu::sensor_msgs::binary_read_recursive_RegionOfInterest(
            meta, binary_data, child, base_off + 528);
        obj["roi"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_CameraInfo(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_CameraInfo(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_CameraInfo(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 548);
    if (obj.has("header")) {
        hako::godot_pdu::std_msgs::binary_write_recursive_Header(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("height")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["height"])),
            parent_off + 136);
    }
    if (obj.has("width")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["width"])),
            parent_off + 140);
    }
    if (obj.has("distortion_model")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["distortion_model"]), 128),
            parent_off + 144);
    }
    if (obj.has("d")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["d"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 272);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 272 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]));
        }
    }
    if (obj.has("k")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["k"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 9);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]),
                parent_off + 280 + (i * 8));
        }
    }
    if (obj.has("r")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["r"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 9);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]),
                parent_off + 352 + (i * 8));
        }
    }
    if (obj.has("p")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["p"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 12);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]),
                parent_off + 424 + (i * 8));
        }
    }
    if (obj.has("binning_x")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["binning_x"])),
            parent_off + 520);
    }
    if (obj.has("binning_y")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["binning_y"])),
            parent_off + 524);
    }
    if (obj.has("roi")) {
        hako::godot_pdu::sensor_msgs::binary_write_recursive_RegionOfInterest(
            parent_off + 528,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["roi"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_CameraInfo(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_CameraInfo(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::sensor_msgs
