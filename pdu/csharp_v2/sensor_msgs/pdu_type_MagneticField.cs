using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class MagneticField
    {
        public Header header { get; set; } = new Header();
        public Vector3 magnetic_field { get; set; } = new Vector3();
        public List<double> magnetic_field_covariance { get; set; } = new List<double>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["magnetic_field"] = ToSerializableValue(magnetic_field);
            dict["magnetic_field_covariance"] = ToSerializableValue(magnetic_field_covariance);
            return dict;
        }

        public static MagneticField FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new MagneticField();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("magnetic_field", out var magnetic_fieldValue))
            {
                obj.magnetic_field = PduRuntime.ConvertObject<Vector3>(magnetic_fieldValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("magnetic_field_covariance", out var magnetic_field_covarianceValue))
            {
                obj.magnetic_field_covariance = PduRuntime.ConvertList<double>(magnetic_field_covarianceValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static MagneticField FromJson(string json)
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
