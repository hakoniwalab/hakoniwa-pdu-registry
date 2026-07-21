using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.trajectory_msgs
{
    public class JointTrajectory
    {
        public Header header { get; set; } = new Header();
        public List<string> joint_names { get; set; } = new List<string>();
        public List<JointTrajectoryPoint> points { get; set; } = new List<JointTrajectoryPoint>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["joint_names"] = ToSerializableValue(joint_names);
            dict["points"] = ToSerializableValue(points);
            return dict;
        }

        public static JointTrajectory FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new JointTrajectory();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("joint_names", out var joint_namesValue))
            {
                obj.joint_names = PduRuntime.ConvertList<string>(joint_namesValue);
            }
            if (dict.TryGetValue("points", out var pointsValue))
            {
                obj.points = PduRuntime.ConvertObjectList<JointTrajectoryPoint>(pointsValue, item => JointTrajectoryPoint.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static JointTrajectory FromJson(string json)
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
