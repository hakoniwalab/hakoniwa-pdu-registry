using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.sample_action_msgs
{
    public class FibonacciResult
    {
        public List<int> sequence { get; set; } = new List<int>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["sequence"] = ToSerializableValue(sequence);
            return dict;
        }

        public static FibonacciResult FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new FibonacciResult();
            if (dict.TryGetValue("sequence", out var sequenceValue))
            {
                obj.sequence = PduRuntime.ConvertList<int>(sequenceValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static FibonacciResult FromJson(string json)
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
