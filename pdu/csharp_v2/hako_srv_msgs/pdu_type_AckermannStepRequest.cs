using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.ackermann_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class AckermannStepRequest
    {
        public ulong step { get; set; } = 0;
        public AckermannDrive drive { get; set; } = new AckermannDrive();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["step"] = ToSerializableValue(step);
            dict["drive"] = ToSerializableValue(drive);
            return dict;
        }

        public static AckermannStepRequest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new AckermannStepRequest();
            if (dict.TryGetValue("step", out var stepValue))
            {
                obj.step = PduRuntime.ConvertValue<ulong>(stepValue);
            }
            if (dict.TryGetValue("drive", out var driveValue))
            {
                obj.drive = PduRuntime.ConvertObject<AckermannDrive>(driveValue, item => AckermannDrive.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static AckermannStepRequest FromJson(string json)
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
