using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public class Empty
    {
        public byte hako_dummy { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["hako_dummy"] = ToSerializableValue(hako_dummy);
            return dict;
        }

        public static Empty FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Empty();
            if (dict.TryGetValue("hako_dummy", out var hako_dummyValue))
            {
                obj.hako_dummy = PduRuntime.ConvertValue<byte>(hako_dummyValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Empty FromJson(string json)
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
