using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class SimpleVarray
    {
        public List<sbyte> data { get; set; } = new List<sbyte>();
        public List<sbyte> fixed_array { get; set; } = new List<sbyte>();
        public int p_mem1 { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["data"] = ToSerializableValue(data);
            dict["fixed_array"] = ToSerializableValue(fixed_array);
            dict["p_mem1"] = ToSerializableValue(p_mem1);
            return dict;
        }

        public static SimpleVarray FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new SimpleVarray();
            if (dict.TryGetValue("data", out var dataValue))
            {
                obj.data = PduRuntime.ConvertList<sbyte>(dataValue);
            }
            if (dict.TryGetValue("fixed_array", out var fixed_arrayValue))
            {
                obj.fixed_array = PduRuntime.ConvertList<sbyte>(fixed_arrayValue);
            }
            if (dict.TryGetValue("p_mem1", out var p_mem1Value))
            {
                obj.p_mem1 = PduRuntime.ConvertValue<int>(p_mem1Value);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static SimpleVarray FromJson(string json)
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
