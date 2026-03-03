using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.ev3_msgs
{
    public class Ev3PduSensorHeader
    {
        public string name { get; set; } = string.Empty;
        public uint version { get; set; } = 0;
        public long hakoniwa_time { get; set; } = 0;
        public uint ext_off { get; set; } = 0;
        public uint ext_size { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["name"] = ToSerializableValue(name);
            dict["version"] = ToSerializableValue(version);
            dict["hakoniwa_time"] = ToSerializableValue(hakoniwa_time);
            dict["ext_off"] = ToSerializableValue(ext_off);
            dict["ext_size"] = ToSerializableValue(ext_size);
            return dict;
        }

        public static Ev3PduSensorHeader FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Ev3PduSensorHeader();
            if (dict.TryGetValue("name", out var nameValue))
            {
                obj.name = PduRuntime.ConvertValue<string>(nameValue);
            }
            if (dict.TryGetValue("version", out var versionValue))
            {
                obj.version = PduRuntime.ConvertValue<uint>(versionValue);
            }
            if (dict.TryGetValue("hakoniwa_time", out var hakoniwa_timeValue))
            {
                obj.hakoniwa_time = PduRuntime.ConvertValue<long>(hakoniwa_timeValue);
            }
            if (dict.TryGetValue("ext_off", out var ext_offValue))
            {
                obj.ext_off = PduRuntime.ConvertValue<uint>(ext_offValue);
            }
            if (dict.TryGetValue("ext_size", out var ext_sizeValue))
            {
                obj.ext_size = PduRuntime.ConvertValue<uint>(ext_sizeValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Ev3PduSensorHeader FromJson(string json)
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
