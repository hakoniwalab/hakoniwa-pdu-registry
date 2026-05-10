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
#include "sensor_msgs/pdu_conv_NavSatStatus.hpp"

namespace hako::godot_pdu::sensor_msgs {

inline void binary_read_recursive_NavSatFix(
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
        hako::godot_pdu::sensor_msgs::binary_read_recursive_NavSatStatus(
            meta, binary_data, child, base_off + 136);
        obj["status"] = child;
    }
    obj["latitude"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 144);
    obj["longitude"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 152);
    obj["altitude"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 160);
    {
        godot::PackedFloat64Array values;
        for (int32_t i = 0; i < 9; ++i) {
            values.append(hako::godot_runtime::read_float64(
                binary_data, base_off + 168 + (i * 8)));
        }
        obj["position_covariance"] = values;
    }
    obj["position_covariance_type"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 240);
}

inline godot::Dictionary pdu_to_godot_NavSatFix(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_NavSatFix(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_NavSatFix(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 241);
    if (obj.has("header")) {
        hako::godot_pdu::std_msgs::binary_write_recursive_Header(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("status")) {
        hako::godot_pdu::sensor_msgs::binary_write_recursive_NavSatStatus(
            parent_off + 136,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["status"]));
    }
    if (obj.has("latitude")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["latitude"])),
            parent_off + 144);
    }
    if (obj.has("longitude")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["longitude"])),
            parent_off + 152);
    }
    if (obj.has("altitude")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["altitude"])),
            parent_off + 160);
    }
    if (obj.has("position_covariance")) {
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["position_covariance"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 9);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_float64(values[i]),
                parent_off + 168 + (i * 8));
        }
    }
    if (obj.has("position_covariance_type")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["position_covariance_type"])),
            parent_off + 240);
    }
}

inline godot::PackedByteArray godot_to_pdu_NavSatFix(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_NavSatFix(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::sensor_msgs
