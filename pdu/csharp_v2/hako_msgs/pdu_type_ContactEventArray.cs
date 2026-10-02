using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class ContactEventArray
    {
        public List<ContactEvent> events { get; set; } = new List<ContactEvent>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["events"] = ToSerializableValue(events);
            return dict;
        }

        public static ContactEventArray FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new ContactEventArray();
            if (dict.TryGetValue("events", out var eventsValue))
            {
                obj.events = PduRuntime.ConvertObjectList<ContactEvent>(eventsValue, item => ContactEvent.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static ContactEventArray FromJson(string json)
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
