using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class AckEventRequest
    {
        public string name { get; set; } = string.Empty;
        public uint event_code { get; set; } = 0;
        public uint result_code { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["name"] = ToSerializableValue(name);
            dict["event_code"] = ToSerializableValue(event_code);
            dict["result_code"] = ToSerializableValue(result_code);
            return dict;
        }

        public static AckEventRequest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new AckEventRequest();
            if (dict.TryGetValue("name", out var nameValue))
            {
                obj.name = PduRuntime.ConvertValue<string>(nameValue);
            }
            if (dict.TryGetValue("event_code", out var event_codeValue))
            {
                obj.event_code = PduRuntime.ConvertValue<uint>(event_codeValue);
            }
            if (dict.TryGetValue("result_code", out var result_codeValue))
            {
                obj.result_code = PduRuntime.ConvertValue<uint>(result_codeValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static AckEventRequest FromJson(string json)
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
