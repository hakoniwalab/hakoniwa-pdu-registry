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
#include "std_msgs/pdu_conv_MultiArrayLayout.hpp"

namespace hako::godot_pdu::std_msgs {

inline void binary_read_recursive_Int16MultiArray(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::std_msgs::binary_read_recursive_MultiArrayLayout(
            meta, binary_data, child, base_off + 0);
        obj["layout"] = child;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 12);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 12 + 4);
        godot::Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_int16(
                binary_data, meta.heap_off + offset_from_heap + (i * 2)));
        }
        obj["data"] = values;
    }
}

inline godot::Dictionary pdu_to_godot_Int16MultiArray(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Int16MultiArray(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Int16MultiArray(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 14);
    if (obj.has("layout")) {
        hako::godot_pdu::std_msgs::binary_write_recursive_MultiArrayLayout(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["layout"]));
    }
    if (obj.has("data")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["data"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 12);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 12 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_int16(hako::godot_runtime::variant_to_int16(values[i])));
        }
    }
}

inline godot::PackedByteArray godot_to_pdu_Int16MultiArray(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Int16MultiArray(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::std_msgs
