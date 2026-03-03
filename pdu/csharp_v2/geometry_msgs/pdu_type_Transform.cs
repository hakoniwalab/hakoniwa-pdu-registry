using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public class Transform
    {
        public Vector3 translation { get; set; } = new Vector3();
        public Quaternion rotation { get; set; } = new Quaternion();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["translation"] = ToSerializableValue(translation);
            dict["rotation"] = ToSerializableValue(rotation);
            return dict;
        }

        public static Transform FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Transform();
            if (dict.TryGetValue("translation", out var translationValue))
            {
                obj.translation = PduRuntime.ConvertObject<Vector3>(translationValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("rotation", out var rotationValue))
            {
                obj.rotation = PduRuntime.ConvertObject<Quaternion>(rotationValue, item => Quaternion.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Transform FromJson(string json)
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
