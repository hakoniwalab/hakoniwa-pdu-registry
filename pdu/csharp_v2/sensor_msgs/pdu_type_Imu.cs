using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class Imu
    {
        public Header header { get; set; } = new Header();
        public Quaternion orientation { get; set; } = new Quaternion();
        public List<double> orientation_covariance { get; set; } = new List<double>();
        public Vector3 angular_velocity { get; set; } = new Vector3();
        public List<double> angular_velocity_covariance { get; set; } = new List<double>();
        public Vector3 linear_acceleration { get; set; } = new Vector3();
        public List<double> linear_acceleration_covariance { get; set; } = new List<double>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["orientation"] = ToSerializableValue(orientation);
            dict["orientation_covariance"] = ToSerializableValue(orientation_covariance);
            dict["angular_velocity"] = ToSerializableValue(angular_velocity);
            dict["angular_velocity_covariance"] = ToSerializableValue(angular_velocity_covariance);
            dict["linear_acceleration"] = ToSerializableValue(linear_acceleration);
            dict["linear_acceleration_covariance"] = ToSerializableValue(linear_acceleration_covariance);
            return dict;
        }

        public static Imu FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Imu();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("orientation", out var orientationValue))
            {
                obj.orientation = PduRuntime.ConvertObject<Quaternion>(orientationValue, item => Quaternion.FromDictionary(item));
            }
            if (dict.TryGetValue("orientation_covariance", out var orientation_covarianceValue))
            {
                obj.orientation_covariance = PduRuntime.ConvertList<double>(orientation_covarianceValue);
            }
            if (dict.TryGetValue("angular_velocity", out var angular_velocityValue))
            {
                obj.angular_velocity = PduRuntime.ConvertObject<Vector3>(angular_velocityValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("angular_velocity_covariance", out var angular_velocity_covarianceValue))
            {
                obj.angular_velocity_covariance = PduRuntime.ConvertList<double>(angular_velocity_covarianceValue);
            }
            if (dict.TryGetValue("linear_acceleration", out var linear_accelerationValue))
            {
                obj.linear_acceleration = PduRuntime.ConvertObject<Vector3>(linear_accelerationValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("linear_acceleration_covariance", out var linear_acceleration_covarianceValue))
            {
                obj.linear_acceleration_covariance = PduRuntime.ConvertList<double>(linear_acceleration_covarianceValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Imu FromJson(string json)
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
