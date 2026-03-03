using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class ExecutionUnitRuntimeStatus
    {
        public uint config_hash { get; set; } = 0;
        public ushort unit_count { get; set; } = 0;
        public List<byte> status { get; set; } = new List<byte>();
        public List<byte> epoch { get; set; } = new List<byte>();
        public List<byte> curr_owner_node_id { get; set; } = new List<byte>();
        public List<byte> next_owner_node_id { get; set; } = new List<byte>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["config_hash"] = ToSerializableValue(config_hash);
            dict["unit_count"] = ToSerializableValue(unit_count);
            dict["status"] = ToSerializableValue(status);
            dict["epoch"] = ToSerializableValue(epoch);
            dict["curr_owner_node_id"] = ToSerializableValue(curr_owner_node_id);
            dict["next_owner_node_id"] = ToSerializableValue(next_owner_node_id);
            return dict;
        }

        public static ExecutionUnitRuntimeStatus FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new ExecutionUnitRuntimeStatus();
            if (dict.TryGetValue("config_hash", out var config_hashValue))
            {
                obj.config_hash = PduRuntime.ConvertValue<uint>(config_hashValue);
            }
            if (dict.TryGetValue("unit_count", out var unit_countValue))
            {
                obj.unit_count = PduRuntime.ConvertValue<ushort>(unit_countValue);
            }
            if (dict.TryGetValue("status", out var statusValue))
            {
                obj.status = PduRuntime.ConvertList<byte>(statusValue);
            }
            if (dict.TryGetValue("epoch", out var epochValue))
            {
                obj.epoch = PduRuntime.ConvertList<byte>(epochValue);
            }
            if (dict.TryGetValue("curr_owner_node_id", out var curr_owner_node_idValue))
            {
                obj.curr_owner_node_id = PduRuntime.ConvertList<byte>(curr_owner_node_idValue);
            }
            if (dict.TryGetValue("next_owner_node_id", out var next_owner_node_idValue))
            {
                obj.next_owner_node_id = PduRuntime.ConvertList<byte>(next_owner_node_idValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static ExecutionUnitRuntimeStatus FromJson(string json)
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
