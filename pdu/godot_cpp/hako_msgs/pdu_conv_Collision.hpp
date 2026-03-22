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
#include "geometry_msgs/pdu_conv_Vector3.hpp"
#include "geometry_msgs/pdu_conv_Point.hpp"

namespace hako::godot_pdu::hako_msgs {

inline void binary_read_recursive_Collision(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
    obj["collision"] = hako::godot_runtime::read_bool(
        binary_data, base_off + 0);
    obj["contact_num"] = hako::godot_runtime::read_uint32(
        binary_data, base_off + 4);
    {
        godot::Dictionary child;
        hako::godot_pdu::geometry_msgs::binary_read_recursive_Vector3(
            meta, binary_data, child, base_off + 8);
        obj["relative_velocity"] = child;
    }
    {
        godot::Array values;
        for (int32_t i = 0; i < 10; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::geometry_msgs::binary_read_recursive_Point(
                meta, binary_data, child, base_off + 32 + (i * 24));
            values.append(child);
        }
        obj["contact_position"] = values;
    }
    obj["restitution_coefficient"] = hako::godot_runtime::read_float64(
        binary_data, base_off + 272);
}

inline godot::Dictionary pdu_to_godot_Collision(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_Collision(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_Collision(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + 280);
    if (obj.has("collision")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_bool(
                hako::godot_runtime::variant_to_bool(obj["collision"])),
            parent_off + 0);
    }
    if (obj.has("contact_num")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_uint32(
                hako::godot_runtime::variant_to_uint32(obj["contact_num"])),
            parent_off + 4);
    }
    if (obj.has("relative_velocity")) {
        hako::godot_pdu::geometry_msgs::binary_write_recursive_Vector3(
            parent_off + 8,
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["relative_velocity"]));
    }
    if (obj.has("contact_position")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["contact_position"]);
        const int32_t value_count = std::min<int32_t>(values.size(), 10);
        for (int32_t i = 0; i < value_count; ++i) {
            hako::godot_pdu::geometry_msgs::binary_write_recursive_Point(
                parent_off + 32 + (i * 24),
                writer,
                allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
    if (obj.has("restitution_coefficient")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_float64(
                hako::godot_runtime::variant_to_float64(obj["restitution_coefficient"])),
            parent_off + 272);
    }
}

inline godot::PackedByteArray godot_to_pdu_Collision(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_Collision(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::hako_msgs
