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

namespace hako::godot_pdu::ev3_msgs {

inline void binary_read_recursive_Ev3PduSensorHeader(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["name"] = hako::godot_runtime::read_string(
        binary_data, base_off + 0, 128);
    obj["version"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 128);
    obj["hakoniwa_time"] = hako::godot_runtime::read_int64(
        binary_data, base_off + 136);
    obj["ext_off"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 144);
    obj["ext_size"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 148);
}

inline godot::Dictionary pdu_to_godot_Ev3PduSensorHeader(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Ev3PduSensorHeader(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Ev3PduSensorHeader(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 152);
    if (obj.has("name")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["name"]), 128),
            parent_off + 0);
    }
    if (obj.has("version")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["version"])),
            parent_off + 128);
    }
    if (obj.has("hakoniwa_time")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int64(
                hako::godot_runtime::variant_to_int64(obj["hakoniwa_time"])),
            parent_off + 136);
    }
    if (obj.has("ext_off")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["ext_off"])),
            parent_off + 144);
    }
    if (obj.has("ext_size")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["ext_size"])),
            parent_off + 148);
    }
}

inline godot::PackedByteArray godot_to_pdu_Ev3PduSensorHeader(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Ev3PduSensorHeader(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::ev3_msgs
