using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class AddTwoIntsRequest
    {
        public long a { get; set; } = 0;
        public long b { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["a"] = ToSerializableValue(a);
            dict["b"] = ToSerializableValue(b);
            return dict;
        }

        public static AddTwoIntsRequest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new AddTwoIntsRequest();
            if (dict.TryGetValue("a", out var aValue))
            {
                obj.a = PduRuntime.ConvertValue<long>(aValue);
            }
            if (dict.TryGetValue("b", out var bValue))
            {
                obj.b = PduRuntime.ConvertValue<long>(bValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static AddTwoIntsRequest FromJson(string json)
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
