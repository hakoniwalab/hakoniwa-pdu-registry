using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class AttachResponse
    {
        public uint result_code { get; set; } = 0;
        public ulong session_id { get; set; } = 0;
        public LogicalTime world_time { get; set; } = new LogicalTime();
        public ulong delta_asset_tick { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["result_code"] = ToSerializableValue(result_code);
            dict["session_id"] = ToSerializableValue(session_id);
            dict["world_time"] = ToSerializableValue(world_time);
            dict["delta_asset_tick"] = ToSerializableValue(delta_asset_tick);
            return dict;
        }

        public static AttachResponse FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new AttachResponse();
            if (dict.TryGetValue("result_code", out var result_codeValue))
            {
                obj.result_code = PduRuntime.ConvertValue<uint>(result_codeValue);
            }
            if (dict.TryGetValue("session_id", out var session_idValue))
            {
                obj.session_id = PduRuntime.ConvertValue<ulong>(session_idValue);
            }
            if (dict.TryGetValue("world_time", out var world_timeValue))
            {
                obj.world_time = PduRuntime.ConvertObject<LogicalTime>(world_timeValue, item => LogicalTime.FromDictionary(item));
            }
            if (dict.TryGetValue("delta_asset_tick", out var delta_asset_tickValue))
            {
                obj.delta_asset_tick = PduRuntime.ConvertValue<ulong>(delta_asset_tickValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static AttachResponse FromJson(string json)
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
