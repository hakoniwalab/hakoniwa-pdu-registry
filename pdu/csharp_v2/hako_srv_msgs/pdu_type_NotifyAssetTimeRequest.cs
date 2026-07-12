using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class NotifyAssetTimeRequest
    {
        public ulong session_id { get; set; } = 0;
        public LogicalTime asset_time { get; set; } = new LogicalTime();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["session_id"] = ToSerializableValue(session_id);
            dict["asset_time"] = ToSerializableValue(asset_time);
            return dict;
        }

        public static NotifyAssetTimeRequest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new NotifyAssetTimeRequest();
            if (dict.TryGetValue("session_id", out var session_idValue))
            {
                obj.session_id = PduRuntime.ConvertValue<ulong>(session_idValue);
            }
            if (dict.TryGetValue("asset_time", out var asset_timeValue))
            {
                obj.asset_time = PduRuntime.ConvertObject<LogicalTime>(asset_timeValue, item => LogicalTime.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static NotifyAssetTimeRequest FromJson(string json)
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
