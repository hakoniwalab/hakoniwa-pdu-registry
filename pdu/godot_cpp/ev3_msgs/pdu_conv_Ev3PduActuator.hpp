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
#include "ev3_msgs/pdu_conv_Ev3PduActuatorHeader.hpp"
#include "ev3_msgs/pdu_conv_Ev3PduMotor.hpp"

namespace hako::godot_pdu::ev3_msgs {

inline void binary_read_recursive_Ev3PduActuator(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::ev3_msgs::binary_read_recursive_Ev3PduActuatorHeader(
            meta, binary_data, child, base_off + 0);
        obj["head"] = child;
    }
    {
        godot::PackedByteArray values;
        for (int32_t i = 0; i < 1; ++i) {
            values.append(hako::godot_runtime::read_uint8(
                binary_data, base_off + 152 + (i * 1)));
        }
        obj["leds"] = values;
    }
    {
        godot::Array values;
        for (int32_t i = 0; i < 3; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::ev3_msgs::binary_read_recursive_Ev3PduMotor(
                meta, binary_data, child, base_off + 156 + (i * 12));
            values.append(child);
        }
        obj["motors"] = values;
    }
    obj["gyro_reset"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 192);
}

inline godot::Dictionary pdu_to_godot_Ev3PduActuator(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Ev3PduActuator(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Ev3PduActuator(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 196);
    if (obj.has("head")) {
        hako::godot_pdu::ev3_msgs::binary_write_recursive_Ev3PduActuatorHeader(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["head"]));
    }
    if (obj.has("leds")) {
        godot::PackedByteArray values = hako::godot_runtime::variant_to_packed_byte_array(obj["leds"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 1);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_uint8(values[i]),
                parent_off + 152 + (i * 1));
        }
    }
    if (obj.has("motors")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["motors"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 3);
        for (int32_t i = 0; i < value_count; ++i) {
            hako::godot_pdu::ev3_msgs::binary_write_recursive_Ev3PduMotor(
                parent_off + 156 + (i * 12),
                writer,
                allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
    if (obj.has("gyro_reset")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["gyro_reset"])),
            parent_off + 192);
    }
}

inline godot::PackedByteArray godot_to_pdu_Ev3PduActuator(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Ev3PduActuator(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::ev3_msgs
