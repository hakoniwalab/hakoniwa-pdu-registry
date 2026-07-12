using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class GetWorldTimeResponse
    {
        public uint result_code { get; set; } = 0;
        public LogicalTime world_time { get; set; } = new LogicalTime();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["result_code"] = ToSerializableValue(result_code);
            dict["world_time"] = ToSerializableValue(world_time);
            return dict;
        }

        public static GetWorldTimeResponse FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new GetWorldTimeResponse();
            if (dict.TryGetValue("result_code", out var result_codeValue))
            {
                obj.result_code = PduRuntime.ConvertValue<uint>(result_codeValue);
            }
            if (dict.TryGetValue("world_time", out var world_timeValue))
            {
                obj.world_time = PduRuntime.ConvertObject<LogicalTime>(world_timeValue, item => LogicalTime.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static GetWorldTimeResponse FromJson(string json)
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
