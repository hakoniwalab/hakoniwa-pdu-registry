using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class HakoBatteryStatus
    {
        public double full_voltage { get; set; } = 0.0;
        public double curr_voltage { get; set; } = 0.0;
        public double curr_temp { get; set; } = 0.0;
        public uint status { get; set; } = 0;
        public uint cycles { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["full_voltage"] = ToSerializableValue(full_voltage);
            dict["curr_voltage"] = ToSerializableValue(curr_voltage);
            dict["curr_temp"] = ToSerializableValue(curr_temp);
            dict["status"] = ToSerializableValue(status);
            dict["cycles"] = ToSerializableValue(cycles);
            return dict;
        }

        public static HakoBatteryStatus FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoBatteryStatus();
            if (dict.TryGetValue("full_voltage", out var full_voltageValue))
            {
                obj.full_voltage = PduRuntime.ConvertValue<double>(full_voltageValue);
            }
            if (dict.TryGetValue("curr_voltage", out var curr_voltageValue))
            {
                obj.curr_voltage = PduRuntime.ConvertValue<double>(curr_voltageValue);
            }
            if (dict.TryGetValue("curr_temp", out var curr_tempValue))
            {
                obj.curr_temp = PduRuntime.ConvertValue<double>(curr_tempValue);
            }
            if (dict.TryGetValue("status", out var statusValue))
            {
                obj.status = PduRuntime.ConvertValue<uint>(statusValue);
            }
            if (dict.TryGetValue("cycles", out var cyclesValue))
            {
                obj.cycles = PduRuntime.ConvertValue<uint>(cyclesValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoBatteryStatus FromJson(string json)
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
