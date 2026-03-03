using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class SimpleStructVarray
    {
        public int aaa { get; set; } = 0;
        public List<string> fixed_str { get; set; } = new List<string>();
        public List<string> varray_str { get; set; } = new List<string>();
        public List<SimpleVarray> fixed_array { get; set; } = new List<SimpleVarray>();
        public List<SimpleVarray> data { get; set; } = new List<SimpleVarray>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["aaa"] = ToSerializableValue(aaa);
            dict["fixed_str"] = ToSerializableValue(fixed_str);
            dict["varray_str"] = ToSerializableValue(varray_str);
            dict["fixed_array"] = ToSerializableValue(fixed_array);
            dict["data"] = ToSerializableValue(data);
            return dict;
        }

        public static SimpleStructVarray FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new SimpleStructVarray();
            if (dict.TryGetValue("aaa", out var aaaValue))
            {
                obj.aaa = PduRuntime.ConvertValue<int>(aaaValue);
            }
            if (dict.TryGetValue("fixed_str", out var fixed_strValue))
            {
                obj.fixed_str = PduRuntime.ConvertList<string>(fixed_strValue);
            }
            if (dict.TryGetValue("varray_str", out var varray_strValue))
            {
                obj.varray_str = PduRuntime.ConvertList<string>(varray_strValue);
            }
            if (dict.TryGetValue("fixed_array", out var fixed_arrayValue))
            {
                obj.fixed_array = PduRuntime.ConvertObjectList<SimpleVarray>(fixed_arrayValue, item => SimpleVarray.FromDictionary(item));
            }
            if (dict.TryGetValue("data", out var dataValue))
            {
                obj.data = PduRuntime.ConvertObjectList<SimpleVarray>(dataValue, item => SimpleVarray.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static SimpleStructVarray FromJson(string json)
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
