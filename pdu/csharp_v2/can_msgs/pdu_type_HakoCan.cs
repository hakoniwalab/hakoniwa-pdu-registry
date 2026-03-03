using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.can_msgs
{
    public class HakoCan
    {
        public HakoCanHead head { get; set; } = new HakoCanHead();
        public HakoCanBody body { get; set; } = new HakoCanBody();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["head"] = ToSerializableValue(head);
            dict["body"] = ToSerializableValue(body);
            return dict;
        }

        public static HakoCan FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoCan();
            if (dict.TryGetValue("head", out var headValue))
            {
                obj.head = PduRuntime.ConvertObject<HakoCanHead>(headValue, item => HakoCanHead.FromDictionary(item));
            }
            if (dict.TryGetValue("body", out var bodyValue))
            {
                obj.body = PduRuntime.ConvertObject<HakoCanBody>(bodyValue, item => HakoCanBody.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoCan FromJson(string json)
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
