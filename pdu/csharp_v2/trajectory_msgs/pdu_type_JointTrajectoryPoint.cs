using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;

namespace Hakoniwa.Pdu.CSharpV2.trajectory_msgs
{
    public class JointTrajectoryPoint
    {
        public List<double> positions { get; set; } = new List<double>();
        public List<double> velocities { get; set; } = new List<double>();
        public List<double> accelerations { get; set; } = new List<double>();
        public List<double> effort { get; set; } = new List<double>();
        public Duration time_from_start { get; set; } = new Duration();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["positions"] = ToSerializableValue(positions);
            dict["velocities"] = ToSerializableValue(velocities);
            dict["accelerations"] = ToSerializableValue(accelerations);
            dict["effort"] = ToSerializableValue(effort);
            dict["time_from_start"] = ToSerializableValue(time_from_start);
            return dict;
        }

        public static JointTrajectoryPoint FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new JointTrajectoryPoint();
            if (dict.TryGetValue("positions", out var positionsValue))
            {
                obj.positions = PduRuntime.ConvertList<double>(positionsValue);
            }
            if (dict.TryGetValue("velocities", out var velocitiesValue))
            {
                obj.velocities = PduRuntime.ConvertList<double>(velocitiesValue);
            }
            if (dict.TryGetValue("accelerations", out var accelerationsValue))
            {
                obj.accelerations = PduRuntime.ConvertList<double>(accelerationsValue);
            }
            if (dict.TryGetValue("effort", out var effortValue))
            {
                obj.effort = PduRuntime.ConvertList<double>(effortValue);
            }
            if (dict.TryGetValue("time_from_start", out var time_from_startValue))
            {
                obj.time_from_start = PduRuntime.ConvertObject<Duration>(time_from_startValue, item => Duration.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static JointTrajectoryPoint FromJson(string json)
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
