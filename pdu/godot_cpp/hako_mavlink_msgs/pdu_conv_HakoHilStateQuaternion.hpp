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

namespace hako::godot_pdu::hako_mavlink_msgs {

inline void binary_read_recursive_HakoHilStateQuaternion(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["time_usec"] = hako::godot_runtime::read_uint64(
        binary_data, base_off + 0);
    {
        godot::PackedFloat32Array values;
        for (int32_t i = 0; i < 4; ++i) {
            values.append(hako::godot_runtime::read_float32(
                binary_data, base_off + 8 + (i * 4)));
        }
        obj["attitude_quaternion"] = values;
    }
    obj["rollspeed"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 24);
    obj["pitchspeed"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 28);
    obj["yawspeed"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 32);
    obj["lat"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 36);
    obj["lon"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 40);
    obj["alt"] = hako::godot_runtime::read_int32(
        binary_data, base_off + 44);
    obj["vx"] = hako::godot_runtime::read_int16(
        binary_data, base_off + 48);
    obj["vy"] = hako::godot_runtime::read_int16(
        binary_data, base_off + 50);
    obj["vz"] = hako::godot_runtime::read_int16(
        binary_data, base_off + 52);
    obj["ind_airspeed"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 54);
    obj["true_airspeed"] = hako::godot_runtime::read_uint16(
        binary_data, base_off + 56);
    obj["xacc"] = hako::godot_runtime::read_int16(
        binary_data, base_off + 58);
    obj["yacc"] = hako::godot_runtime::read_int16(
        binary_data, base_off + 60);
    obj["zacc"] = hako::godot_runtime::read_int16(
        binary_data, base_off + 62);
}

inline godot::Dictionary pdu_to_godot_HakoHilStateQuaternion(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_HakoHilStateQuaternion(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_HakoHilStateQuaternion(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 64);
    if (obj.has("time_usec")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint64(
                hako::godot_runtime::variant_to_uint64(obj["time_usec"])),
            parent_off + 0);
    }
    if (obj.has("attitude_quaternion")) {
        godot::PackedFloat32Array values = hako::godot_runtime::variant_to_packed_float32_array(obj["attitude_quaternion"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 4);
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_float32(values[i]),
                parent_off + 8 + (i * 4));
        }
    }
    if (obj.has("rollspeed")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["rollspeed"])),
            parent_off + 24);
    }
    if (obj.has("pitchspeed")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["pitchspeed"])),
            parent_off + 28);
    }
    if (obj.has("yawspeed")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["yawspeed"])),
            parent_off + 32);
    }
    if (obj.has("lat")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["lat"])),
            parent_off + 36);
    }
    if (obj.has("lon")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["lon"])),
            parent_off + 40);
    }
    if (obj.has("alt")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int32(
                hako::godot_runtime::variant_to_int32(obj["alt"])),
            parent_off + 44);
    }
    if (obj.has("vx")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int16(
                hako::godot_runtime::variant_to_int16(obj["vx"])),
            parent_off + 48);
    }
    if (obj.has("vy")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int16(
                hako::godot_runtime::variant_to_int16(obj["vy"])),
            parent_off + 50);
    }
    if (obj.has("vz")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int16(
                hako::godot_runtime::variant_to_int16(obj["vz"])),
            parent_off + 52);
    }
    if (obj.has("ind_airspeed")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["ind_airspeed"])),
            parent_off + 54);
    }
    if (obj.has("true_airspeed")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint16(
                hako::godot_runtime::variant_to_uint16(obj["true_airspeed"])),
            parent_off + 56);
    }
    if (obj.has("xacc")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int16(
                hako::godot_runtime::variant_to_int16(obj["xacc"])),
            parent_off + 58);
    }
    if (obj.has("yacc")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int16(
                hako::godot_runtime::variant_to_int16(obj["yacc"])),
            parent_off + 60);
    }
    if (obj.has("zacc")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_int16(
                hako::godot_runtime::variant_to_int16(obj["zacc"])),
            parent_off + 62);
    }
}

inline godot::PackedByteArray godot_to_pdu_HakoHilStateQuaternion(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_HakoHilStateQuaternion(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_mavlink_msgs
