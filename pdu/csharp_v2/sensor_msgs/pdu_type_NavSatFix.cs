using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class NavSatFix
    {
        public Header header { get; set; } = new Header();
        public NavSatStatus status { get; set; } = new NavSatStatus();
        public double latitude { get; set; } = 0.0;
        public double longitude { get; set; } = 0.0;
        public double altitude { get; set; } = 0.0;
        public List<double> position_covariance { get; set; } = new List<double>();
        public byte position_covariance_type { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["status"] = ToSerializableValue(status);
            dict["latitude"] = ToSerializableValue(latitude);
            dict["longitude"] = ToSerializableValue(longitude);
            dict["altitude"] = ToSerializableValue(altitude);
            dict["position_covariance"] = ToSerializableValue(position_covariance);
            dict["position_covariance_type"] = ToSerializableValue(position_covariance_type);
            return dict;
        }

        public static NavSatFix FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new NavSatFix();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("status", out var statusValue))
            {
                obj.status = PduRuntime.ConvertObject<NavSatStatus>(statusValue, item => NavSatStatus.FromDictionary(item));
            }
            if (dict.TryGetValue("latitude", out var latitudeValue))
            {
                obj.latitude = PduRuntime.ConvertValue<double>(latitudeValue);
            }
            if (dict.TryGetValue("longitude", out var longitudeValue))
            {
                obj.longitude = PduRuntime.ConvertValue<double>(longitudeValue);
            }
            if (dict.TryGetValue("altitude", out var altitudeValue))
            {
                obj.altitude = PduRuntime.ConvertValue<double>(altitudeValue);
            }
            if (dict.TryGetValue("position_covariance", out var position_covarianceValue))
            {
                obj.position_covariance = PduRuntime.ConvertList<double>(position_covarianceValue);
            }
            if (dict.TryGetValue("position_covariance_type", out var position_covariance_typeValue))
            {
                obj.position_covariance_type = PduRuntime.ConvertValue<byte>(position_covariance_typeValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static NavSatFix FromJson(string json)
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
