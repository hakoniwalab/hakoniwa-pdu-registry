using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class LaserScan
    {
        public Header header { get; set; } = new Header();
        public float angle_min { get; set; } = 0.0F;
        public float angle_max { get; set; } = 0.0F;
        public float angle_increment { get; set; } = 0.0F;
        public float time_increment { get; set; } = 0.0F;
        public float scan_time { get; set; } = 0.0F;
        public float range_min { get; set; } = 0.0F;
        public float range_max { get; set; } = 0.0F;
        public List<float> ranges { get; set; } = new List<float>();
        public List<float> intensities { get; set; } = new List<float>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["angle_min"] = ToSerializableValue(angle_min);
            dict["angle_max"] = ToSerializableValue(angle_max);
            dict["angle_increment"] = ToSerializableValue(angle_increment);
            dict["time_increment"] = ToSerializableValue(time_increment);
            dict["scan_time"] = ToSerializableValue(scan_time);
            dict["range_min"] = ToSerializableValue(range_min);
            dict["range_max"] = ToSerializableValue(range_max);
            dict["ranges"] = ToSerializableValue(ranges);
            dict["intensities"] = ToSerializableValue(intensities);
            return dict;
        }

        public static LaserScan FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new LaserScan();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("angle_min", out var angle_minValue))
            {
                obj.angle_min = PduRuntime.ConvertValue<float>(angle_minValue);
            }
            if (dict.TryGetValue("angle_max", out var angle_maxValue))
            {
                obj.angle_max = PduRuntime.ConvertValue<float>(angle_maxValue);
            }
            if (dict.TryGetValue("angle_increment", out var angle_incrementValue))
            {
                obj.angle_increment = PduRuntime.ConvertValue<float>(angle_incrementValue);
            }
            if (dict.TryGetValue("time_increment", out var time_incrementValue))
            {
                obj.time_increment = PduRuntime.ConvertValue<float>(time_incrementValue);
            }
            if (dict.TryGetValue("scan_time", out var scan_timeValue))
            {
                obj.scan_time = PduRuntime.ConvertValue<float>(scan_timeValue);
            }
            if (dict.TryGetValue("range_min", out var range_minValue))
            {
                obj.range_min = PduRuntime.ConvertValue<float>(range_minValue);
            }
            if (dict.TryGetValue("range_max", out var range_maxValue))
            {
                obj.range_max = PduRuntime.ConvertValue<float>(range_maxValue);
            }
            if (dict.TryGetValue("ranges", out var rangesValue))
            {
                obj.ranges = PduRuntime.ConvertList<float>(rangesValue);
            }
            if (dict.TryGetValue("intensities", out var intensitiesValue))
            {
                obj.intensities = PduRuntime.ConvertList<float>(intensitiesValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static LaserScan FromJson(string json)
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
