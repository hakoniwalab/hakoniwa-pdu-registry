using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink2_msgs
{
    public class HakoSERVO_OUTPUT_RAW
    {
        public uint time_usec { get; set; } = 0;
        public byte port { get; set; } = 0;
        public ushort servo1_raw { get; set; } = 0;
        public ushort servo2_raw { get; set; } = 0;
        public ushort servo3_raw { get; set; } = 0;
        public ushort servo4_raw { get; set; } = 0;
        public ushort servo5_raw { get; set; } = 0;
        public ushort servo6_raw { get; set; } = 0;
        public ushort servo7_raw { get; set; } = 0;
        public ushort servo8_raw { get; set; } = 0;
        public ushort servo9_raw { get; set; } = 0;
        public ushort servo10_raw { get; set; } = 0;
        public ushort servo11_raw { get; set; } = 0;
        public ushort servo12_raw { get; set; } = 0;
        public ushort servo13_raw { get; set; } = 0;
        public ushort servo14_raw { get; set; } = 0;
        public ushort servo15_raw { get; set; } = 0;
        public ushort servo16_raw { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["time_usec"] = ToSerializableValue(time_usec);
            dict["port"] = ToSerializableValue(port);
            dict["servo1_raw"] = ToSerializableValue(servo1_raw);
            dict["servo2_raw"] = ToSerializableValue(servo2_raw);
            dict["servo3_raw"] = ToSerializableValue(servo3_raw);
            dict["servo4_raw"] = ToSerializableValue(servo4_raw);
            dict["servo5_raw"] = ToSerializableValue(servo5_raw);
            dict["servo6_raw"] = ToSerializableValue(servo6_raw);
            dict["servo7_raw"] = ToSerializableValue(servo7_raw);
            dict["servo8_raw"] = ToSerializableValue(servo8_raw);
            dict["servo9_raw"] = ToSerializableValue(servo9_raw);
            dict["servo10_raw"] = ToSerializableValue(servo10_raw);
            dict["servo11_raw"] = ToSerializableValue(servo11_raw);
            dict["servo12_raw"] = ToSerializableValue(servo12_raw);
            dict["servo13_raw"] = ToSerializableValue(servo13_raw);
            dict["servo14_raw"] = ToSerializableValue(servo14_raw);
            dict["servo15_raw"] = ToSerializableValue(servo15_raw);
            dict["servo16_raw"] = ToSerializableValue(servo16_raw);
            return dict;
        }

        public static HakoSERVO_OUTPUT_RAW FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoSERVO_OUTPUT_RAW();
            if (dict.TryGetValue("time_usec", out var time_usecValue))
            {
                obj.time_usec = PduRuntime.ConvertValue<uint>(time_usecValue);
            }
            if (dict.TryGetValue("port", out var portValue))
            {
                obj.port = PduRuntime.ConvertValue<byte>(portValue);
            }
            if (dict.TryGetValue("servo1_raw", out var servo1_rawValue))
            {
                obj.servo1_raw = PduRuntime.ConvertValue<ushort>(servo1_rawValue);
            }
            if (dict.TryGetValue("servo2_raw", out var servo2_rawValue))
            {
                obj.servo2_raw = PduRuntime.ConvertValue<ushort>(servo2_rawValue);
            }
            if (dict.TryGetValue("servo3_raw", out var servo3_rawValue))
            {
                obj.servo3_raw = PduRuntime.ConvertValue<ushort>(servo3_rawValue);
            }
            if (dict.TryGetValue("servo4_raw", out var servo4_rawValue))
            {
                obj.servo4_raw = PduRuntime.ConvertValue<ushort>(servo4_rawValue);
            }
            if (dict.TryGetValue("servo5_raw", out var servo5_rawValue))
            {
                obj.servo5_raw = PduRuntime.ConvertValue<ushort>(servo5_rawValue);
            }
            if (dict.TryGetValue("servo6_raw", out var servo6_rawValue))
            {
                obj.servo6_raw = PduRuntime.ConvertValue<ushort>(servo6_rawValue);
            }
            if (dict.TryGetValue("servo7_raw", out var servo7_rawValue))
            {
                obj.servo7_raw = PduRuntime.ConvertValue<ushort>(servo7_rawValue);
            }
            if (dict.TryGetValue("servo8_raw", out var servo8_rawValue))
            {
                obj.servo8_raw = PduRuntime.ConvertValue<ushort>(servo8_rawValue);
            }
            if (dict.TryGetValue("servo9_raw", out var servo9_rawValue))
            {
                obj.servo9_raw = PduRuntime.ConvertValue<ushort>(servo9_rawValue);
            }
            if (dict.TryGetValue("servo10_raw", out var servo10_rawValue))
            {
                obj.servo10_raw = PduRuntime.ConvertValue<ushort>(servo10_rawValue);
            }
            if (dict.TryGetValue("servo11_raw", out var servo11_rawValue))
            {
                obj.servo11_raw = PduRuntime.ConvertValue<ushort>(servo11_rawValue);
            }
            if (dict.TryGetValue("servo12_raw", out var servo12_rawValue))
            {
                obj.servo12_raw = PduRuntime.ConvertValue<ushort>(servo12_rawValue);
            }
            if (dict.TryGetValue("servo13_raw", out var servo13_rawValue))
            {
                obj.servo13_raw = PduRuntime.ConvertValue<ushort>(servo13_rawValue);
            }
            if (dict.TryGetValue("servo14_raw", out var servo14_rawValue))
            {
                obj.servo14_raw = PduRuntime.ConvertValue<ushort>(servo14_rawValue);
            }
            if (dict.TryGetValue("servo15_raw", out var servo15_rawValue))
            {
                obj.servo15_raw = PduRuntime.ConvertValue<ushort>(servo15_rawValue);
            }
            if (dict.TryGetValue("servo16_raw", out var servo16_rawValue))
            {
                obj.servo16_raw = PduRuntime.ConvertValue<ushort>(servo16_rawValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoSERVO_OUTPUT_RAW FromJson(string json)
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
