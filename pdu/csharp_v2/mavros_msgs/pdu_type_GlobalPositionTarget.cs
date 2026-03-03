using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.mavros_msgs
{
    public class GlobalPositionTarget
    {
        public Header header { get; set; } = new Header();
        public byte coordinate_frame { get; set; } = 0;
        public ushort type_mask { get; set; } = 0;
        public double latitude { get; set; } = 0.0;
        public double longitude { get; set; } = 0.0;
        public float altitude { get; set; } = 0.0F;
        public Vector3 velocity { get; set; } = new Vector3();
        public Vector3 acceleration_or_force { get; set; } = new Vector3();
        public float yaw { get; set; } = 0.0F;
        public float yaw_rate { get; set; } = 0.0F;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["coordinate_frame"] = ToSerializableValue(coordinate_frame);
            dict["type_mask"] = ToSerializableValue(type_mask);
            dict["latitude"] = ToSerializableValue(latitude);
            dict["longitude"] = ToSerializableValue(longitude);
            dict["altitude"] = ToSerializableValue(altitude);
            dict["velocity"] = ToSerializableValue(velocity);
            dict["acceleration_or_force"] = ToSerializableValue(acceleration_or_force);
            dict["yaw"] = ToSerializableValue(yaw);
            dict["yaw_rate"] = ToSerializableValue(yaw_rate);
            return dict;
        }

        public static GlobalPositionTarget FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new GlobalPositionTarget();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("coordinate_frame", out var coordinate_frameValue))
            {
                obj.coordinate_frame = PduRuntime.ConvertValue<byte>(coordinate_frameValue);
            }
            if (dict.TryGetValue("type_mask", out var type_maskValue))
            {
                obj.type_mask = PduRuntime.ConvertValue<ushort>(type_maskValue);
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
                obj.altitude = PduRuntime.ConvertValue<float>(altitudeValue);
            }
            if (dict.TryGetValue("velocity", out var velocityValue))
            {
                obj.velocity = PduRuntime.ConvertObject<Vector3>(velocityValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("acceleration_or_force", out var acceleration_or_forceValue))
            {
                obj.acceleration_or_force = PduRuntime.ConvertObject<Vector3>(acceleration_or_forceValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("yaw", out var yawValue))
            {
                obj.yaw = PduRuntime.ConvertValue<float>(yawValue);
            }
            if (dict.TryGetValue("yaw_rate", out var yaw_rateValue))
            {
                obj.yaw_rate = PduRuntime.ConvertValue<float>(yaw_rateValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static GlobalPositionTarget FromJson(string json)
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
