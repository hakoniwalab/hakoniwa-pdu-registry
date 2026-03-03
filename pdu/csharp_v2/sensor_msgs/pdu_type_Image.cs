using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class Image
    {
        public Header header { get; set; } = new Header();
        public uint height { get; set; } = 0;
        public uint width { get; set; } = 0;
        public string encoding { get; set; } = string.Empty;
        public byte is_bigendian { get; set; } = 0;
        public uint step { get; set; } = 0;
        public List<byte> data { get; set; } = new List<byte>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["height"] = ToSerializableValue(height);
            dict["width"] = ToSerializableValue(width);
            dict["encoding"] = ToSerializableValue(encoding);
            dict["is_bigendian"] = ToSerializableValue(is_bigendian);
            dict["step"] = ToSerializableValue(step);
            dict["data"] = ToSerializableValue(data);
            return dict;
        }

        public static Image FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Image();
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
            if (dict.TryGetValue("encoding", out var encodingValue))
            {
                obj.encoding = PduRuntime.ConvertValue<string>(encodingValue);
            }
            if (dict.TryGetValue("is_bigendian", out var is_bigendianValue))
            {
                obj.is_bigendian = PduRuntime.ConvertValue<byte>(is_bigendianValue);
            }
            if (dict.TryGetValue("step", out var stepValue))
            {
                obj.step = PduRuntime.ConvertValue<uint>(stepValue);
            }
            if (dict.TryGetValue("data", out var dataValue))
            {
                obj.data = PduRuntime.ConvertList<byte>(dataValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Image FromJson(string json)
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
