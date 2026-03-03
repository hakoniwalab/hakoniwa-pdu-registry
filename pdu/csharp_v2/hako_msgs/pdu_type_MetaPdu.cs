using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class MetaPdu
    {
        public uint total_len { get; set; } = 0;
        public uint magicno { get; set; } = 0;
        public ushort version { get; set; } = 0;
        public ushort flags { get; set; } = 0;
        public uint meta_request_type { get; set; } = 0;
        public ulong hako_time_us { get; set; } = 0;
        public ulong asset_time_us { get; set; } = 0;
        public ulong real_time_us { get; set; } = 0;
        public string robot_name { get; set; } = string.Empty;
        public int channel_id { get; set; } = 0;
        public uint body_len { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["total_len"] = ToSerializableValue(total_len);
            dict["magicno"] = ToSerializableValue(magicno);
            dict["version"] = ToSerializableValue(version);
            dict["flags"] = ToSerializableValue(flags);
            dict["meta_request_type"] = ToSerializableValue(meta_request_type);
            dict["hako_time_us"] = ToSerializableValue(hako_time_us);
            dict["asset_time_us"] = ToSerializableValue(asset_time_us);
            dict["real_time_us"] = ToSerializableValue(real_time_us);
            dict["robot_name"] = ToSerializableValue(robot_name);
            dict["channel_id"] = ToSerializableValue(channel_id);
            dict["body_len"] = ToSerializableValue(body_len);
            return dict;
        }

        public static MetaPdu FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new MetaPdu();
            if (dict.TryGetValue("total_len", out var total_lenValue))
            {
                obj.total_len = PduRuntime.ConvertValue<uint>(total_lenValue);
            }
            if (dict.TryGetValue("magicno", out var magicnoValue))
            {
                obj.magicno = PduRuntime.ConvertValue<uint>(magicnoValue);
            }
            if (dict.TryGetValue("version", out var versionValue))
            {
                obj.version = PduRuntime.ConvertValue<ushort>(versionValue);
            }
            if (dict.TryGetValue("flags", out var flagsValue))
            {
                obj.flags = PduRuntime.ConvertValue<ushort>(flagsValue);
            }
            if (dict.TryGetValue("meta_request_type", out var meta_request_typeValue))
            {
                obj.meta_request_type = PduRuntime.ConvertValue<uint>(meta_request_typeValue);
            }
            if (dict.TryGetValue("hako_time_us", out var hako_time_usValue))
            {
                obj.hako_time_us = PduRuntime.ConvertValue<ulong>(hako_time_usValue);
            }
            if (dict.TryGetValue("asset_time_us", out var asset_time_usValue))
            {
                obj.asset_time_us = PduRuntime.ConvertValue<ulong>(asset_time_usValue);
            }
            if (dict.TryGetValue("real_time_us", out var real_time_usValue))
            {
                obj.real_time_us = PduRuntime.ConvertValue<ulong>(real_time_usValue);
            }
            if (dict.TryGetValue("robot_name", out var robot_nameValue))
            {
                obj.robot_name = PduRuntime.ConvertValue<string>(robot_nameValue);
            }
            if (dict.TryGetValue("channel_id", out var channel_idValue))
            {
                obj.channel_id = PduRuntime.ConvertValue<int>(channel_idValue);
            }
            if (dict.TryGetValue("body_len", out var body_lenValue))
            {
                obj.body_len = PduRuntime.ConvertValue<uint>(body_lenValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static MetaPdu FromJson(string json)
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
