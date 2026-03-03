using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public class CameraCaptureImageRequest
    {
        public string drone_name { get; set; } = string.Empty;
        public string image_type { get; set; } = string.Empty;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["drone_name"] = ToSerializableValue(drone_name);
            dict["image_type"] = ToSerializableValue(image_type);
            return dict;
        }

        public static CameraCaptureImageRequest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new CameraCaptureImageRequest();
            if (dict.TryGetValue("drone_name", out var drone_nameValue))
            {
                obj.drone_name = PduRuntime.ConvertValue<string>(drone_nameValue);
            }
            if (dict.TryGetValue("image_type", out var image_typeValue))
            {
                obj.image_type = PduRuntime.ConvertValue<string>(image_typeValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static CameraCaptureImageRequest FromJson(string json)
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
