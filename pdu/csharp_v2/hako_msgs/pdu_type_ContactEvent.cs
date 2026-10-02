using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class ContactEvent
    {
        public Time stamp { get; set; } = new Time();
        public string self_name { get; set; } = string.Empty;
        public string other_name { get; set; } = string.Empty;
        public string other_kind { get; set; } = string.Empty;
        public Point position { get; set; } = new Point();
        public double relative_speed { get; set; } = 0.0;
        public bool started { get; set; } = false;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["stamp"] = ToSerializableValue(stamp);
            dict["self_name"] = ToSerializableValue(self_name);
            dict["other_name"] = ToSerializableValue(other_name);
            dict["other_kind"] = ToSerializableValue(other_kind);
            dict["position"] = ToSerializableValue(position);
            dict["relative_speed"] = ToSerializableValue(relative_speed);
            dict["started"] = ToSerializableValue(started);
            return dict;
        }

        public static ContactEvent FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new ContactEvent();
            if (dict.TryGetValue("stamp", out var stampValue))
            {
                obj.stamp = PduRuntime.ConvertObject<Time>(stampValue, item => Time.FromDictionary(item));
            }
            if (dict.TryGetValue("self_name", out var self_nameValue))
            {
                obj.self_name = PduRuntime.ConvertValue<string>(self_nameValue);
            }
            if (dict.TryGetValue("other_name", out var other_nameValue))
            {
                obj.other_name = PduRuntime.ConvertValue<string>(other_nameValue);
            }
            if (dict.TryGetValue("other_kind", out var other_kindValue))
            {
                obj.other_kind = PduRuntime.ConvertValue<string>(other_kindValue);
            }
            if (dict.TryGetValue("position", out var positionValue))
            {
                obj.position = PduRuntime.ConvertObject<Point>(positionValue, item => Point.FromDictionary(item));
            }
            if (dict.TryGetValue("relative_speed", out var relative_speedValue))
            {
                obj.relative_speed = PduRuntime.ConvertValue<double>(relative_speedValue);
            }
            if (dict.TryGetValue("started", out var startedValue))
            {
                obj.started = PduRuntime.ConvertValue<bool>(startedValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static ContactEvent FromJson(string json)
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
