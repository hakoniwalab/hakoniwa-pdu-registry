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
#include "ev3_msgs/pdu_conv_Ev3PduSensorHeader.hpp"
#include "ev3_msgs/pdu_conv_Ev3PduColorSensor.hpp"
#include "ev3_msgs/pdu_conv_Ev3PduTouchSensor.hpp"

namespace hako::godot_pdu::ev3_msgs {

inline void binary_read_recursive_Ev3PduSensor(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    {
        godot::Dictionary child;
        hako::godot_pdu::ev3_msgs::binary_read_recursive_Ev3PduSensorHeader(
            meta, binary_data, child, base_off + 0);
        obj["head"] = child;
    }
    {
        godot::PackedByteArray values;
        for (int32_t i = 0; i < 1; ++i) {
            values.append(hako::godot_runtime::read_uint8(
                binary_data, base_off + 152 + (i * 1)));
        }
        obj["buttons"] = values;
    }
    {
        godot::Array values;
        for (int32_t i = 0; i < 2; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::ev3_msgs::binary_read_recursive_Ev3PduColorSensor(
                meta, binary_data, child, base_off + 156 + (i * 20));
            values.append(child);
        }
        obj["color_sensors"] = values;
    }
    {
        godot::Array values;
        for (int32_t i = 0; i < 2; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::ev3_msgs::binary_read_recursive_Ev3PduTouchSensor(
                meta, binary_data, child, base_off + 196 + (i * 4));
            values.append(child);
        }
        obj["touch_sensors"] = values;
    }
    {
        godot::Array values;
        for (int32_t i = 0; i < 3; ++i) {
            values.append(hako::godot_runtime::read_uint32(
                binary_data, base_off + 204 + (i * 4)));
        }
        obj["motor_angle"] = values;
    }
    obj["gyro_degree"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 216);
    obj["gyro_degree_rate"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 220);
    obj["sensor_ultrasonic"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 224);
    obj["gps_lat"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 232);
    obj["gps_lon"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 240);
}

inline godot::Dictionary pdu_to_godot_Ev3PduSensor(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Ev3PduSensor(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Ev3PduSensor(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 248);
    if (obj.has("head")) {
        hako::godot_pdu::ev3_msgs::binary_write_recursive_Ev3PduSensorHeader(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["head"]));
    }
    if (obj.has("buttons")) {
        godot::PackedByteArray values = hako::godot_runtime::variant_to_packed_byte_array(obj["buttons"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 1);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_uint8(values[i]),
                parent_off + 152 + (i * 1));
        }
    }
    if (obj.has("color_sensors")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["color_sensors"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 2);
        for (int32_t i = 0; i < value_count; ++i) {
            hako::godot_pdu::ev3_msgs::binary_write_recursive_Ev3PduColorSensor(
                parent_off + 156 + (i * 20),
                writer,
                allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
    if (obj.has("touch_sensors")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["touch_sensors"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 2);
        for (int32_t i = 0; i < value_count; ++i) {
            hako::godot_pdu::ev3_msgs::binary_write_recursive_Ev3PduTouchSensor(
                parent_off + 196 + (i * 4),
                writer,
                allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
    if (obj.has("motor_angle")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["motor_angle"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 3);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_uint32(hako::godot_runtime::variant_to_uint32(values[i])),
                parent_off + 204 + (i * 4));
        }
    }
    if (obj.has("gyro_degree")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["gyro_degree"])),
            parent_off + 216);
    }
    if (obj.has("gyro_degree_rate")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["gyro_degree_rate"])),
            parent_off + 220);
    }
    if (obj.has("sensor_ultrasonic")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["sensor_ultrasonic"])),
            parent_off + 224);
    }
    if (obj.has("gps_lat")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["gps_lat"])),
            parent_off + 232);
    }
    if (obj.has("gps_lon")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["gps_lon"])),
            parent_off + 240);
    }
}

inline godot::PackedByteArray godot_to_pdu_Ev3PduSensor(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Ev3PduSensor(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::ev3_msgs
