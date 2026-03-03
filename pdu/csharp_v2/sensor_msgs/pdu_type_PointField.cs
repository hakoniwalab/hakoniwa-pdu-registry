using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class PointField
    {
        public string name { get; set; } = string.Empty;
        public uint offset { get; set; } = 0;
        public byte datatype { get; set; } = 0;
        public uint count { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["name"] = ToSerializableValue(name);
            dict["offset"] = ToSerializableValue(offset);
            dict["datatype"] = ToSerializableValue(datatype);
            dict["count"] = ToSerializableValue(count);
            return dict;
        }

        public static PointField FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new PointField();
            if (dict.TryGetValue("name", out var nameValue))
            {
                obj.name = PduRuntime.ConvertValue<string>(nameValue);
            }
            if (dict.TryGetValue("offset", out var offsetValue))
            {
                obj.offset = PduRuntime.ConvertValue<uint>(offsetValue);
            }
            if (dict.TryGetValue("datatype", out var datatypeValue))
            {
                obj.datatype = PduRuntime.ConvertValue<byte>(datatypeValue);
            }
            if (dict.TryGetValue("count", out var countValue))
            {
                obj.count = PduRuntime.ConvertValue<uint>(countValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static PointField FromJson(string json)
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
