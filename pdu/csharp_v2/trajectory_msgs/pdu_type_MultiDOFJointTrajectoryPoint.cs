using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.trajectory_msgs
{
    public class MultiDOFJointTrajectoryPoint
    {
        public List<Transform> transforms { get; set; } = new List<Transform>();
        public List<Twist> velocities { get; set; } = new List<Twist>();
        public List<Twist> accelerations { get; set; } = new List<Twist>();
        public Duration time_from_start { get; set; } = new Duration();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["transforms"] = ToSerializableValue(transforms);
            dict["velocities"] = ToSerializableValue(velocities);
            dict["accelerations"] = ToSerializableValue(accelerations);
            dict["time_from_start"] = ToSerializableValue(time_from_start);
            return dict;
        }

        public static MultiDOFJointTrajectoryPoint FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new MultiDOFJointTrajectoryPoint();
            if (dict.TryGetValue("transforms", out var transformsValue))
            {
                obj.transforms = PduRuntime.ConvertObjectList<Transform>(transformsValue, item => Transform.FromDictionary(item));
            }
            if (dict.TryGetValue("velocities", out var velocitiesValue))
            {
                obj.velocities = PduRuntime.ConvertObjectList<Twist>(velocitiesValue, item => Twist.FromDictionary(item));
            }
            if (dict.TryGetValue("accelerations", out var accelerationsValue))
            {
                obj.accelerations = PduRuntime.ConvertObjectList<Twist>(accelerationsValue, item => Twist.FromDictionary(item));
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

        public static MultiDOFJointTrajectoryPoint FromJson(string json)
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
