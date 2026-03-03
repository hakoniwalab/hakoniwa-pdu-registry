using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public class MultiArrayLayout
    {
        public List<MultiArrayDimension> dim { get; set; } = new List<MultiArrayDimension>();
        public uint data_offset { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["dim"] = ToSerializableValue(dim);
            dict["data_offset"] = ToSerializableValue(data_offset);
            return dict;
        }

        public static MultiArrayLayout FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new MultiArrayLayout();
            if (dict.TryGetValue("dim", out var dimValue))
            {
                obj.dim = PduRuntime.ConvertObjectList<MultiArrayDimension>(dimValue, item => MultiArrayDimension.FromDictionary(item));
            }
            if (dict.TryGetValue("data_offset", out var data_offsetValue))
            {
                obj.data_offset = PduRuntime.ConvertValue<uint>(data_offsetValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static MultiArrayLayout FromJson(string json)
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
