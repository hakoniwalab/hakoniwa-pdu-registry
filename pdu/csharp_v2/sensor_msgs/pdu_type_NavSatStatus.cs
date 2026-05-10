using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class NavSatStatus
    {
        public sbyte status { get; set; } = 0;
        public ushort service { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["status"] = ToSerializableValue(status);
            dict["service"] = ToSerializableValue(service);
            return dict;
        }

        public static NavSatStatus FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new NavSatStatus();
            if (dict.TryGetValue("status", out var statusValue))
            {
                obj.status = PduRuntime.ConvertValue<sbyte>(statusValue);
            }
            if (dict.TryGetValue("service", out var serviceValue))
            {
                obj.service = PduRuntime.ConvertValue<ushort>(serviceValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static NavSatStatus FromJson(string json)
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
