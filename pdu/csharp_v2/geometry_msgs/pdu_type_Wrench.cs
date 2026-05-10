using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public class Wrench
    {
        public Vector3 force { get; set; } = new Vector3();
        public Vector3 torque { get; set; } = new Vector3();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["force"] = ToSerializableValue(force);
            dict["torque"] = ToSerializableValue(torque);
            return dict;
        }

        public static Wrench FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Wrench();
            if (dict.TryGetValue("force", out var forceValue))
            {
                obj.force = PduRuntime.ConvertObject<Vector3>(forceValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("torque", out var torqueValue))
            {
                obj.torque = PduRuntime.ConvertObject<Vector3>(torqueValue, item => Vector3.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Wrench FromJson(string json)
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
