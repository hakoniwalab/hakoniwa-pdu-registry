using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class HakoCmdHeader
    {
        public bool request { get; set; } = false;
        public bool result { get; set; } = false;
        public int result_code { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["request"] = ToSerializableValue(request);
            dict["result"] = ToSerializableValue(result);
            dict["result_code"] = ToSerializableValue(result_code);
            return dict;
        }

        public static HakoCmdHeader FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoCmdHeader();
            if (dict.TryGetValue("request", out var requestValue))
            {
                obj.request = PduRuntime.ConvertValue<bool>(requestValue);
            }
            if (dict.TryGetValue("result", out var resultValue))
            {
                obj.result = PduRuntime.ConvertValue<bool>(resultValue);
            }
            if (dict.TryGetValue("result_code", out var result_codeValue))
            {
                obj.result_code = PduRuntime.ConvertValue<int>(result_codeValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoCmdHeader FromJson(string json)
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
