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
#include "geometry_msgs/pdu_conv_Transform.hpp"
#include "geometry_msgs/pdu_conv_Twist.hpp"

namespace hako::godot_pdu::hako_srv_msgs {

inline void binary_read_recursive_AckermannStepResponse(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["step"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 0);
    obj["result_code"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 8);
    obj["sim_time_usec"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 16);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Transform(
            meta, binary_data, child, base_off + 24);
        obj["pose"] = child;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Twist(
            meta, binary_data, child, base_off + 80);
        obj["twist"] = child;
    }
}

inline godot::Dictionary pdu_to_godot_AckermannStepResponse(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_AckermannStepResponse(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_AckermannStepResponse(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 128);
    if (obj.has("step")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["step"])),
            parent_off + 0);
    }
    if (obj.has("result_code")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["result_code"])),
            parent_off + 8);
    }
    if (obj.has("sim_time_usec")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["sim_time_usec"])),
            parent_off + 16);
    }
    if (obj.has("pose")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Transform(
            parent_off + 24,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["pose"]));
    }
    if (obj.has("twist")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Twist(
            parent_off + 80,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["twist"]));
    }
}

inline godot::PackedByteArray godot_to_pdu_AckermannStepResponse(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_AckermannStepResponse(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_srv_msgs
