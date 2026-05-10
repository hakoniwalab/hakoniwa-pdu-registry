using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.tf2_msgs
{
    public class TF2Error
    {
        public byte error { get; set; } = 0;
        public string error_string { get; set; } = string.Empty;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["error"] = ToSerializableValue(error);
            dict["error_string"] = ToSerializableValue(error_string);
            return dict;
        }

        public static TF2Error FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new TF2Error();
            if (dict.TryGetValue("error", out var errorValue))
            {
                obj.error = PduRuntime.ConvertValue<byte>(errorValue);
            }
            if (dict.TryGetValue("error_string", out var error_stringValue))
            {
                obj.error_string = PduRuntime.ConvertValue<string>(error_stringValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static TF2Error FromJson(string json)
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
