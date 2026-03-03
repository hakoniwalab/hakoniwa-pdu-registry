using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class CompressedImage
    {
        public Header header { get; set; } = new Header();
        public string format { get; set; } = string.Empty;
        public List<byte> data { get; set; } = new List<byte>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["format"] = ToSerializableValue(format);
            dict["data"] = ToSerializableValue(data);
            return dict;
        }

        public static CompressedImage FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new CompressedImage();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("format", out var formatValue))
            {
                obj.format = PduRuntime.ConvertValue<string>(formatValue);
            }
            if (dict.TryGetValue("data", out var dataValue))
            {
                obj.data = PduRuntime.ConvertList<byte>(dataValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static CompressedImage FromJson(string json)
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
