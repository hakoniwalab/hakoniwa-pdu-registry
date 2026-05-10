using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.nav_msgs
{
    public class MapMetaData
    {
        public Time map_load_time { get; set; } = new Time();
        public float resolution { get; set; } = 0.0F;
        public uint width { get; set; } = 0;
        public uint height { get; set; } = 0;
        public Pose origin { get; set; } = new Pose();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["map_load_time"] = ToSerializableValue(map_load_time);
            dict["resolution"] = ToSerializableValue(resolution);
            dict["width"] = ToSerializableValue(width);
            dict["height"] = ToSerializableValue(height);
            dict["origin"] = ToSerializableValue(origin);
            return dict;
        }

        public static MapMetaData FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new MapMetaData();
            if (dict.TryGetValue("map_load_time", out var map_load_timeValue))
            {
                obj.map_load_time = PduRuntime.ConvertObject<Time>(map_load_timeValue, item => Time.FromDictionary(item));
            }
            if (dict.TryGetValue("resolution", out var resolutionValue))
            {
                obj.resolution = PduRuntime.ConvertValue<float>(resolutionValue);
            }
            if (dict.TryGetValue("width", out var widthValue))
            {
                obj.width = PduRuntime.ConvertValue<uint>(widthValue);
            }
            if (dict.TryGetValue("height", out var heightValue))
            {
                obj.height = PduRuntime.ConvertValue<uint>(heightValue);
            }
            if (dict.TryGetValue("origin", out var originValue))
            {
                obj.origin = PduRuntime.ConvertObject<Pose>(originValue, item => Pose.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static MapMetaData FromJson(string json)
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
