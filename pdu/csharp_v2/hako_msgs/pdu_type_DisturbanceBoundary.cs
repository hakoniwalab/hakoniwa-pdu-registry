using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class DisturbanceBoundary
    {
        public Point boundary_point { get; set; } = new Point();
        public Vector3 boundary_normal { get; set; } = new Vector3();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["boundary_point"] = ToSerializableValue(boundary_point);
            dict["boundary_normal"] = ToSerializableValue(boundary_normal);
            return dict;
        }

        public static DisturbanceBoundary FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new DisturbanceBoundary();
            if (dict.TryGetValue("boundary_point", out var boundary_pointValue))
            {
                obj.boundary_point = PduRuntime.ConvertObject<Point>(boundary_pointValue, item => Point.FromDictionary(item));
            }
            if (dict.TryGetValue("boundary_normal", out var boundary_normalValue))
            {
                obj.boundary_normal = PduRuntime.ConvertObject<Vector3>(boundary_normalValue, item => Vector3.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static DisturbanceBoundary FromJson(string json)
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
