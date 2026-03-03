using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public class HakoSystemTime
    {
        public ulong time_unix_usec { get; set; } = 0;
        public ulong time_boot_ms { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["time_unix_usec"] = ToSerializableValue(time_unix_usec);
            dict["time_boot_ms"] = ToSerializableValue(time_boot_ms);
            return dict;
        }

        public static HakoSystemTime FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoSystemTime();
            if (dict.TryGetValue("time_unix_usec", out var time_unix_usecValue))
            {
                obj.time_unix_usec = PduRuntime.ConvertValue<ulong>(time_unix_usecValue);
            }
            if (dict.TryGetValue("time_boot_ms", out var time_boot_msValue))
            {
                obj.time_boot_ms = PduRuntime.ConvertValue<ulong>(time_boot_msValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoSystemTime FromJson(string json)
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
