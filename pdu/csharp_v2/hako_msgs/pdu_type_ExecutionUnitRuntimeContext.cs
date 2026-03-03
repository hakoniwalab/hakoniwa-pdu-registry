using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class ExecutionUnitRuntimeContext
    {
        public uint config_hash { get; set; } = 0;
        public byte epoch { get; set; } = 0;
        public byte owner_id { get; set; } = 0;
        public List<byte> context { get; set; } = new List<byte>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["config_hash"] = ToSerializableValue(config_hash);
            dict["epoch"] = ToSerializableValue(epoch);
            dict["owner_id"] = ToSerializableValue(owner_id);
            dict["context"] = ToSerializableValue(context);
            return dict;
        }

        public static ExecutionUnitRuntimeContext FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new ExecutionUnitRuntimeContext();
            if (dict.TryGetValue("config_hash", out var config_hashValue))
            {
                obj.config_hash = PduRuntime.ConvertValue<uint>(config_hashValue);
            }
            if (dict.TryGetValue("epoch", out var epochValue))
            {
                obj.epoch = PduRuntime.ConvertValue<byte>(epochValue);
            }
            if (dict.TryGetValue("owner_id", out var owner_idValue))
            {
                obj.owner_id = PduRuntime.ConvertValue<byte>(owner_idValue);
            }
            if (dict.TryGetValue("context", out var contextValue))
            {
                obj.context = PduRuntime.ConvertList<byte>(contextValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static ExecutionUnitRuntimeContext FromJson(string json)
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
