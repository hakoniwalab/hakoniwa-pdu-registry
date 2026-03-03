using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class ImpulseCollision
    {
        public bool collision { get; set; } = false;
        public bool is_target_static { get; set; } = false;
        public double restitution_coefficient { get; set; } = 0.0;
        public Point self_contact_vector { get; set; } = new Point();
        public Vector3 normal { get; set; } = new Vector3();
        public Point target_contact_vector { get; set; } = new Point();
        public Vector3 target_velocity { get; set; } = new Vector3();
        public Vector3 target_angular_velocity { get; set; } = new Vector3();
        public Vector3 target_euler { get; set; } = new Vector3();
        public Vector3 target_inertia { get; set; } = new Vector3();
        public double target_mass { get; set; } = 0.0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["collision"] = ToSerializableValue(collision);
            dict["is_target_static"] = ToSerializableValue(is_target_static);
            dict["restitution_coefficient"] = ToSerializableValue(restitution_coefficient);
            dict["self_contact_vector"] = ToSerializableValue(self_contact_vector);
            dict["normal"] = ToSerializableValue(normal);
            dict["target_contact_vector"] = ToSerializableValue(target_contact_vector);
            dict["target_velocity"] = ToSerializableValue(target_velocity);
            dict["target_angular_velocity"] = ToSerializableValue(target_angular_velocity);
            dict["target_euler"] = ToSerializableValue(target_euler);
            dict["target_inertia"] = ToSerializableValue(target_inertia);
            dict["target_mass"] = ToSerializableValue(target_mass);
            return dict;
        }

        public static ImpulseCollision FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new ImpulseCollision();
            if (dict.TryGetValue("collision", out var collisionValue))
            {
                obj.collision = PduRuntime.ConvertValue<bool>(collisionValue);
            }
            if (dict.TryGetValue("is_target_static", out var is_target_staticValue))
            {
                obj.is_target_static = PduRuntime.ConvertValue<bool>(is_target_staticValue);
            }
            if (dict.TryGetValue("restitution_coefficient", out var restitution_coefficientValue))
            {
                obj.restitution_coefficient = PduRuntime.ConvertValue<double>(restitution_coefficientValue);
            }
            if (dict.TryGetValue("self_contact_vector", out var self_contact_vectorValue))
            {
                obj.self_contact_vector = PduRuntime.ConvertObject<Point>(self_contact_vectorValue, item => Point.FromDictionary(item));
            }
            if (dict.TryGetValue("normal", out var normalValue))
            {
                obj.normal = PduRuntime.ConvertObject<Vector3>(normalValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("target_contact_vector", out var target_contact_vectorValue))
            {
                obj.target_contact_vector = PduRuntime.ConvertObject<Point>(target_contact_vectorValue, item => Point.FromDictionary(item));
            }
            if (dict.TryGetValue("target_velocity", out var target_velocityValue))
            {
                obj.target_velocity = PduRuntime.ConvertObject<Vector3>(target_velocityValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("target_angular_velocity", out var target_angular_velocityValue))
            {
                obj.target_angular_velocity = PduRuntime.ConvertObject<Vector3>(target_angular_velocityValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("target_euler", out var target_eulerValue))
            {
                obj.target_euler = PduRuntime.ConvertObject<Vector3>(target_eulerValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("target_inertia", out var target_inertiaValue))
            {
                obj.target_inertia = PduRuntime.ConvertObject<Vector3>(target_inertiaValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("target_mass", out var target_massValue))
            {
                obj.target_mass = PduRuntime.ConvertValue<double>(target_massValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static ImpulseCollision FromJson(string json)
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
