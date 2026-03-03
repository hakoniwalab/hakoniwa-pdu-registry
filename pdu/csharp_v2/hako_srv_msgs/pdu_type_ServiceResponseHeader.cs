using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class ServiceResponseHeader
    {
        public uint request_id { get; set; } = 0;
        public string service_name { get; set; } = string.Empty;
        public string client_name { get; set; } = string.Empty;
        public byte status { get; set; } = 0;
        public byte processing_percentage { get; set; } = 0;
        public int result_code { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["request_id"] = ToSerializableValue(request_id);
            dict["service_name"] = ToSerializableValue(service_name);
            dict["client_name"] = ToSerializableValue(client_name);
            dict["status"] = ToSerializableValue(status);
            dict["processing_percentage"] = ToSerializableValue(processing_percentage);
            dict["result_code"] = ToSerializableValue(result_code);
            return dict;
        }

        public static ServiceResponseHeader FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new ServiceResponseHeader();
            if (dict.TryGetValue("request_id", out var request_idValue))
            {
                obj.request_id = PduRuntime.ConvertValue<uint>(request_idValue);
            }
            if (dict.TryGetValue("service_name", out var service_nameValue))
            {
                obj.service_name = PduRuntime.ConvertValue<string>(service_nameValue);
            }
            if (dict.TryGetValue("client_name", out var client_nameValue))
            {
                obj.client_name = PduRuntime.ConvertValue<string>(client_nameValue);
            }
            if (dict.TryGetValue("status", out var statusValue))
            {
                obj.status = PduRuntime.ConvertValue<byte>(statusValue);
            }
            if (dict.TryGetValue("processing_percentage", out var processing_percentageValue))
            {
                obj.processing_percentage = PduRuntime.ConvertValue<byte>(processing_percentageValue);
            }
            if (dict.TryGetValue("result_code", out var result_codeValue))
            {
                obj.result_code = PduRuntime.ConvertValue<int>(result_codeValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static ServiceResponseHeader FromJson(string json)
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
