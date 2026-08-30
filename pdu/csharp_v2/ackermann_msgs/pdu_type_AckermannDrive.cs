using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.ackermann_msgs
{
    public class AckermannDrive
    {
        public float steering_angle { get; set; } = 0.0F;
        public float steering_angle_velocity { get; set; } = 0.0F;
        public float speed { get; set; } = 0.0F;
        public float acceleration { get; set; } = 0.0F;
        public float jerk { get; set; } = 0.0F;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["steering_angle"] = ToSerializableValue(steering_angle);
            dict["steering_angle_velocity"] = ToSerializableValue(steering_angle_velocity);
            dict["speed"] = ToSerializableValue(speed);
            dict["acceleration"] = ToSerializableValue(acceleration);
            dict["jerk"] = ToSerializableValue(jerk);
            return dict;
        }

        public static AckermannDrive FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new AckermannDrive();
            if (dict.TryGetValue("steering_angle", out var steering_angleValue))
            {
                obj.steering_angle = PduRuntime.ConvertValue<float>(steering_angleValue);
            }
            if (dict.TryGetValue("steering_angle_velocity", out var steering_angle_velocityValue))
            {
                obj.steering_angle_velocity = PduRuntime.ConvertValue<float>(steering_angle_velocityValue);
            }
            if (dict.TryGetValue("speed", out var speedValue))
            {
                obj.speed = PduRuntime.ConvertValue<float>(speedValue);
            }
            if (dict.TryGetValue("acceleration", out var accelerationValue))
            {
                obj.acceleration = PduRuntime.ConvertValue<float>(accelerationValue);
            }
            if (dict.TryGetValue("jerk", out var jerkValue))
            {
                obj.jerk = PduRuntime.ConvertValue<float>(jerkValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static AckermannDrive FromJson(string json)
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
