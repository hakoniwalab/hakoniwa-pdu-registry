using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class ManualPosAttControl
    {
        public bool do_operation { get; set; } = false;
        public Twist posatt { get; set; } = new Twist();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["do_operation"] = ToSerializableValue(do_operation);
            dict["posatt"] = ToSerializableValue(posatt);
            return dict;
        }

        public static ManualPosAttControl FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new ManualPosAttControl();
            if (dict.TryGetValue("do_operation", out var do_operationValue))
            {
                obj.do_operation = PduRuntime.ConvertValue<bool>(do_operationValue);
            }
            if (dict.TryGetValue("posatt", out var posattValue))
            {
                obj.posatt = PduRuntime.ConvertObject<Twist>(posattValue, item => Twist.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static ManualPosAttControl FromJson(string json)
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
