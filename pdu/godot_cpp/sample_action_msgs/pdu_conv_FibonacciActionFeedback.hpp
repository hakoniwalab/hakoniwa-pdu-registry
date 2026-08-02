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
#include "hako_action_msgs/pdu_conv_ActionFeedbackHeader.hpp"
#include "sample_action_msgs/pdu_conv_FibonacciFeedback.hpp"

namespace hako::godot_pdu::sample_action_msgs {

inline void binary_read_recursive_FibonacciActionFeedback(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::hako_action_msgs::binary_read_recursive_ActionFeedbackHeader(
            meta, binary_data, child, base_off + 0);
        obj["header"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::sample_action_msgs::binary_read_recursive_FibonacciFeedback(
            meta, binary_data, child, base_off + 24);
        obj["body"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_FibonacciActionFeedback(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_FibonacciActionFeedback(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_FibonacciActionFeedback(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 32);
    if (obj.has("header")) {
        hako::godot_pdu::hako_action_msgs::binary_write_recursive_ActionFeedbackHeader(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("body")) {
        hako::godot_pdu::sample_action_msgs::binary_write_recursive_FibonacciFeedback(
            parent_off + 24,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["body"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_FibonacciActionFeedback(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_FibonacciActionFeedback(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::sample_action_msgs
