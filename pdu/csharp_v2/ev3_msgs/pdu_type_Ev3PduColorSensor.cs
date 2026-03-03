using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.ev3_msgs
{
    public class Ev3PduColorSensor
    {
        public uint color { get; set; } = 0;
        public uint reflect { get; set; } = 0;
        public uint rgb_r { get; set; } = 0;
        public uint rgb_g { get; set; } = 0;
        public uint rgb_b { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["color"] = ToSerializableValue(color);
            dict["reflect"] = ToSerializableValue(reflect);
            dict["rgb_r"] = ToSerializableValue(rgb_r);
            dict["rgb_g"] = ToSerializableValue(rgb_g);
            dict["rgb_b"] = ToSerializableValue(rgb_b);
            return dict;
        }

        public static Ev3PduColorSensor FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Ev3PduColorSensor();
            if (dict.TryGetValue("color", out var colorValue))
            {
                obj.color = PduRuntime.ConvertValue<uint>(colorValue);
            }
            if (dict.TryGetValue("reflect", out var reflectValue))
            {
                obj.reflect = PduRuntime.ConvertValue<uint>(reflectValue);
            }
            if (dict.TryGetValue("rgb_r", out var rgb_rValue))
            {
                obj.rgb_r = PduRuntime.ConvertValue<uint>(rgb_rValue);
            }
            if (dict.TryGetValue("rgb_g", out var rgb_gValue))
            {
                obj.rgb_g = PduRuntime.ConvertValue<uint>(rgb_gValue);
            }
            if (dict.TryGetValue("rgb_b", out var rgb_bValue))
            {
                obj.rgb_b = PduRuntime.ConvertValue<uint>(rgb_bValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Ev3PduColorSensor FromJson(string json)
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
