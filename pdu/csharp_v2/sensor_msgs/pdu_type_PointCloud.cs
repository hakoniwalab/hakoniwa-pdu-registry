using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class PointCloud
    {
        public Header header { get; set; } = new Header();
        public List<Point32> points { get; set; } = new List<Point32>();
        public List<ChannelFloat32> channels { get; set; } = new List<ChannelFloat32>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["points"] = ToSerializableValue(points);
            dict["channels"] = ToSerializableValue(channels);
            return dict;
        }

        public static PointCloud FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new PointCloud();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("points", out var pointsValue))
            {
                obj.points = PduRuntime.ConvertObjectList<Point32>(pointsValue, item => Point32.FromDictionary(item));
            }
            if (dict.TryGetValue("channels", out var channelsValue))
            {
                obj.channels = PduRuntime.ConvertObjectList<ChannelFloat32>(channelsValue, item => ChannelFloat32.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static PointCloud FromJson(string json)
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
