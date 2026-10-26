using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class PersonStepRequest
    {
        public ulong step { get; set; } = 0;
        public Twist cmd_vel { get; set; } = new Twist();
        public string animation { get; set; } = string.Empty;
        public string ride { get; set; } = string.Empty;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["step"] = ToSerializableValue(step);
            dict["cmd_vel"] = ToSerializableValue(cmd_vel);
            dict["animation"] = ToSerializableValue(animation);
            dict["ride"] = ToSerializableValue(ride);
            return dict;
        }

        public static PersonStepRequest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new PersonStepRequest();
            if (dict.TryGetValue("step", out var stepValue))
            {
                obj.step = PduRuntime.ConvertValue<ulong>(stepValue);
            }
            if (dict.TryGetValue("cmd_vel", out var cmd_velValue))
            {
                obj.cmd_vel = PduRuntime.ConvertObject<Twist>(cmd_velValue, item => Twist.FromDictionary(item));
            }
            if (dict.TryGetValue("animation", out var animationValue))
            {
                obj.animation = PduRuntime.ConvertValue<string>(animationValue);
            }
            if (dict.TryGetValue("ride", out var rideValue))
            {
                obj.ride = PduRuntime.ConvertValue<string>(rideValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static PersonStepRequest FromJson(string json)
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
