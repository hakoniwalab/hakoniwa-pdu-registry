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
{%- for item in container.godot_cpp_imports %}
#include "{{ item.dep_pkg }}/pdu_conv_{{ item.msg_type }}.hpp"
{%- endfor %}

namespace hako::godot_pdu::{{ container.pkg_name }} {

inline void binary_read_recursive_{{ container.msg_type_name }}(
    const hako::godot_runtime::PduMetaData &meta,
    const godot::PackedByteArray &binary_data,
    godot::Dictionary &obj,
    int32_t base_off)
{
{%- for item in container.offset_data %}
{%- if item.data_type == 'primitive' %}
    {%- if item.array_type == 'single' %}
    obj["{{ item.member_name }}"] = hako::godot_runtime::read_{{ container.get_godot_io_suffix(item.type_name).lower() }}(
        binary_data, base_off + {{ item.offset }}{% if item.type_name == 'string' %}, {{ item.size }}{% endif %});
    {%- elif item.array_type == 'array' %}
    {
        {%- set array_type = container.get_array_type(item.type_name) %}
        {%- set container_type = container.get_godot_cpp_array_container(item.type_name) %}
        {%- set elm_size = item.size // item.array_len %}
        godot::{{ container_type }} values;
        for (int32_t i = 0; i < {{ item.array_len }}; ++i) {
            values.append(hako::godot_runtime::read_{{ container.get_godot_io_suffix(array_type).lower() }}(
                binary_data, base_off + {{ item.offset }} + (i * {{ elm_size }}){% if array_type == 'string' %}, {{ elm_size }}{% endif %}));
        }
        obj["{{ item.member_name }}"] = values;
    }
    {%- else %}
    {
        {%- set container_type = container.get_godot_cpp_array_container(item.type_name) %}
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + {{ item.offset }});
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + {{ item.offset }} + 4);
        godot::{{ container_type }} values;
        for (int32_t i = 0; i < array_size; ++i) {
            values.append(hako::godot_runtime::read_{{ container.get_godot_io_suffix(item.type_name).lower() }}(
                binary_data, meta.heap_off + offset_from_heap + (i * {{ item.size }}){% if item.type_name == 'string' %}, {{ item.size }}{% endif %}));
        }
        obj["{{ item.member_name }}"] = values;
    }
    {%- endif %}
{%- else %}
    {%- if item.array_type == 'single' %}
    {
        godot::Dictionary child;
        hako::godot_pdu::{{ container.get_msg_pkg(item.type_name) }}::binary_read_recursive_{{ container.get_msg_type(item.type_name) }}(
            meta, binary_data, child, base_off + {{ item.offset }});
        obj["{{ item.member_name }}"] = child;
    }
    {%- elif item.array_type == 'array' %}
    {
        {%- set one_elm_size = item.size // item.array_len %}
        godot::Array values;
        for (int32_t i = 0; i < {{ item.array_len }}; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::{{ container.get_msg_pkg(item.type_name) }}::binary_read_recursive_{{ container.get_msg_type(item.type_name) }}(
                meta, binary_data, child, base_off + {{ item.offset }} + (i * {{ one_elm_size }}));
            values.append(child);
        }
        obj["{{ item.member_name }}"] = values;
    }
    {%- else %}
    {
        const int32_t array_size = hako::godot_runtime::read_int32(binary_data, base_off + {{ item.offset }});
        const int32_t offset_from_heap = hako::godot_runtime::read_int32(binary_data, base_off + {{ item.offset }} + 4);
        godot::Array values;
        for (int32_t i = 0; i < array_size; ++i) {
            godot::Dictionary child;
            hako::godot_pdu::{{ container.get_msg_pkg(item.type_name) }}::binary_read_recursive_{{ container.get_msg_type(item.type_name) }}(
                meta, binary_data, child, meta.heap_off + offset_from_heap + (i * {{ item.size }}));
            values.append(child);
        }
        obj["{{ item.member_name }}"] = values;
    }
    {%- endif %}
{%- endif %}
{%- endfor %}
}

inline godot::Dictionary pdu_to_godot_{{ container.msg_type_name }}(const godot::PackedByteArray &binary_data)
{
    godot::Dictionary obj;
    hako::godot_runtime::PduMetaData meta;
    if (!hako::godot_runtime::PduMetaData::parse(binary_data, meta)) {
        return obj;
    }
    binary_read_recursive_{{ container.msg_type_name }}(meta, binary_data, obj, hako::godot_runtime::PduMetaData::PDU_META_DATA_SIZE);
    return obj;
}

inline void binary_write_recursive_{{ container.msg_type_name }}(
    int32_t parent_off,
    hako::godot_runtime::BinaryWriterContainer &writer,
    hako::godot_runtime::DynamicAllocator &allocator,
    const godot::Dictionary &obj)
{
    allocator.ensure_size(parent_off + {{ container.base_data_size }});
{%- for item in container.offset_data %}
{%- if item.data_type == 'primitive' %}
    {%- if item.array_type == 'single' %}
    if (obj.has("{{ item.member_name }}")) {
        allocator.add(
            hako::godot_runtime::get_binary_for_{{ container.get_godot_io_suffix(item.type_name).lower() }}(
                hako::godot_runtime::variant_to_{{ container.get_godot_io_suffix(item.type_name).lower() }}(obj["{{ item.member_name }}"]){% if item.type_name == 'string' %}, {{ item.size }}{% endif %}),
            parent_off + {{ item.offset }});
    }
    {%- elif item.array_type == 'array' %}
    if (obj.has("{{ item.member_name }}")) {
        {%- set array_type = container.get_array_type(item.type_name) %}
        {%- set container_type = container.get_godot_cpp_array_container(item.type_name) %}
        {%- set elm_size = item.size // item.array_len %}
        {%- if container_type == 'PackedByteArray' %}
        godot::PackedByteArray values = hako::godot_runtime::variant_to_packed_byte_array(obj["{{ item.member_name }}"]);
        {%- elif container_type == 'PackedInt32Array' %}
        godot::PackedInt32Array values = hako::godot_runtime::variant_to_packed_int32_array(obj["{{ item.member_name }}"]);
        {%- elif container_type == 'PackedInt64Array' %}
        godot::PackedInt64Array values = hako::godot_runtime::variant_to_packed_int64_array(obj["{{ item.member_name }}"]);
        {%- elif container_type == 'PackedFloat32Array' %}
        godot::PackedFloat32Array values = hako::godot_runtime::variant_to_packed_float32_array(obj["{{ item.member_name }}"]);
        {%- elif container_type == 'PackedFloat64Array' %}
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["{{ item.member_name }}"]);
        {%- else %}
        godot::Array values = hako::godot_runtime::variant_to_array(obj["{{ item.member_name }}"]);
        {%- endif %}
        const int32_t value_count = std::min<int32_t>(values.size(), {{ item.array_len }});
        for (int32_t i = 0; i < value_count; ++i) {
            allocator.add(
                hako::godot_runtime::get_binary_for_{{ container.get_godot_io_suffix(array_type).lower() }}(
                    {%- if container_type == 'Array' %}hako::godot_runtime::variant_to_{{ container.get_godot_io_suffix(array_type).lower() }}(values[i]){% else %}values[i]{% endif %}{% if array_type == 'string' %}, {{ elm_size }}{% endif %}),
                parent_off + {{ item.offset }} + (i * {{ elm_size }}));
        }
    }
    {%- else %}
    if (obj.has("{{ item.member_name }}")) {
        {%- set container_type = container.get_godot_cpp_array_container(item.type_name) %}
        {%- if container_type == 'PackedByteArray' %}
        godot::PackedByteArray values = hako::godot_runtime::variant_to_packed_byte_array(obj["{{ item.member_name }}"]);
        {%- elif container_type == 'PackedInt32Array' %}
        godot::PackedInt32Array values = hako::godot_runtime::variant_to_packed_int32_array(obj["{{ item.member_name }}"]);
        {%- elif container_type == 'PackedInt64Array' %}
        godot::PackedInt64Array values = hako::godot_runtime::variant_to_packed_int64_array(obj["{{ item.member_name }}"]);
        {%- elif container_type == 'PackedFloat32Array' %}
        godot::PackedFloat32Array values = hako::godot_runtime::variant_to_packed_float32_array(obj["{{ item.member_name }}"]);
        {%- elif container_type == 'PackedFloat64Array' %}
        godot::PackedFloat64Array values = hako::godot_runtime::variant_to_packed_float64_array(obj["{{ item.member_name }}"]);
        {%- else %}
        godot::Array values = hako::godot_runtime::variant_to_array(obj["{{ item.member_name }}"]);
        {%- endif %}
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + {{ item.offset }});
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + {{ item.offset }} + 4);
        for (int32_t i = 0; i < array_size; ++i) {
            writer.heap_allocator.add(
                hako::godot_runtime::get_binary_for_{{ container.get_godot_io_suffix(item.type_name).lower() }}(
                    {%- if container_type == 'Array' %}hako::godot_runtime::variant_to_{{ container.get_godot_io_suffix(item.type_name).lower() }}(values[i]){% else %}values[i]{% endif %}{% if item.type_name == 'string' %}, {{ item.size }}{% endif %}));
        }
    }
    {%- endif %}
{%- else %}
    {%- if item.array_type == 'single' %}
    if (obj.has("{{ item.member_name }}")) {
        hako::godot_pdu::{{ container.get_msg_pkg(item.type_name) }}::binary_write_recursive_{{ container.get_msg_type(item.type_name) }}(
            parent_off + {{ item.offset }},
            writer,
            allocator,
            hako::godot_runtime::variant_to_dictionary(obj["{{ item.member_name }}"]));
    }
    {%- elif item.array_type == 'array' %}
    if (obj.has("{{ item.member_name }}")) {
        {%- set one_elm_size = item.size // item.array_len %}
        godot::Array values = hako::godot_runtime::variant_to_array(obj["{{ item.member_name }}"]);
        const int32_t value_count = std::min<int32_t>(values.size(), {{ item.array_len }});
        for (int32_t i = 0; i < value_count; ++i) {
            hako::godot_pdu::{{ container.get_msg_pkg(item.type_name) }}::binary_write_recursive_{{ container.get_msg_type(item.type_name) }}(
                parent_off + {{ item.offset }} + (i * {{ one_elm_size }}),
                writer,
                allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
    {%- else %}
    if (obj.has("{{ item.member_name }}")) {
        godot::Array values = hako::godot_runtime::variant_to_array(obj["{{ item.member_name }}"]);
        const int32_t offset_from_heap = writer.heap_allocator.size();
        const int32_t array_size = values.size();
        allocator.add(hako::godot_runtime::get_binary_for_int32(array_size), parent_off + {{ item.offset }});
        allocator.add(hako::godot_runtime::get_binary_for_int32(offset_from_heap), parent_off + {{ item.offset }} + 4);
        writer.heap_allocator.add(hako::godot_runtime::zero_bytes(array_size * {{ item.size }}), offset_from_heap);
        for (int32_t i = 0; i < array_size; ++i) {
            hako::godot_pdu::{{ container.get_msg_pkg(item.type_name) }}::binary_write_recursive_{{ container.get_msg_type(item.type_name) }}(
                offset_from_heap + (i * {{ item.size }}),
                writer,
                writer.heap_allocator,
                hako::godot_runtime::variant_to_dictionary(values[i]));
        }
    }
    {%- endif %}
{%- endif %}
{%- endfor %}
}

inline godot::PackedByteArray godot_to_pdu_{{ container.msg_type_name }}(const godot::Dictionary &obj)
{
    hako::godot_runtime::DynamicAllocator base_allocator;
    hako::godot_runtime::BinaryWriterContainer writer;
    binary_write_recursive_{{ container.msg_type_name }}(0, writer, base_allocator, obj);
    return hako::godot_runtime::build_pdu(base_allocator, writer);
}

} // namespace hako::godot_pdu::{{ container.pkg_name }}
