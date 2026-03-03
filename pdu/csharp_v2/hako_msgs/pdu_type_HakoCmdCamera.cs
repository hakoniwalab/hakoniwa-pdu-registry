using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class HakoCmdCamera
    {
        public HakoCmdHeader header { get; set; } = new HakoCmdHeader();
        public int request_id { get; set; } = 0;
        public int encode_type { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["request_id"] = ToSerializableValue(request_id);
            dict["encode_type"] = ToSerializableValue(encode_type);
            return dict;
        }

        public static HakoCmdCamera FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoCmdCamera();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<HakoCmdHeader>(headerValue, item => HakoCmdHeader.FromDictionary(item));
            }
            if (dict.TryGetValue("request_id", out var request_idValue))
            {
                obj.request_id = PduRuntime.ConvertValue<int>(request_idValue);
            }
            if (dict.TryGetValue("encode_type", out var encode_typeValue))
            {
                obj.encode_type = PduRuntime.ConvertValue<int>(encode_typeValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoCmdCamera FromJson(string json)
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
