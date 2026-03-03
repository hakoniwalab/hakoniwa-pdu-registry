using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.mavros_msgs
{
    public class AttitudeTarget
    {
        public Header header { get; set; } = new Header();
        public byte type_mask { get; set; } = 0;
        public Quaternion orientation { get; set; } = new Quaternion();
        public Vector3 body_rate { get; set; } = new Vector3();
        public float thrust { get; set; } = 0.0F;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["type_mask"] = ToSerializableValue(type_mask);
            dict["orientation"] = ToSerializableValue(orientation);
            dict["body_rate"] = ToSerializableValue(body_rate);
            dict["thrust"] = ToSerializableValue(thrust);
            return dict;
        }

        public static AttitudeTarget FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new AttitudeTarget();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("type_mask", out var type_maskValue))
            {
                obj.type_mask = PduRuntime.ConvertValue<byte>(type_maskValue);
            }
            if (dict.TryGetValue("orientation", out var orientationValue))
            {
                obj.orientation = PduRuntime.ConvertObject<Quaternion>(orientationValue, item => Quaternion.FromDictionary(item));
            }
            if (dict.TryGetValue("body_rate", out var body_rateValue))
            {
                obj.body_rate = PduRuntime.ConvertObject<Vector3>(body_rateValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("thrust", out var thrustValue))
            {
                obj.thrust = PduRuntime.ConvertValue<float>(thrustValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static AttitudeTarget FromJson(string json)
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
