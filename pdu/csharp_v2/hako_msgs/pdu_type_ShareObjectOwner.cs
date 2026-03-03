using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class ShareObjectOwner
    {
        public string object_name { get; set; } = string.Empty;
        public uint owner_id { get; set; } = 0;
        public ulong last_update { get; set; } = 0;
        public Twist pos { get; set; } = new Twist();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["object_name"] = ToSerializableValue(object_name);
            dict["owner_id"] = ToSerializableValue(owner_id);
            dict["last_update"] = ToSerializableValue(last_update);
            dict["pos"] = ToSerializableValue(pos);
            return dict;
        }

        public static ShareObjectOwner FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new ShareObjectOwner();
            if (dict.TryGetValue("object_name", out var object_nameValue))
            {
                obj.object_name = PduRuntime.ConvertValue<string>(object_nameValue);
            }
            if (dict.TryGetValue("owner_id", out var owner_idValue))
            {
                obj.owner_id = PduRuntime.ConvertValue<uint>(owner_idValue);
            }
            if (dict.TryGetValue("last_update", out var last_updateValue))
            {
                obj.last_update = PduRuntime.ConvertValue<ulong>(last_updateValue);
            }
            if (dict.TryGetValue("pos", out var posValue))
            {
                obj.pos = PduRuntime.ConvertObject<Twist>(posValue, item => Twist.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static ShareObjectOwner FromJson(string json)
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
