using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.nav_msgs
{
    public class Odometry
    {
        public Header header { get; set; } = new Header();
        public string child_frame_id { get; set; } = string.Empty;
        public PoseWithCovariance pose { get; set; } = new PoseWithCovariance();
        public TwistWithCovariance twist { get; set; } = new TwistWithCovariance();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["child_frame_id"] = ToSerializableValue(child_frame_id);
            dict["pose"] = ToSerializableValue(pose);
            dict["twist"] = ToSerializableValue(twist);
            return dict;
        }

        public static Odometry FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Odometry();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("child_frame_id", out var child_frame_idValue))
            {
                obj.child_frame_id = PduRuntime.ConvertValue<string>(child_frame_idValue);
            }
            if (dict.TryGetValue("pose", out var poseValue))
            {
                obj.pose = PduRuntime.ConvertObject<PoseWithCovariance>(poseValue, item => PoseWithCovariance.FromDictionary(item));
            }
            if (dict.TryGetValue("twist", out var twistValue))
            {
                obj.twist = PduRuntime.ConvertObject<TwistWithCovariance>(twistValue, item => TwistWithCovariance.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Odometry FromJson(string json)
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
