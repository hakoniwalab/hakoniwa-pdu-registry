using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class JoinResponse
    {
        public uint status_code { get; set; } = 0;
        public string message { get; set; } = string.Empty;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["status_code"] = ToSerializableValue(status_code);
            dict["message"] = ToSerializableValue(message);
            return dict;
        }

        public static JoinResponse FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new JoinResponse();
            if (dict.TryGetValue("status_code", out var status_codeValue))
            {
                obj.status_code = PduRuntime.ConvertValue<uint>(status_codeValue);
            }
            if (dict.TryGetValue("message", out var messageValue))
            {
                obj.message = PduRuntime.ConvertValue<string>(messageValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static JoinResponse FromJson(string json)
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
