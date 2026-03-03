using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class Collision
    {
        public bool collision { get; set; } = false;
        public uint contact_num { get; set; } = 0;
        public Vector3 relative_velocity { get; set; } = new Vector3();
        public List<Point> contact_position { get; set; } = new List<Point>();
        public double restitution_coefficient { get; set; } = 0.0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["collision"] = ToSerializableValue(collision);
            dict["contact_num"] = ToSerializableValue(contact_num);
            dict["relative_velocity"] = ToSerializableValue(relative_velocity);
            dict["contact_position"] = ToSerializableValue(contact_position);
            dict["restitution_coefficient"] = ToSerializableValue(restitution_coefficient);
            return dict;
        }

        public static Collision FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Collision();
            if (dict.TryGetValue("collision", out var collisionValue))
            {
                obj.collision = PduRuntime.ConvertValue<bool>(collisionValue);
            }
            if (dict.TryGetValue("contact_num", out var contact_numValue))
            {
                obj.contact_num = PduRuntime.ConvertValue<uint>(contact_numValue);
            }
            if (dict.TryGetValue("relative_velocity", out var relative_velocityValue))
            {
                obj.relative_velocity = PduRuntime.ConvertObject<Vector3>(relative_velocityValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("contact_position", out var contact_positionValue))
            {
                obj.contact_position = PduRuntime.ConvertObjectList<Point>(contact_positionValue, item => Point.FromDictionary(item));
            }
            if (dict.TryGetValue("restitution_coefficient", out var restitution_coefficientValue))
            {
                obj.restitution_coefficient = PduRuntime.ConvertValue<double>(restitution_coefficientValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Collision FromJson(string json)
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
