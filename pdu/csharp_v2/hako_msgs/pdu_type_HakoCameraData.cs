using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class HakoCameraData
    {
        public int request_id { get; set; } = 0;
        public CompressedImage image { get; set; } = new CompressedImage();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["request_id"] = ToSerializableValue(request_id);
            dict["image"] = ToSerializableValue(image);
            return dict;
        }

        public static HakoCameraData FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoCameraData();
            if (dict.TryGetValue("request_id", out var request_idValue))
            {
                obj.request_id = PduRuntime.ConvertValue<int>(request_idValue);
            }
            if (dict.TryGetValue("image", out var imageValue))
            {
                obj.image = PduRuntime.ConvertObject<CompressedImage>(imageValue, item => CompressedImage.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoCameraData FromJson(string json)
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
