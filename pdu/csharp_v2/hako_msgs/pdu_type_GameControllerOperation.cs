using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class GameControllerOperation
    {
        public List<double> axis { get; set; } = new List<double>();
        public List<bool> button { get; set; } = new List<bool>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["axis"] = ToSerializableValue(axis);
            dict["button"] = ToSerializableValue(button);
            return dict;
        }

        public static GameControllerOperation FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new GameControllerOperation();
            if (dict.TryGetValue("axis", out var axisValue))
            {
                obj.axis = PduRuntime.ConvertList<double>(axisValue);
            }
            if (dict.TryGetValue("button", out var buttonValue))
            {
                obj.button = PduRuntime.ConvertList<bool>(buttonValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static GameControllerOperation FromJson(string json)
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
