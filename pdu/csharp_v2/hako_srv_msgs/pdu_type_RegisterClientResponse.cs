using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class RegisterClientResponse
    {
        public uint service_id { get; set; } = 0;
        public uint client_id { get; set; } = 0;
        public uint request_channel_id { get; set; } = 0;
        public uint response_channel_id { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["service_id"] = ToSerializableValue(service_id);
            dict["client_id"] = ToSerializableValue(client_id);
            dict["request_channel_id"] = ToSerializableValue(request_channel_id);
            dict["response_channel_id"] = ToSerializableValue(response_channel_id);
            return dict;
        }

        public static RegisterClientResponse FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new RegisterClientResponse();
            if (dict.TryGetValue("service_id", out var service_idValue))
            {
                obj.service_id = PduRuntime.ConvertValue<uint>(service_idValue);
            }
            if (dict.TryGetValue("client_id", out var client_idValue))
            {
                obj.client_id = PduRuntime.ConvertValue<uint>(client_idValue);
            }
            if (dict.TryGetValue("request_channel_id", out var request_channel_idValue))
            {
                obj.request_channel_id = PduRuntime.ConvertValue<uint>(request_channel_idValue);
            }
            if (dict.TryGetValue("response_channel_id", out var response_channel_idValue))
            {
                obj.response_channel_id = PduRuntime.ConvertValue<uint>(response_channel_idValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static RegisterClientResponse FromJson(string json)
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
