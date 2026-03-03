using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.ev3_msgs
{
    public class Ev3PduActuator
    {
        public Ev3PduActuatorHeader head { get; set; } = new Ev3PduActuatorHeader();
        public List<byte> leds { get; set; } = new List<byte>();
        public List<Ev3PduMotor> motors { get; set; } = new List<Ev3PduMotor>();
        public uint gyro_reset { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["head"] = ToSerializableValue(head);
            dict["leds"] = ToSerializableValue(leds);
            dict["motors"] = ToSerializableValue(motors);
            dict["gyro_reset"] = ToSerializableValue(gyro_reset);
            return dict;
        }

        public static Ev3PduActuator FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Ev3PduActuator();
            if (dict.TryGetValue("head", out var headValue))
            {
                obj.head = PduRuntime.ConvertObject<Ev3PduActuatorHeader>(headValue, item => Ev3PduActuatorHeader.FromDictionary(item));
            }
            if (dict.TryGetValue("leds", out var ledsValue))
            {
                obj.leds = PduRuntime.ConvertList<byte>(ledsValue);
            }
            if (dict.TryGetValue("motors", out var motorsValue))
            {
                obj.motors = PduRuntime.ConvertObjectList<Ev3PduMotor>(motorsValue, item => Ev3PduMotor.FromDictionary(item));
            }
            if (dict.TryGetValue("gyro_reset", out var gyro_resetValue))
            {
                obj.gyro_reset = PduRuntime.ConvertValue<uint>(gyro_resetValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Ev3PduActuator FromJson(string json)
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
