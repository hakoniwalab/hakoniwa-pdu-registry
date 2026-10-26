using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class LightStateArray
    {
        public ulong stamp_usec { get; set; } = 0;
        public string carrier { get; set; } = string.Empty;
        public List<LightState> lights { get; set; } = new List<LightState>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["stamp_usec"] = ToSerializableValue(stamp_usec);
            dict["carrier"] = ToSerializableValue(carrier);
            dict["lights"] = ToSerializableValue(lights);
            return dict;
        }

        public static LightStateArray FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new LightStateArray();
            if (dict.TryGetValue("stamp_usec", out var stamp_usecValue))
            {
                obj.stamp_usec = PduRuntime.ConvertValue<ulong>(stamp_usecValue);
            }
            if (dict.TryGetValue("carrier", out var carrierValue))
            {
                obj.carrier = PduRuntime.ConvertValue<string>(carrierValue);
            }
            if (dict.TryGetValue("lights", out var lightsValue))
            {
                obj.lights = PduRuntime.ConvertObjectList<LightState>(lightsValue, item => LightState.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static LightStateArray FromJson(string json)
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
