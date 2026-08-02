using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.hako_action_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sample_action_msgs
{
    public class FibonacciActionResponse
    {
        public ActionResponseHeader header { get; set; } = new ActionResponseHeader();
        public FibonacciResult body { get; set; } = new FibonacciResult();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["body"] = ToSerializableValue(body);
            return dict;
        }

        public static FibonacciActionResponse FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new FibonacciActionResponse();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<ActionResponseHeader>(headerValue, item => ActionResponseHeader.FromDictionary(item));
            }
            if (dict.TryGetValue("body", out var bodyValue))
            {
                obj.body = PduRuntime.ConvertObject<FibonacciResult>(bodyValue, item => FibonacciResult.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static FibonacciActionResponse FromJson(string json)
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
