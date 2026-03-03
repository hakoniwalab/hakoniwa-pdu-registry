using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class HakoCmdMagnetHolder
    {
        public HakoCmdHeader header { get; set; } = new HakoCmdHeader();
        public bool magnet_on { get; set; } = false;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["magnet_on"] = ToSerializableValue(magnet_on);
            return dict;
        }

        public static HakoCmdMagnetHolder FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoCmdMagnetHolder();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<HakoCmdHeader>(headerValue, item => HakoCmdHeader.FromDictionary(item));
            }
            if (dict.TryGetValue("magnet_on", out var magnet_onValue))
            {
                obj.magnet_on = PduRuntime.ConvertValue<bool>(magnet_onValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoCmdMagnetHolder FromJson(string json)
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
