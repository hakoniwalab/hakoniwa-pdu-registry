using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class RelativeHumidity
    {
        public Header header { get; set; } = new Header();
        public double relative_humidity { get; set; } = 0.0;
        public double variance { get; set; } = 0.0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["relative_humidity"] = ToSerializableValue(relative_humidity);
            dict["variance"] = ToSerializableValue(variance);
            return dict;
        }

        public static RelativeHumidity FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new RelativeHumidity();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("relative_humidity", out var relative_humidityValue))
            {
                obj.relative_humidity = PduRuntime.ConvertValue<double>(relative_humidityValue);
            }
            if (dict.TryGetValue("variance", out var varianceValue))
            {
                obj.variance = PduRuntime.ConvertValue<double>(varianceValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static RelativeHumidity FromJson(string json)
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
