using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_action_msgs
{
    public class ActionRequestHeader
    {
        public byte version { get; set; } = 0;
        public byte request_kind { get; set; } = 0;
        public List<byte> reserved { get; set; } = new List<byte>();
        public List<byte> goal_id { get; set; } = new List<byte>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["version"] = ToSerializableValue(version);
            dict["request_kind"] = ToSerializableValue(request_kind);
            dict["reserved"] = ToSerializableValue(reserved);
            dict["goal_id"] = ToSerializableValue(goal_id);
            return dict;
        }

        public static ActionRequestHeader FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new ActionRequestHeader();
            if (dict.TryGetValue("version", out var versionValue))
            {
                obj.version = PduRuntime.ConvertValue<byte>(versionValue);
            }
            if (dict.TryGetValue("request_kind", out var request_kindValue))
            {
                obj.request_kind = PduRuntime.ConvertValue<byte>(request_kindValue);
            }
            if (dict.TryGetValue("reserved", out var reservedValue))
            {
                obj.reserved = PduRuntime.ConvertList<byte>(reservedValue);
            }
            if (dict.TryGetValue("goal_id", out var goal_idValue))
            {
                obj.goal_id = PduRuntime.ConvertList<byte>(goal_idValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static ActionRequestHeader FromJson(string json)
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
