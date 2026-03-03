using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class ShareObjectOwnerRequest
    {
        public string object_name { get; set; } = string.Empty;
        public uint request_type { get; set; } = 0;
        public uint new_owner_id { get; set; } = 0;
        public ulong request_time { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["object_name"] = ToSerializableValue(object_name);
            dict["request_type"] = ToSerializableValue(request_type);
            dict["new_owner_id"] = ToSerializableValue(new_owner_id);
            dict["request_time"] = ToSerializableValue(request_time);
            return dict;
        }

        public static ShareObjectOwnerRequest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new ShareObjectOwnerRequest();
            if (dict.TryGetValue("object_name", out var object_nameValue))
            {
                obj.object_name = PduRuntime.ConvertValue<string>(object_nameValue);
            }
            if (dict.TryGetValue("request_type", out var request_typeValue))
            {
                obj.request_type = PduRuntime.ConvertValue<uint>(request_typeValue);
            }
            if (dict.TryGetValue("new_owner_id", out var new_owner_idValue))
            {
                obj.new_owner_id = PduRuntime.ConvertValue<uint>(new_owner_idValue);
            }
            if (dict.TryGetValue("request_time", out var request_timeValue))
            {
                obj.request_time = PduRuntime.ConvertValue<ulong>(request_timeValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static ShareObjectOwnerRequest FromJson(string json)
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
