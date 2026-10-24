using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class RenderObject
    {
        public string name { get; set; } = string.Empty;
        public string model { get; set; } = string.Empty;
        public Pose pose { get; set; } = new Pose();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["name"] = ToSerializableValue(name);
            dict["model"] = ToSerializableValue(model);
            dict["pose"] = ToSerializableValue(pose);
            return dict;
        }

        public static RenderObject FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new RenderObject();
            if (dict.TryGetValue("name", out var nameValue))
            {
                obj.name = PduRuntime.ConvertValue<string>(nameValue);
            }
            if (dict.TryGetValue("model", out var modelValue))
            {
                obj.model = PduRuntime.ConvertValue<string>(modelValue);
            }
            if (dict.TryGetValue("pose", out var poseValue))
            {
                obj.pose = PduRuntime.ConvertObject<Pose>(poseValue, item => Pose.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static RenderObject FromJson(string json)
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
