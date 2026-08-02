using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.sample_action_msgs
{
    public class FibonacciFeedback
    {
        public List<int> partial_sequence { get; set; } = new List<int>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["partial_sequence"] = ToSerializableValue(partial_sequence);
            return dict;
        }

        public static FibonacciFeedback FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new FibonacciFeedback();
            if (dict.TryGetValue("partial_sequence", out var partial_sequenceValue))
            {
                obj.partial_sequence = PduRuntime.ConvertList<int>(partial_sequenceValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static FibonacciFeedback FromJson(string json)
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
