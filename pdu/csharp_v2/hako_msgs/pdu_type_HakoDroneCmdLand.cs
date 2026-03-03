using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class HakoDroneCmdLand
    {
        public HakoDroneCmdHeader header { get; set; } = new HakoDroneCmdHeader();
        public double height { get; set; } = 0.0;
        public double speed { get; set; } = 0.0;
        public double yaw_deg { get; set; } = 0.0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["height"] = ToSerializableValue(height);
            dict["speed"] = ToSerializableValue(speed);
            dict["yaw_deg"] = ToSerializableValue(yaw_deg);
            return dict;
        }

        public static HakoDroneCmdLand FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoDroneCmdLand();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<HakoDroneCmdHeader>(headerValue, item => HakoDroneCmdHeader.FromDictionary(item));
            }
            if (dict.TryGetValue("height", out var heightValue))
            {
                obj.height = PduRuntime.ConvertValue<double>(heightValue);
            }
            if (dict.TryGetValue("speed", out var speedValue))
            {
                obj.speed = PduRuntime.ConvertValue<double>(speedValue);
            }
            if (dict.TryGetValue("yaw_deg", out var yaw_degValue))
            {
                obj.yaw_deg = PduRuntime.ConvertValue<double>(yaw_degValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoDroneCmdLand FromJson(string json)
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
