using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public class HakoHilActuatorControls
    {
        public ulong time_usec { get; set; } = 0;
        public List<float> controls { get; set; } = new List<float>();
        public byte mode { get; set; } = 0;
        public ulong flags { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["time_usec"] = ToSerializableValue(time_usec);
            dict["controls"] = ToSerializableValue(controls);
            dict["mode"] = ToSerializableValue(mode);
            dict["flags"] = ToSerializableValue(flags);
            return dict;
        }

        public static HakoHilActuatorControls FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoHilActuatorControls();
            if (dict.TryGetValue("time_usec", out var time_usecValue))
            {
                obj.time_usec = PduRuntime.ConvertValue<ulong>(time_usecValue);
            }
            if (dict.TryGetValue("controls", out var controlsValue))
            {
                obj.controls = PduRuntime.ConvertList<float>(controlsValue);
            }
            if (dict.TryGetValue("mode", out var modeValue))
            {
                obj.mode = PduRuntime.ConvertValue<byte>(modeValue);
            }
            if (dict.TryGetValue("flags", out var flagsValue))
            {
                obj.flags = PduRuntime.ConvertValue<ulong>(flagsValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoHilActuatorControls FromJson(string json)
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
