using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public class Inertia
    {
        public double m { get; set; } = 0.0;
        public Vector3 com { get; set; } = new Vector3();
        public double ixx { get; set; } = 0.0;
        public double ixy { get; set; } = 0.0;
        public double ixz { get; set; } = 0.0;
        public double iyy { get; set; } = 0.0;
        public double iyz { get; set; } = 0.0;
        public double izz { get; set; } = 0.0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["m"] = ToSerializableValue(m);
            dict["com"] = ToSerializableValue(com);
            dict["ixx"] = ToSerializableValue(ixx);
            dict["ixy"] = ToSerializableValue(ixy);
            dict["ixz"] = ToSerializableValue(ixz);
            dict["iyy"] = ToSerializableValue(iyy);
            dict["iyz"] = ToSerializableValue(iyz);
            dict["izz"] = ToSerializableValue(izz);
            return dict;
        }

        public static Inertia FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Inertia();
            if (dict.TryGetValue("m", out var mValue))
            {
                obj.m = PduRuntime.ConvertValue<double>(mValue);
            }
            if (dict.TryGetValue("com", out var comValue))
            {
                obj.com = PduRuntime.ConvertObject<Vector3>(comValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("ixx", out var ixxValue))
            {
                obj.ixx = PduRuntime.ConvertValue<double>(ixxValue);
            }
            if (dict.TryGetValue("ixy", out var ixyValue))
            {
                obj.ixy = PduRuntime.ConvertValue<double>(ixyValue);
            }
            if (dict.TryGetValue("ixz", out var ixzValue))
            {
                obj.ixz = PduRuntime.ConvertValue<double>(ixzValue);
            }
            if (dict.TryGetValue("iyy", out var iyyValue))
            {
                obj.iyy = PduRuntime.ConvertValue<double>(iyyValue);
            }
            if (dict.TryGetValue("iyz", out var iyzValue))
            {
                obj.iyz = PduRuntime.ConvertValue<double>(iyzValue);
            }
            if (dict.TryGetValue("izz", out var izzValue))
            {
                obj.izz = PduRuntime.ConvertValue<double>(izzValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Inertia FromJson(string json)
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
