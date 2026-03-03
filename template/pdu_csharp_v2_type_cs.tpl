using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

{%- for item in container.csharp_includes %}
using Hakoniwa.Pdu.CSharpV2.{{ item }};
{%- endfor %}

namespace Hakoniwa.Pdu.CSharpV2.{{ container.pkg_name }}
{
    public class {{ container.msg_type_name }}
    {
{%- for field in container.json_data["fields"] %}
        public {{ container.get_csharp_v2_type_hint(field.type) }} {{ field.name }} { get; set; } = {{ container.get_csharp_v2_default_value(field.type) }};
{%- endfor %}

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
{%- for field in container.json_data["fields"] %}
            dict["{{ field.name }}"] = ToSerializableValue({{ field.name }});
{%- endfor %}
            return dict;
        }

        public static {{ container.msg_type_name }} FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new {{ container.msg_type_name }}();
{%- for field in container.json_data["fields"] %}
            if (dict.TryGetValue("{{ field.name }}", out var {{ field.name }}Value))
            {
    {%- if container.is_array(field.type) %}
        {%- set array_type = container.get_array_type(field.type) %}
        {%- if container.is_primitive(array_type) or container.is_string(array_type) %}
                obj.{{ field.name }} = PduRuntime.ConvertList<{{ container.get_csharp_type(array_type) }}>({{ field.name }}Value);
        {%- else %}
                obj.{{ field.name }} = PduRuntime.ConvertObjectList<{{ container.get_msg_type(array_type) }}>({{ field.name }}Value, item => {{ container.get_msg_type(array_type) }}.FromDictionary(item));
        {%- endif %}
    {%- elif container.is_primitive(field.type) or container.is_string(field.type) %}
                obj.{{ field.name }} = PduRuntime.ConvertValue<{{ container.get_csharp_type(field.type) }}>({{ field.name }}Value);
    {%- else %}
                obj.{{ field.name }} = PduRuntime.ConvertObject<{{ container.get_msg_type(field.type) }}>({{ field.name }}Value, item => {{ container.get_msg_type(field.type) }}.FromDictionary(item));
    {%- endif %}
            }
{%- endfor %}
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static {{ container.msg_type_name }} FromJson(string json)
        {
            using var doc = JsonDocument.Parse(json);
            return FromDictionary(PduRuntime.JsonElementToDictionary(doc.RootElement));
        }

        private static object? ToSerializableValue(object? value)
        {
            if (value is null) {
                return null;
            }
            if (value is string || value.GetType().IsPrimitive || value is decimal) {
                return value;
            }
            if (value is System.Collections.IEnumerable enumerable && value is not string) {
                var list = new List<object?>();
                foreach (var item in enumerable) {
                    list.Add(ToSerializableValue(item));
                }
                return list;
            }
            var toDictionary = value.GetType().GetMethod("ToDictionary");
            if (toDictionary != null) {
                return toDictionary.Invoke(value, Array.Empty<object>());
            }
            return value;
        }
    }
}
