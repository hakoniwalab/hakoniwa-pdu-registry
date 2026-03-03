using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public class DroneGetStateResponsePacket
    {
        public ServiceResponseHeader header { get; set; } = new ServiceResponseHeader();
        public DroneGetStateResponse body { get; set; } = new DroneGetStateResponse();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["body"] = ToSerializableValue(body);
            return dict;
        }

        public static DroneGetStateResponsePacket FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new DroneGetStateResponsePacket();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<ServiceResponseHeader>(headerValue, item => ServiceResponseHeader.FromDictionary(item));
            }
            if (dict.TryGetValue("body", out var bodyValue))
            {
                obj.body = PduRuntime.ConvertObject<DroneGetStateResponse>(bodyValue, item => DroneGetStateResponse.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static DroneGetStateResponsePacket FromJson(string json)
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
