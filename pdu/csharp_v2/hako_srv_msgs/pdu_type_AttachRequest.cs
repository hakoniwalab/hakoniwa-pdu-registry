using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class AttachRequest
    {
        public string asset_name { get; set; } = string.Empty;
        public ulong delta_asset_tick { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["asset_name"] = ToSerializableValue(asset_name);
            dict["delta_asset_tick"] = ToSerializableValue(delta_asset_tick);
            return dict;
        }

        public static AttachRequest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new AttachRequest();
            if (dict.TryGetValue("asset_name", out var asset_nameValue))
            {
                obj.asset_name = PduRuntime.ConvertValue<string>(asset_nameValue);
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

        public static AttachRequest FromJson(string json)
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
