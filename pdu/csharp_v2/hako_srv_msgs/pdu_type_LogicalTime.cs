using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class LogicalTime
    {
        public ulong generation { get; set; } = 0;
        public ulong offset_tick { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["generation"] = ToSerializableValue(generation);
            dict["offset_tick"] = ToSerializableValue(offset_tick);
            return dict;
        }

        public static LogicalTime FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new LogicalTime();
            if (dict.TryGetValue("generation", out var generationValue))
            {
                obj.generation = PduRuntime.ConvertValue<ulong>(generationValue);
            }
            if (dict.TryGetValue("offset_tick", out var offset_tickValue))
            {
                obj.offset_tick = PduRuntime.ConvertValue<ulong>(offset_tickValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static LogicalTime FromJson(string json)
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
