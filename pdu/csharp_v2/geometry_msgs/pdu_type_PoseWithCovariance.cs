using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public class PoseWithCovariance
    {
        public Pose pose { get; set; } = new Pose();
        public List<double> covariance { get; set; } = new List<double>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["pose"] = ToSerializableValue(pose);
            dict["covariance"] = ToSerializableValue(covariance);
            return dict;
        }

        public static PoseWithCovariance FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new PoseWithCovariance();
            if (dict.TryGetValue("pose", out var poseValue))
            {
                obj.pose = PduRuntime.ConvertObject<Pose>(poseValue, item => Pose.FromDictionary(item));
            }
            if (dict.TryGetValue("covariance", out var covarianceValue))
            {
                obj.covariance = PduRuntime.ConvertList<double>(covarianceValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static PoseWithCovariance FromJson(string json)
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
