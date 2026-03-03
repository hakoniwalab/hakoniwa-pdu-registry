using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public class HakoHeartbeat
    {
        public byte type { get; set; } = 0;
        public byte autopilot { get; set; } = 0;
        public byte base_mode { get; set; } = 0;
        public uint custom_mode { get; set; } = 0;
        public byte system_status { get; set; } = 0;
        public byte mavlink_version { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["type"] = ToSerializableValue(type);
            dict["autopilot"] = ToSerializableValue(autopilot);
            dict["base_mode"] = ToSerializableValue(base_mode);
            dict["custom_mode"] = ToSerializableValue(custom_mode);
            dict["system_status"] = ToSerializableValue(system_status);
            dict["mavlink_version"] = ToSerializableValue(mavlink_version);
            return dict;
        }

        public static HakoHeartbeat FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoHeartbeat();
            if (dict.TryGetValue("type", out var typeValue))
            {
                obj.type = PduRuntime.ConvertValue<byte>(typeValue);
            }
            if (dict.TryGetValue("autopilot", out var autopilotValue))
            {
                obj.autopilot = PduRuntime.ConvertValue<byte>(autopilotValue);
            }
            if (dict.TryGetValue("base_mode", out var base_modeValue))
            {
                obj.base_mode = PduRuntime.ConvertValue<byte>(base_modeValue);
            }
            if (dict.TryGetValue("custom_mode", out var custom_modeValue))
            {
                obj.custom_mode = PduRuntime.ConvertValue<uint>(custom_modeValue);
            }
            if (dict.TryGetValue("system_status", out var system_statusValue))
            {
                obj.system_status = PduRuntime.ConvertValue<byte>(system_statusValue);
            }
            if (dict.TryGetValue("mavlink_version", out var mavlink_versionValue))
            {
                obj.mavlink_version = PduRuntime.ConvertValue<byte>(mavlink_versionValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoHeartbeat FromJson(string json)
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
