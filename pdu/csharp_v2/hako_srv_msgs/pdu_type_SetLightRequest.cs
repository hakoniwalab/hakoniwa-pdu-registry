using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class SetLightRequest
    {
        public string source { get; set; } = string.Empty;
        public byte mode { get; set; } = 0;
        public double luminous_intensity_scale { get; set; } = 0.0;
        public double flashing_on_s { get; set; } = 0.0;
        public double flashing_off_s { get; set; } = 0.0;
        public double transition_s { get; set; } = 0.0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["source"] = ToSerializableValue(source);
            dict["mode"] = ToSerializableValue(mode);
            dict["luminous_intensity_scale"] = ToSerializableValue(luminous_intensity_scale);
            dict["flashing_on_s"] = ToSerializableValue(flashing_on_s);
            dict["flashing_off_s"] = ToSerializableValue(flashing_off_s);
            dict["transition_s"] = ToSerializableValue(transition_s);
            return dict;
        }

        public static SetLightRequest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new SetLightRequest();
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
            if (dict.TryGetValue("flashing_on_s", out var flashing_on_sValue))
            {
                obj.flashing_on_s = PduRuntime.ConvertValue<double>(flashing_on_sValue);
            }
            if (dict.TryGetValue("flashing_off_s", out var flashing_off_sValue))
            {
                obj.flashing_off_s = PduRuntime.ConvertValue<double>(flashing_off_sValue);
            }
            if (dict.TryGetValue("transition_s", out var transition_sValue))
            {
                obj.transition_s = PduRuntime.ConvertValue<double>(transition_sValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static SetLightRequest FromJson(string json)
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
