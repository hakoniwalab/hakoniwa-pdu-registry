using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public class Pose
    {
        public Point position { get; set; } = new Point();
        public Quaternion orientation { get; set; } = new Quaternion();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["position"] = ToSerializableValue(position);
            dict["orientation"] = ToSerializableValue(orientation);
            return dict;
        }

        public static Pose FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Pose();
            if (dict.TryGetValue("position", out var positionValue))
            {
                obj.position = PduRuntime.ConvertObject<Point>(positionValue, item => Point.FromDictionary(item));
            }
            if (dict.TryGetValue("orientation", out var orientationValue))
            {
                obj.orientation = PduRuntime.ConvertObject<Quaternion>(orientationValue, item => Quaternion.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Pose FromJson(string json)
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
