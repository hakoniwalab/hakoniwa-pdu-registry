using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public class Int64MultiArray
    {
        public MultiArrayLayout layout { get; set; } = new MultiArrayLayout();
        public List<long> data { get; set; } = new List<long>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["layout"] = ToSerializableValue(layout);
            dict["data"] = ToSerializableValue(data);
            return dict;
        }

        public static Int64MultiArray FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Int64MultiArray();
            if (dict.TryGetValue("layout", out var layoutValue))
            {
                obj.layout = PduRuntime.ConvertObject<MultiArrayLayout>(layoutValue, item => MultiArrayLayout.FromDictionary(item));
            }
            if (dict.TryGetValue("data", out var dataValue))
            {
                obj.data = PduRuntime.ConvertList<long>(dataValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Int64MultiArray FromJson(string json)
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
