using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.{{ container.pkg_name }};
{%- for item in container.cs_conv_imports %}
using Hakoniwa.Pdu.CSharpV2.{{ item.dep_pkg }};
{%- endfor %}

namespace Hakoniwa.Pdu.CSharpV2.{{ container.pkg_name }}
{
    public static class {{ container.msg_type_name }}Converter
    {
        public static {{ container.msg_type_name }} PduToMsg(byte[] binaryData)
        {
            var obj = new {{ container.msg_type_name }}();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu({{ container.msg_type_name }} obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, {{ container.msg_type_name }} obj, int baseOff)
        {
{%- for item in container.offset_data %}
{%- if item.data_type == 'primitive' %}
    {%- if item.array_type == 'single' %}
            obj.{{ item.member_name }} = PduRuntime.Read{{ container.get_csharp_io_suffix(item.type_name) }}(binaryData, baseOff + {{ item.offset }}{% if item.type_name == 'string' %}, {{ item.size }}{% endif %});
    {%- elif item.array_type == 'array' %}
            obj.{{ item.member_name }} = new {{ container.get_csharp_v2_type_hint(item.type_name + "[]") }}();
    {%- set array_type = container.get_array_type(item.type_name) %}
    {%- set elm_size = item.size // item.array_len %}
            for (var i = 0; i < {{ item.array_len }}; i++) {
                obj.{{ item.member_name }}.Add(PduRuntime.Read{{ container.get_csharp_io_suffix(array_type) }}(binaryData, baseOff + {{ item.offset }} + (i * {{ elm_size }}){% if array_type == 'string' %}, {{ elm_size }}{% endif %}));
            }
    {%- else %}
            obj.{{ item.member_name }} = new {{ container.get_csharp_v2_type_hint(item.type_name + "[]") }}();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + {{ item.offset }});
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + {{ item.offset }} + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.{{ item.member_name }}.Add(PduRuntime.Read{{ container.get_csharp_io_suffix(item.type_name) }}(binaryData, meta.HeapOff + offsetFromHeap + (i * {{ item.size }}){% if item.type_name == 'string' %}, {{ item.size }}{% endif %}));
                }
            }
    {%- endif %}
{%- else %}
    {%- if item.array_type == 'single' %}
            obj.{{ item.member_name }} = new {{ container.get_msg_type(item.type_name) }}();
            {{ container.get_msg_type(item.type_name) }}Converter.BinaryReadRecursive(meta, binaryData, obj.{{ item.member_name }}, baseOff + {{ item.offset }});
    {%- elif item.array_type == 'array' %}
            obj.{{ item.member_name }} = new {{ container.get_csharp_v2_type_hint(item.type_name + "[]") }}();
    {%- set one_elm_size = item.size // item.array_len %}
            for (var i = 0; i < {{ item.array_len }}; i++) {
                var tmp = new {{ container.get_msg_type(item.type_name) }}();
                {{ container.get_msg_type(item.type_name) }}Converter.BinaryReadRecursive(meta, binaryData, tmp, baseOff + {{ item.offset }} + (i * {{ one_elm_size }}));
                obj.{{ item.member_name }}.Add(tmp);
            }
    {%- else %}
            obj.{{ item.member_name }} = new {{ container.get_csharp_v2_type_hint(item.type_name + "[]") }}();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + {{ item.offset }});
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + {{ item.offset }} + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new {{ container.get_msg_type(item.type_name) }}();
                    {{ container.get_msg_type(item.type_name) }}Converter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * {{ item.size }}));
                    obj.{{ item.member_name }}.Add(tmp);
                }
            }
    {%- endif %}
{%- endif %}
{%- endfor %}
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, {{ container.msg_type_name }} obj)
        {
{%- for item in container.offset_data %}
{%- if item.data_type == 'primitive' %}
    {%- if item.array_type == 'single' %}
            allocator.Add(PduRuntime.GetBinaryFor{{ container.get_csharp_io_suffix(item.type_name) }}(obj.{{ item.member_name }}{% if item.type_name == 'string' %}, {{ item.size }}{% endif %}), parentOff + {{ item.offset }});
    {%- elif item.array_type == 'array' %}
    {%- set array_type = container.get_array_type(item.type_name) %}
    {%- set elm_size = item.size // item.array_len %}
            for (var i = 0; i < obj.{{ item.member_name }}.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryFor{{ container.get_csharp_io_suffix(array_type) }}(obj.{{ item.member_name }}[i]{% if array_type == 'string' %}, {{ elm_size }}{% endif %}), parentOff + {{ item.offset }} + (i * {{ elm_size }}));
            }
    {%- else %}
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.{{ item.member_name }}.Count), parentOff + {{ item.offset }});
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + {{ item.offset }} + 4);
                for (var i = 0; i < obj.{{ item.member_name }}.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryFor{{ container.get_csharp_io_suffix(item.type_name) }}(obj.{{ item.member_name }}[i]{% if item.type_name == 'string' %}, {{ item.size }}{% endif %}));
                }
            }
    {%- endif %}
{%- else %}
    {%- if item.array_type == 'single' %}
            {{ container.get_msg_type(item.type_name) }}Converter.BinaryWriteRecursive(parentOff + {{ item.offset }}, writer, allocator, obj.{{ item.member_name }});
    {%- elif item.array_type == 'array' %}
    {%- set one_elm_size = item.size // item.array_len %}
            for (var i = 0; i < obj.{{ item.member_name }}.Count; i++) {
                {{ container.get_msg_type(item.type_name) }}Converter.BinaryWriteRecursive(parentOff + {{ item.offset }} + (i * {{ one_elm_size }}), writer, allocator, obj.{{ item.member_name }}[i]);
            }
    {%- else %}
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.{{ item.member_name }}.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + {{ item.offset }});
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + {{ item.offset }} + 4);
                writer.HeapAllocator.Add(new byte[arraySize * {{ item.size }}], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    {{ container.get_msg_type(item.type_name) }}Converter.BinaryWriteRecursive(offsetFromHeap + (i * {{ item.size }}), writer, writer.HeapAllocator, obj.{{ item.member_name }}[i]);
                }
            }
    {%- endif %}
{%- endif %}
{%- endfor %}
        }
    }
}
