using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class LightState
    {
        public string source { get; set; } = string.Empty;
        public byte mode { get; set; } = 0;
        public double luminous_intensity_scale { get; set; } = 0.0;
        public bool is_lit { get; set; } = false;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["source"] = ToSerializableValue(source);
            dict["mode"] = ToSerializableValue(mode);
            dict["luminous_intensity_scale"] = ToSerializableValue(luminous_intensity_scale);
            dict["is_lit"] = ToSerializableValue(is_lit);
            return dict;
        }

        public static LightState FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new LightState();
            if (dict.TryGetValue("source", out var sourceValue))
            {
                obj.source = PduRuntime.ConvertValue<string>(sourceValue);
            }
            if (dict.TryGetValue("mode", out var modeValue))
            {
                obj.mode = PduRuntime.ConvertValue<byte>(modeValue);
            }
            if (dict.TryGetValue("luminous_intensity_scale", out var luminous_intensity_scaleValue))
            {
                obj.luminous_intensity_scale = PduRuntime.ConvertValue<double>(luminous_intensity_scaleValue);
            }
            if (dict.TryGetValue("is_lit", out var is_litValue))
            {
                obj.is_lit = PduRuntime.ConvertValue<bool>(is_litValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static LightState FromJson(string json)
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
