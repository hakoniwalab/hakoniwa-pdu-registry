using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.can_msgs
{
    public class HakoCanHead
    {
        public uint channel { get; set; } = 0;
        public uint ide { get; set; } = 0;
        public uint rtr { get; set; } = 0;
        public uint dlc { get; set; } = 0;
        public uint canid { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["channel"] = ToSerializableValue(channel);
            dict["ide"] = ToSerializableValue(ide);
            dict["rtr"] = ToSerializableValue(rtr);
            dict["dlc"] = ToSerializableValue(dlc);
            dict["canid"] = ToSerializableValue(canid);
            return dict;
        }

        public static HakoCanHead FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoCanHead();
            if (dict.TryGetValue("channel", out var channelValue))
            {
                obj.channel = PduRuntime.ConvertValue<uint>(channelValue);
            }
            if (dict.TryGetValue("ide", out var ideValue))
            {
                obj.ide = PduRuntime.ConvertValue<uint>(ideValue);
            }
            if (dict.TryGetValue("rtr", out var rtrValue))
            {
                obj.rtr = PduRuntime.ConvertValue<uint>(rtrValue);
            }
            if (dict.TryGetValue("dlc", out var dlcValue))
            {
                obj.dlc = PduRuntime.ConvertValue<uint>(dlcValue);
            }
            if (dict.TryGetValue("canid", out var canidValue))
            {
                obj.canid = PduRuntime.ConvertValue<uint>(canidValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoCanHead FromJson(string json)
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
