using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class JointState
    {
        public Header header { get; set; } = new Header();
        public List<string> name { get; set; } = new List<string>();
        public List<double> position { get; set; } = new List<double>();
        public List<double> velocity { get; set; } = new List<double>();
        public List<double> effort { get; set; } = new List<double>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["name"] = ToSerializableValue(name);
            dict["position"] = ToSerializableValue(position);
            dict["velocity"] = ToSerializableValue(velocity);
            dict["effort"] = ToSerializableValue(effort);
            return dict;
        }

        public static JointState FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new JointState();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("name", out var nameValue))
            {
                obj.name = PduRuntime.ConvertList<string>(nameValue);
            }
            if (dict.TryGetValue("position", out var positionValue))
            {
                obj.position = PduRuntime.ConvertList<double>(positionValue);
            }
            if (dict.TryGetValue("velocity", out var velocityValue))
            {
                obj.velocity = PduRuntime.ConvertList<double>(velocityValue);
            }
            if (dict.TryGetValue("effort", out var effortValue))
            {
                obj.effort = PduRuntime.ConvertList<double>(effortValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static JointState FromJson(string json)
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
