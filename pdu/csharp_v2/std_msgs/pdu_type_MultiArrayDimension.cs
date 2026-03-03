using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public class MultiArrayDimension
    {
        public string label { get; set; } = string.Empty;
        public uint size { get; set; } = 0;
        public uint stride { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["label"] = ToSerializableValue(label);
            dict["size"] = ToSerializableValue(size);
            dict["stride"] = ToSerializableValue(stride);
            return dict;
        }

        public static MultiArrayDimension FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new MultiArrayDimension();
            if (dict.TryGetValue("label", out var labelValue))
            {
                obj.label = PduRuntime.ConvertValue<string>(labelValue);
            }
            if (dict.TryGetValue("size", out var sizeValue))
            {
                obj.size = PduRuntime.ConvertValue<uint>(sizeValue);
            }
            if (dict.TryGetValue("stride", out var strideValue))
            {
                obj.stride = PduRuntime.ConvertValue<uint>(strideValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static MultiArrayDimension FromJson(string json)
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
