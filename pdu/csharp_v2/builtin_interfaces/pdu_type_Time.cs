using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.builtin_interfaces
{
    public class Time
    {
        public int sec { get; set; } = 0;
        public uint nanosec { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["sec"] = ToSerializableValue(sec);
            dict["nanosec"] = ToSerializableValue(nanosec);
            return dict;
        }

        public static Time FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Time();
            if (dict.TryGetValue("sec", out var secValue))
            {
                obj.sec = PduRuntime.ConvertValue<int>(secValue);
            }
            if (dict.TryGetValue("nanosec", out var nanosecValue))
            {
                obj.nanosec = PduRuntime.ConvertValue<uint>(nanosecValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Time FromJson(string json)
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
