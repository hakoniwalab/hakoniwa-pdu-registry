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

namespace hako::godot_pdu::hako_action_msgs {

inline void binary_read_recursive_ActionRequestHeader(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["version"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 0);
    obj["request_kind"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 1);
    {
        godot::PackedByteArray values;
        for (int32_t i = 0; i < 2; ++i) {
            values.append(hako::godot_runtime::read_uint8(
                binary_data, base_off + 2 + (i * 1)));
        }
        obj["reserved"] = values;
    }
    {
        godot::PackedByteArray values;
        for (int32_t i = 0; i < 16; ++i) {
            values.append(hako::godot_runtime::read_uint8(
                binary_data, base_off + 4 + (i * 1)));
        }
        obj["goal_id"] = values;
    }
}

inline godot::Dictionary pdu_to_godot_ActionRequestHeader(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_ActionRequestHeader(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_ActionRequestHeader(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 20);
    if (obj.has("version")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["version"])),
            parent_off + 0);
    }
    if (obj.has("request_kind")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["request_kind"])),
            parent_off + 1);
    }
    if (obj.has("reserved")) {
        godot::PackedByteArray values = hako::godot_runtime::variant_to_packed_byte_array(obj["reserved"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 2);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_uint8(values[i]),
                parent_off + 2 + (i * 1));
        }
    }
    if (obj.has("goal_id")) {
        godot::PackedByteArray values = hako::godot_runtime::variant_to_packed_byte_array(obj["goal_id"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 16);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_uint8(values[i]),
                parent_off + 4 + (i * 1));
        }
    }
}

inline godot::PackedByteArray godot_to_pdu_ActionRequestHeader(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_ActionRequestHeader(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_action_msgs
