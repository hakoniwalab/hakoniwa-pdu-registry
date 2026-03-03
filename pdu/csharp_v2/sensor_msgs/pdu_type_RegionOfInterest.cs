using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class RegionOfInterest
    {
        public uint x_offset { get; set; } = 0;
        public uint y_offset { get; set; } = 0;
        public uint height { get; set; } = 0;
        public uint width { get; set; } = 0;
        public bool do_rectify { get; set; } = false;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["x_offset"] = ToSerializableValue(x_offset);
            dict["y_offset"] = ToSerializableValue(y_offset);
            dict["height"] = ToSerializableValue(height);
            dict["width"] = ToSerializableValue(width);
            dict["do_rectify"] = ToSerializableValue(do_rectify);
            return dict;
        }

        public static RegionOfInterest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new RegionOfInterest();
            if (dict.TryGetValue("x_offset", out var x_offsetValue))
            {
                obj.x_offset = PduRuntime.ConvertValue<uint>(x_offsetValue);
            }
            if (dict.TryGetValue("y_offset", out var y_offsetValue))
            {
                obj.y_offset = PduRuntime.ConvertValue<uint>(y_offsetValue);
            }
            if (dict.TryGetValue("height", out var heightValue))
            {
                obj.height = PduRuntime.ConvertValue<uint>(heightValue);
            }
            if (dict.TryGetValue("width", out var widthValue))
            {
                obj.width = PduRuntime.ConvertValue<uint>(widthValue);
            }
            if (dict.TryGetValue("do_rectify", out var do_rectifyValue))
            {
                obj.do_rectify = PduRuntime.ConvertValue<bool>(do_rectifyValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static RegionOfInterest FromJson(string json)
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
