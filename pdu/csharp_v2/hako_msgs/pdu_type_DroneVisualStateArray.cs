using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class DroneVisualStateArray
    {
        public uint sequence_id { get; set; } = 0;
        public uint chunk_index { get; set; } = 0;
        public uint chunk_count { get; set; } = 0;
        public uint start_index { get; set; } = 0;
        public uint valid_count { get; set; } = 0;
        public List<DroneVisualState> drones { get; set; } = new List<DroneVisualState>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["sequence_id"] = ToSerializableValue(sequence_id);
            dict["chunk_index"] = ToSerializableValue(chunk_index);
            dict["chunk_count"] = ToSerializableValue(chunk_count);
            dict["start_index"] = ToSerializableValue(start_index);
            dict["valid_count"] = ToSerializableValue(valid_count);
            dict["drones"] = ToSerializableValue(drones);
            return dict;
        }

        public static DroneVisualStateArray FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new DroneVisualStateArray();
            if (dict.TryGetValue("sequence_id", out var sequence_idValue))
            {
                obj.sequence_id = PduRuntime.ConvertValue<uint>(sequence_idValue);
            }
            if (dict.TryGetValue("chunk_index", out var chunk_indexValue))
            {
                obj.chunk_index = PduRuntime.ConvertValue<uint>(chunk_indexValue);
            }
            if (dict.TryGetValue("chunk_count", out var chunk_countValue))
            {
                obj.chunk_count = PduRuntime.ConvertValue<uint>(chunk_countValue);
            }
            if (dict.TryGetValue("start_index", out var start_indexValue))
            {
                obj.start_index = PduRuntime.ConvertValue<uint>(start_indexValue);
            }
            if (dict.TryGetValue("valid_count", out var valid_countValue))
            {
                obj.valid_count = PduRuntime.ConvertValue<uint>(valid_countValue);
            }
            if (dict.TryGetValue("drones", out var dronesValue))
            {
                obj.drones = PduRuntime.ConvertObjectList<DroneVisualState>(dronesValue, item => DroneVisualState.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static DroneVisualStateArray FromJson(string json)
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
