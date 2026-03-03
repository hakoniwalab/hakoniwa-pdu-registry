using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.ev3_msgs
{
    public class Ev3PduMotor
    {
        public int power { get; set; } = 0;
        public uint stop { get; set; } = 0;
        public uint reset_angle { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["power"] = ToSerializableValue(power);
            dict["stop"] = ToSerializableValue(stop);
            dict["reset_angle"] = ToSerializableValue(reset_angle);
            return dict;
        }

        public static Ev3PduMotor FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Ev3PduMotor();
            if (dict.TryGetValue("power", out var powerValue))
            {
                obj.power = PduRuntime.ConvertValue<int>(powerValue);
            }
            if (dict.TryGetValue("stop", out var stopValue))
            {
                obj.stop = PduRuntime.ConvertValue<uint>(stopValue);
            }
            if (dict.TryGetValue("reset_angle", out var reset_angleValue))
            {
                obj.reset_angle = PduRuntime.ConvertValue<uint>(reset_angleValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Ev3PduMotor FromJson(string json)
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
