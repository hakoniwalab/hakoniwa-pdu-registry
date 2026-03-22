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
#include "sensor_msgs/pdu_conv_PointField.hpp"

namespace hako::godot_pdu::sensor_msgs {

inline void binary_read_recursive_PointCloud2(
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
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 144);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 144 + 4);
        godot::Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::sensor_msgs::binary_read_recursive_PointField(
                meta, binary_data, child, meta.heap_off + offset_from_heap + (i * 140));
            values.append(child);
        }
        obj["fields"] = values;
    }
    obj["is_bigendian"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 152);
    obj["point_step"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 156);
    obj["row_step"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 160);
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 164);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 164 + 4);
        godot::PackedByteArray values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_uint8(
                binary_data, meta.heap_off + offset_from_heap + (i * 1)));
        }
        obj["data"] = values;
    }
    obj["is_dense"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 172);
}

inline godot::Dictionary pdu_to_godot_PointCloud2(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_PointCloud2(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_PointCloud2(
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
    if (obj.has("fields")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["fields"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 144);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 144 + 4);
        writer.heap_allocator.add(hako::godot_runtime::zero_bytes(array_size * 140), offset_from_heap);
        for (int32_t i = 0; i < array_size; ++i) {
            hako::godot_pdu::sensor_msgs::binary_write_recursive_PointField(
                offset_from_heap + (i * 140),
                writer,
                writer.heap_allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
    if (obj.has("is_bigendian")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["is_bigendian"])),
            parent_off + 152);
    }
    if (obj.has("point_step")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["point_step"])),
            parent_off + 156);
    }
    if (obj.has("row_step")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["row_step"])),
            parent_off + 160);
    }
    if (obj.has("data")) {
        godot::PackedByteArray values = hako::godot_runtime::variant_to_packed_byte_array(obj["data"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 164);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 164 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_uint8(values[i]));
        }
    }
    if (obj.has("is_dense")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["is_dense"])),
            parent_off + 172);
    }
}

inline godot::PackedByteArray godot_to_pdu_PointCloud2(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_PointCloud2(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::sensor_msgs
