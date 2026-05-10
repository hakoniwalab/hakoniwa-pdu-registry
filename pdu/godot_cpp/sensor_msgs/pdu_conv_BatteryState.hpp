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

namespace hako::godot_pdu::sensor_msgs {

inline void binary_read_recursive_BatteryState(
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
    obj["voltage"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 136);
    obj["temperature"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 140);
    obj["current"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 144);
    obj["charge"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 148);
    obj["capacity"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 152);
    obj["design_capacity"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 156);
    obj["percentage"] = hako::godot_runtime::read_float32(
        binary_data, base_off + 160);
    obj["power_supply_status"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 164);
    obj["power_supply_health"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 165);
    obj["power_supply_technology"] = hako::godot_runtime::read_uint8(
        binary_data, base_off + 166);
    obj["present"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 168);
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 172);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 172 + 4);
        godot::PackedFloat32Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float32(
                binary_data, meta.heap_off + offset_from_heap + (i * 4)));
        }
        obj["cell_voltage"] = values;
    }
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + 180);
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + 180 + 4);
        godot::PackedFloat32Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_float32(
                binary_data, meta.heap_off + offset_from_heap + (i * 4)));
        }
        obj["cell_temperature"] = values;
    }
    obj["location"] = hako::godot_runtime::read_string(
        binary_data, base_off + 188, 128);
    obj["serial_number"] = hako::godot_runtime::read_string(
        binary_data, base_off + 316, 128);
}

inline godot::Dictionary pdu_to_godot_BatteryState(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_BatteryState(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_BatteryState(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 444);
    if (obj.has("header")) {
        hako::godot_pdu::std_msgs::binary_write_recursive_Header(
            parent_off + 0,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["header"]));
    }
    if (obj.has("voltage")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["voltage"])),
            parent_off + 136);
    }
    if (obj.has("temperature")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["temperature"])),
            parent_off + 140);
    }
    if (obj.has("current")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["current"])),
            parent_off + 144);
    }
    if (obj.has("charge")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["charge"])),
            parent_off + 148);
    }
    if (obj.has("capacity")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["capacity"])),
            parent_off + 152);
    }
    if (obj.has("design_capacity")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["design_capacity"])),
            parent_off + 156);
    }
    if (obj.has("percentage")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float32(
                hako::godot_runtime::variant_to_float32(obj["percentage"])),
            parent_off + 160);
    }
    if (obj.has("power_supply_status")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["power_supply_status"])),
            parent_off + 164);
    }
    if (obj.has("power_supply_health")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["power_supply_health"])),
            parent_off + 165);
    }
    if (obj.has("power_supply_technology")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint8(
                hako::godot_runtime::variant_to_uint8(obj["power_supply_technology"])),
            parent_off + 166);
    }
    if (obj.has("present")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["present"])),
            parent_off + 168);
    }
    if (obj.has("cell_voltage")) {
        godot::PackedFloat32Array values = hako::godot_runtime::variant_to_packed_float32_array(obj["cell_voltage"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 172);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 172 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float32(values[i]));
        }
    }
    if (obj.has("cell_temperature")) {
        godot::PackedFloat32Array values = hako::godot_runtime::variant_to_packed_float32_array(obj["cell_temperature"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + 180);
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + 180 + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_float32(values[i]));
        }
    }
    if (obj.has("location")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["location"]), 128),
            parent_off + 188);
    }
    if (obj.has("serial_number")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_string(
                hako::godot_runtime::variant_to_string(obj["serial_number"]), 128),
            parent_off + 316);
    }
}

inline godot::PackedByteArray godot_to_pdu_BatteryState(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_BatteryState(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::sensor_msgs
