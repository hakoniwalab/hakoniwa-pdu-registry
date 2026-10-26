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

namespace hako::godot_pdu::hako_srv_msgs {

inline void binary_read_recursive_SetLightRequest(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["source"] = hako::godot_runtime::read_string(
        binary_data, base_off + 0, 128);
    obj["mode"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 128);
    obj["luminous_intensity_scale"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 136);
    obj["flashing_on_s"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 144);
    obj["flashing_off_s"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 152);
    obj["transition_s"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 160);
}

inline godot::Dictionary pdu_to_godot_SetLightRequest(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_SetLightRequest(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_SetLightRequest(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 168);
    if (obj.has("source")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["source"]), 128),
            parent_off + 0);
    }
    if (obj.has("mode")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["mode"])),
            parent_off + 128);
    }
    if (obj.has("luminous_intensity_scale")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["luminous_intensity_scale"])),
            parent_off + 136);
    }
    if (obj.has("flashing_on_s")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["flashing_on_s"])),
            parent_off + 144);
    }
    if (obj.has("flashing_off_s")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["flashing_off_s"])),
            parent_off + 152);
    }
    if (obj.has("transition_s")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["transition_s"])),
            parent_off + 160);
    }
}

inline godot::PackedByteArray godot_to_pdu_SetLightRequest(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_SetLightRequest(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_srv_msgs
