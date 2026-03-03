using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public class ColorRGBA
    {
        public float r { get; set; } = 0.0F;
        public float g { get; set; } = 0.0F;
        public float b { get; set; } = 0.0F;
        public float a { get; set; } = 0.0F;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["r"] = ToSerializableValue(r);
            dict["g"] = ToSerializableValue(g);
            dict["b"] = ToSerializableValue(b);
            dict["a"] = ToSerializableValue(a);
            return dict;
        }

        public static ColorRGBA FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new ColorRGBA();
            if (dict.TryGetValue("r", out var rValue))
            {
                obj.r = PduRuntime.ConvertValue<float>(rValue);
            }
            if (dict.TryGetValue("g", out var gValue))
            {
                obj.g = PduRuntime.ConvertValue<float>(gValue);
            }
            if (dict.TryGetValue("b", out var bValue))
            {
                obj.b = PduRuntime.ConvertValue<float>(bValue);
            }
            if (dict.TryGetValue("a", out var aValue))
            {
                obj.a = PduRuntime.ConvertValue<float>(aValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static ColorRGBA FromJson(string json)
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
