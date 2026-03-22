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

namespace hako::godot_pdu::hako_msgs {

inline void binary_read_recursive_GameControllerOperation(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < 6; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, base_off + 0 + (i * 8)));
        }
        obj["axis"] = values;
    }
    {
        godot::Array values;
        for (int32_t i = 0; i < 15; ++i) {
            values.append(hako::godot_runtime::read_bool(
                binary_data, base_off + 48 + (i * 4)));
        }
        obj["button"] = values;
    }
}

inline godot::Dictionary pdu_to_godot_GameControllerOperation(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_GameControllerOperation(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_GameControllerOperation(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 108);
    if (obj.has("axis")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["axis"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 6);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]),
                parent_off + 0 + (i * 8));
        }
    }
    if (obj.has("button")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["button"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 15);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_bool(hako::godot_runtime::variant_to_bool(values[i])),
                parent_off + 48 + (i * 4));
        }
    }
}

inline godot::PackedByteArray godot_to_pdu_GameControllerOperation(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_GameControllerOperation(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
