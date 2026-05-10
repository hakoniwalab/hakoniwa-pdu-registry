using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.nav_msgs
{
    public class GridCells
    {
        public Header header { get; set; } = new Header();
        public float cell_width { get; set; } = 0.0F;
        public float cell_height { get; set; } = 0.0F;
        public List<Point> cells { get; set; } = new List<Point>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["cell_width"] = ToSerializableValue(cell_width);
            dict["cell_height"] = ToSerializableValue(cell_height);
            dict["cells"] = ToSerializableValue(cells);
            return dict;
        }

        public static GridCells FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new GridCells();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("cell_width", out var cell_widthValue))
            {
                obj.cell_width = PduRuntime.ConvertValue<float>(cell_widthValue);
            }
            if (dict.TryGetValue("cell_height", out var cell_heightValue))
            {
                obj.cell_height = PduRuntime.ConvertValue<float>(cell_heightValue);
            }
            if (dict.TryGetValue("cells", out var cellsValue))
            {
                obj.cells = PduRuntime.ConvertObjectList<Point>(cellsValue, item => Point.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static GridCells FromJson(string json)
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
