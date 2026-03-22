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

inline void binary_read_recursive_Image(
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
    obj["encoding"] = hako::godot_runtime::read_string(
        binary_data, base_off + 144, 128);
    obj["is_bigendian"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 272);
    obj["step"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 276);
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 280);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 280 + 4);
        godot::PackedByteArray values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_uint8(
                binary_data, meta.heap_off + offset_from_heap + (i * 1)));
        }
        obj["data"] = values;
    }
}

inline godot::Dictionary pdu_to_godot_Image(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Image(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Image(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 281);
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
    if (obj.has("encoding")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["encoding"]), 128),
            parent_off + 144);
    }
    if (obj.has("is_bigendian")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["is_bigendian"])),
            parent_off + 272);
    }
    if (obj.has("step")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["step"])),
            parent_off + 276);
    }
    if (obj.has("data")) {
        godot::PackedByteArray values = hako::godot_runtime::variant_to_packed_byte_array(obj["data"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 280);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 280 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_uint8(values[i]));
        }
    }
}

inline godot::PackedByteArray godot_to_pdu_Image(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Image(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::sensor_msgs
