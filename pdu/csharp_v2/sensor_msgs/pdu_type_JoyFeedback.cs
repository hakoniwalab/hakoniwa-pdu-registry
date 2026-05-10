using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class JoyFeedback
    {
        public byte type { get; set; } = 0;
        public byte id { get; set; } = 0;
        public float intensity { get; set; } = 0.0F;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["type"] = ToSerializableValue(type);
            dict["id"] = ToSerializableValue(id);
            dict["intensity"] = ToSerializableValue(intensity);
            return dict;
        }

        public static JoyFeedback FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new JoyFeedback();
            if (dict.TryGetValue("type", out var typeValue))
            {
                obj.type = PduRuntime.ConvertValue<byte>(typeValue);
            }
            if (dict.TryGetValue("id", out var idValue))
            {
                obj.id = PduRuntime.ConvertValue<byte>(idValue);
            }
            if (dict.TryGetValue("intensity", out var intensityValue))
            {
                obj.intensity = PduRuntime.ConvertValue<float>(intensityValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static JoyFeedback FromJson(string json)
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
