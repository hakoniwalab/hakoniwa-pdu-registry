using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class PointCloud2
    {
        public Header header { get; set; } = new Header();
        public uint height { get; set; } = 0;
        public uint width { get; set; } = 0;
        public List<PointField> fields { get; set; } = new List<PointField>();
        public bool is_bigendian { get; set; } = false;
        public uint point_step { get; set; } = 0;
        public uint row_step { get; set; } = 0;
        public List<byte> data { get; set; } = new List<byte>();
        public bool is_dense { get; set; } = false;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["height"] = ToSerializableValue(height);
            dict["width"] = ToSerializableValue(width);
            dict["fields"] = ToSerializableValue(fields);
            dict["is_bigendian"] = ToSerializableValue(is_bigendian);
            dict["point_step"] = ToSerializableValue(point_step);
            dict["row_step"] = ToSerializableValue(row_step);
            dict["data"] = ToSerializableValue(data);
            dict["is_dense"] = ToSerializableValue(is_dense);
            return dict;
        }

        public static PointCloud2 FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new PointCloud2();
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
            if (dict.TryGetValue("fields", out var fieldsValue))
            {
                obj.fields = PduRuntime.ConvertObjectList<PointField>(fieldsValue, item => PointField.FromDictionary(item));
            }
            if (dict.TryGetValue("is_bigendian", out var is_bigendianValue))
            {
                obj.is_bigendian = PduRuntime.ConvertValue<bool>(is_bigendianValue);
            }
            if (dict.TryGetValue("point_step", out var point_stepValue))
            {
                obj.point_step = PduRuntime.ConvertValue<uint>(point_stepValue);
            }
            if (dict.TryGetValue("row_step", out var row_stepValue))
            {
                obj.row_step = PduRuntime.ConvertValue<uint>(row_stepValue);
            }
            if (dict.TryGetValue("data", out var dataValue))
            {
                obj.data = PduRuntime.ConvertList<byte>(dataValue);
            }
            if (dict.TryGetValue("is_dense", out var is_denseValue))
            {
                obj.is_dense = PduRuntime.ConvertValue<bool>(is_denseValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static PointCloud2 FromJson(string json)
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
