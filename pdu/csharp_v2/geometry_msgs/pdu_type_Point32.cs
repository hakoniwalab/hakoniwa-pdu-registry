using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public class Point32
    {
        public float x { get; set; } = 0.0F;
        public float y { get; set; } = 0.0F;
        public float z { get; set; } = 0.0F;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["x"] = ToSerializableValue(x);
            dict["y"] = ToSerializableValue(y);
            dict["z"] = ToSerializableValue(z);
            return dict;
        }

        public static Point32 FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Point32();
            if (dict.TryGetValue("x", out var xValue))
            {
                obj.x = PduRuntime.ConvertValue<float>(xValue);
            }
            if (dict.TryGetValue("y", out var yValue))
            {
                obj.y = PduRuntime.ConvertValue<float>(yValue);
            }
            if (dict.TryGetValue("z", out var zValue))
            {
                obj.z = PduRuntime.ConvertValue<float>(zValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Point32 FromJson(string json)
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
