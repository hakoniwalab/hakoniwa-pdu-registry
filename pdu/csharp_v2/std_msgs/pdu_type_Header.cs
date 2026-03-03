using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public class Header
    {
        public Time stamp { get; set; } = new Time();
        public string frame_id { get; set; } = string.Empty;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["stamp"] = ToSerializableValue(stamp);
            dict["frame_id"] = ToSerializableValue(frame_id);
            return dict;
        }

        public static Header FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Header();
            if (dict.TryGetValue("stamp", out var stampValue))
            {
                obj.stamp = PduRuntime.ConvertObject<Time>(stampValue, item => Time.FromDictionary(item));
            }
            if (dict.TryGetValue("frame_id", out var frame_idValue))
            {
                obj.frame_id = PduRuntime.ConvertValue<string>(frame_idValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Header FromJson(string json)
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
