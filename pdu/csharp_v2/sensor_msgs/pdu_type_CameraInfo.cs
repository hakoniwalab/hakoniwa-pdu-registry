using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class CameraInfo
    {
        public Header header { get; set; } = new Header();
        public uint height { get; set; } = 0;
        public uint width { get; set; } = 0;
        public string distortion_model { get; set; } = string.Empty;
        public List<double> d { get; set; } = new List<double>();
        public List<double> k { get; set; } = new List<double>();
        public List<double> r { get; set; } = new List<double>();
        public List<double> p { get; set; } = new List<double>();
        public uint binning_x { get; set; } = 0;
        public uint binning_y { get; set; } = 0;
        public RegionOfInterest roi { get; set; } = new RegionOfInterest();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["height"] = ToSerializableValue(height);
            dict["width"] = ToSerializableValue(width);
            dict["distortion_model"] = ToSerializableValue(distortion_model);
            dict["d"] = ToSerializableValue(d);
            dict["k"] = ToSerializableValue(k);
            dict["r"] = ToSerializableValue(r);
            dict["p"] = ToSerializableValue(p);
            dict["binning_x"] = ToSerializableValue(binning_x);
            dict["binning_y"] = ToSerializableValue(binning_y);
            dict["roi"] = ToSerializableValue(roi);
            return dict;
        }

        public static CameraInfo FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new CameraInfo();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("height", out var heightValue))
            {
                obj.height = PduRuntime.ConvertValue<uint>(heightValue);
            }
            if (dict.TryGetValue("width", out var widthValue))
            {
                obj.width = PduRuntime.ConvertValue<uint>(widthValue);
            }
            if (dict.TryGetValue("distortion_model", out var distortion_modelValue))
            {
                obj.distortion_model = PduRuntime.ConvertValue<string>(distortion_modelValue);
            }
            if (dict.TryGetValue("d", out var dValue))
            {
                obj.d = PduRuntime.ConvertList<double>(dValue);
            }
            if (dict.TryGetValue("k", out var kValue))
            {
                obj.k = PduRuntime.ConvertList<double>(kValue);
            }
            if (dict.TryGetValue("r", out var rValue))
            {
                obj.r = PduRuntime.ConvertList<double>(rValue);
            }
            if (dict.TryGetValue("p", out var pValue))
            {
                obj.p = PduRuntime.ConvertList<double>(pValue);
            }
            if (dict.TryGetValue("binning_x", out var binning_xValue))
            {
                obj.binning_x = PduRuntime.ConvertValue<uint>(binning_xValue);
            }
            if (dict.TryGetValue("binning_y", out var binning_yValue))
            {
                obj.binning_y = PduRuntime.ConvertValue<uint>(binning_yValue);
            }
            if (dict.TryGetValue("roi", out var roiValue))
            {
                obj.roi = PduRuntime.ConvertObject<RegionOfInterest>(roiValue, item => RegionOfInterest.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static CameraInfo FromJson(string json)
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
