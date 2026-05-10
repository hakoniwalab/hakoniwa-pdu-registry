using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class Range
    {
        public Header header { get; set; } = new Header();
        public byte radiation_type { get; set; } = 0;
        public float field_of_view { get; set; } = 0.0F;
        public float min_range { get; set; } = 0.0F;
        public float max_range { get; set; } = 0.0F;
        public float range { get; set; } = 0.0F;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["radiation_type"] = ToSerializableValue(radiation_type);
            dict["field_of_view"] = ToSerializableValue(field_of_view);
            dict["min_range"] = ToSerializableValue(min_range);
            dict["max_range"] = ToSerializableValue(max_range);
            dict["range"] = ToSerializableValue(range);
            return dict;
        }

        public static Range FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Range();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("radiation_type", out var radiation_typeValue))
            {
                obj.radiation_type = PduRuntime.ConvertValue<byte>(radiation_typeValue);
            }
            if (dict.TryGetValue("field_of_view", out var field_of_viewValue))
            {
                obj.field_of_view = PduRuntime.ConvertValue<float>(field_of_viewValue);
            }
            if (dict.TryGetValue("min_range", out var min_rangeValue))
            {
                obj.min_range = PduRuntime.ConvertValue<float>(min_rangeValue);
            }
            if (dict.TryGetValue("max_range", out var max_rangeValue))
            {
                obj.max_range = PduRuntime.ConvertValue<float>(max_rangeValue);
            }
            if (dict.TryGetValue("range", out var rangeValue))
            {
                obj.range = PduRuntime.ConvertValue<float>(rangeValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Range FromJson(string json)
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
