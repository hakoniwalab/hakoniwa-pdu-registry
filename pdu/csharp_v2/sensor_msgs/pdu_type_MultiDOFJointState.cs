using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class MultiDOFJointState
    {
        public Header header { get; set; } = new Header();
        public List<string> joint_names { get; set; } = new List<string>();
        public List<Transform> transforms { get; set; } = new List<Transform>();
        public List<Twist> twist { get; set; } = new List<Twist>();
        public List<Wrench> wrench { get; set; } = new List<Wrench>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["joint_names"] = ToSerializableValue(joint_names);
            dict["transforms"] = ToSerializableValue(transforms);
            dict["twist"] = ToSerializableValue(twist);
            dict["wrench"] = ToSerializableValue(wrench);
            return dict;
        }

        public static MultiDOFJointState FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new MultiDOFJointState();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("joint_names", out var joint_namesValue))
            {
                obj.joint_names = PduRuntime.ConvertList<string>(joint_namesValue);
            }
            if (dict.TryGetValue("transforms", out var transformsValue))
            {
                obj.transforms = PduRuntime.ConvertObjectList<Transform>(transformsValue, item => Transform.FromDictionary(item));
            }
            if (dict.TryGetValue("twist", out var twistValue))
            {
                obj.twist = PduRuntime.ConvertObjectList<Twist>(twistValue, item => Twist.FromDictionary(item));
            }
            if (dict.TryGetValue("wrench", out var wrenchValue))
            {
                obj.wrench = PduRuntime.ConvertObjectList<Wrench>(wrenchValue, item => Wrench.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static MultiDOFJointState FromJson(string json)
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
