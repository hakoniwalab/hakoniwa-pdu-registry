using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class DroneVisualState
    {
        public float x { get; set; } = 0.0F;
        public float y { get; set; } = 0.0F;
        public float z { get; set; } = 0.0F;
        public float roll { get; set; } = 0.0F;
        public float pitch { get; set; } = 0.0F;
        public float yaw { get; set; } = 0.0F;
        public List<float> pwm_duty { get; set; } = new List<float>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["x"] = ToSerializableValue(x);
            dict["y"] = ToSerializableValue(y);
            dict["z"] = ToSerializableValue(z);
            dict["roll"] = ToSerializableValue(roll);
            dict["pitch"] = ToSerializableValue(pitch);
            dict["yaw"] = ToSerializableValue(yaw);
            dict["pwm_duty"] = ToSerializableValue(pwm_duty);
            return dict;
        }

        public static DroneVisualState FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new DroneVisualState();
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
            if (dict.TryGetValue("pwm_duty", out var pwm_dutyValue))
            {
                obj.pwm_duty = PduRuntime.ConvertList<float>(pwm_dutyValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static DroneVisualState FromJson(string json)
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
