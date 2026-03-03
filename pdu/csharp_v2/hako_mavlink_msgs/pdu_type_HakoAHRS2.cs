using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public class HakoAHRS2
    {
        public float roll { get; set; } = 0.0F;
        public float pitch { get; set; } = 0.0F;
        public float yaw { get; set; } = 0.0F;
        public float altitude { get; set; } = 0.0F;
        public int lat { get; set; } = 0;
        public int lng { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["roll"] = ToSerializableValue(roll);
            dict["pitch"] = ToSerializableValue(pitch);
            dict["yaw"] = ToSerializableValue(yaw);
            dict["altitude"] = ToSerializableValue(altitude);
            dict["lat"] = ToSerializableValue(lat);
            dict["lng"] = ToSerializableValue(lng);
            return dict;
        }

        public static HakoAHRS2 FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoAHRS2();
            if (dict.TryGetValue("roll", out var rollValue))
            {
                obj.roll = PduRuntime.ConvertValue<float>(rollValue);
            }
            if (dict.TryGetValue("pitch", out var pitchValue))
            {
                obj.pitch = PduRuntime.ConvertValue<float>(pitchValue);
            }
            if (dict.TryGetValue("yaw", out var yawValue))
            {
                obj.yaw = PduRuntime.ConvertValue<float>(yawValue);
            }
            if (dict.TryGetValue("altitude", out var altitudeValue))
            {
                obj.altitude = PduRuntime.ConvertValue<float>(altitudeValue);
            }
            if (dict.TryGetValue("lat", out var latValue))
            {
                obj.lat = PduRuntime.ConvertValue<int>(latValue);
            }
            if (dict.TryGetValue("lng", out var lngValue))
            {
                obj.lng = PduRuntime.ConvertValue<int>(lngValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoAHRS2 FromJson(string json)
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
