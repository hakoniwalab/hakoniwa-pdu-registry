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
#include "geometry_msgs/pdu_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_conv_Vector3.hpp"

namespace hako::godot_pdu::sensor_msgs {

inline void binary_read_recursive_Imu(
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
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Quaternion(
            meta, binary_data, child, base_off + 136);
        obj["orientation"] = child;
    }
    {
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < 9; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, base_off + 168 + (i * 8)));
        }
        obj["orientation_covariance"] = values;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 240);
        obj["angular_velocity"] = child;
    }
    {
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < 9; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, base_off + 264 + (i * 8)));
        }
        obj["angular_velocity_covariance"] = values;
    }
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 336);
        obj["linear_acceleration"] = child;
    }
    {
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < 9; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, base_off + 360 + (i * 8)));
        }
        obj["linear_acceleration_covariance"] = values;
    }
}

inline godot::Dictionary pdu_to_godot_Imu(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Imu(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Imu(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 432);
    if (obj.has("header")) {
        hako::godot_pdu::std_msgs::binary_write_recursive_Header(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("orientation")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Quaternion(
            parent_off + 136,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["orientation"]));
    }
    if (obj.has("orientation_covariance")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["orientation_covariance"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 9);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]),
                parent_off + 168 + (i * 8));
        }
    }
    if (obj.has("angular_velocity")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 240,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["angular_velocity"]));
    }
    if (obj.has("angular_velocity_covariance")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["angular_velocity_covariance"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 9);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]),
                parent_off + 264 + (i * 8));
        }
    }
    if (obj.has("linear_acceleration")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 336,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["linear_acceleration"]));
    }
    if (obj.has("linear_acceleration_covariance")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["linear_acceleration_covariance"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 9);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]),
                parent_off + 360 + (i * 8));
        }
    }
}

inline godot::PackedByteArray godot_to_pdu_Imu(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Imu(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::sensor_msgs
