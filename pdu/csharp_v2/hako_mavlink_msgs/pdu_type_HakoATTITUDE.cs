using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public class HakoATTITUDE
    {
        public uint time_boot_ms { get; set; } = 0;
        public float roll { get; set; } = 0.0F;
        public float pitch { get; set; } = 0.0F;
        public float yaw { get; set; } = 0.0F;
        public float rollspeed { get; set; } = 0.0F;
        public float pitchspeed { get; set; } = 0.0F;
        public float yawspeed { get; set; } = 0.0F;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["time_boot_ms"] = ToSerializableValue(time_boot_ms);
            dict["roll"] = ToSerializableValue(roll);
            dict["pitch"] = ToSerializableValue(pitch);
            dict["yaw"] = ToSerializableValue(yaw);
            dict["rollspeed"] = ToSerializableValue(rollspeed);
            dict["pitchspeed"] = ToSerializableValue(pitchspeed);
            dict["yawspeed"] = ToSerializableValue(yawspeed);
            return dict;
        }

        public static HakoATTITUDE FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoATTITUDE();
            if (dict.TryGetValue("time_boot_ms", out var time_boot_msValue))
            {
                obj.time_boot_ms = PduRuntime.ConvertValue<uint>(time_boot_msValue);
            }
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
            if (dict.TryGetValue("rollspeed", out var rollspeedValue))
            {
                obj.rollspeed = PduRuntime.ConvertValue<float>(rollspeedValue);
            }
            if (dict.TryGetValue("pitchspeed", out var pitchspeedValue))
            {
                obj.pitchspeed = PduRuntime.ConvertValue<float>(pitchspeedValue);
            }
            if (dict.TryGetValue("yawspeed", out var yawspeedValue))
            {
                obj.yawspeed = PduRuntime.ConvertValue<float>(yawspeedValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoATTITUDE FromJson(string json)
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
