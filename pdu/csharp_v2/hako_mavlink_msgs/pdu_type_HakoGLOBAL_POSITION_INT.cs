using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public class HakoGLOBAL_POSITION_INT
    {
        public uint time_boot_ms { get; set; } = 0;
        public int lat { get; set; } = 0;
        public int lon { get; set; } = 0;
        public int alt { get; set; } = 0;
        public int relative_alt { get; set; } = 0;
        public short vx { get; set; } = 0;
        public short vy { get; set; } = 0;
        public short vz { get; set; } = 0;
        public ushort hdg { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["time_boot_ms"] = ToSerializableValue(time_boot_ms);
            dict["lat"] = ToSerializableValue(lat);
            dict["lon"] = ToSerializableValue(lon);
            dict["alt"] = ToSerializableValue(alt);
            dict["relative_alt"] = ToSerializableValue(relative_alt);
            dict["vx"] = ToSerializableValue(vx);
            dict["vy"] = ToSerializableValue(vy);
            dict["vz"] = ToSerializableValue(vz);
            dict["hdg"] = ToSerializableValue(hdg);
            return dict;
        }

        public static HakoGLOBAL_POSITION_INT FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoGLOBAL_POSITION_INT();
            if (dict.TryGetValue("time_boot_ms", out var time_boot_msValue))
            {
                obj.time_boot_ms = PduRuntime.ConvertValue<uint>(time_boot_msValue);
            }
            if (dict.TryGetValue("lat", out var latValue))
            {
                obj.lat = PduRuntime.ConvertValue<int>(latValue);
            }
            if (dict.TryGetValue("lon", out var lonValue))
            {
                obj.lon = PduRuntime.ConvertValue<int>(lonValue);
            }
            if (dict.TryGetValue("alt", out var altValue))
            {
                obj.alt = PduRuntime.ConvertValue<int>(altValue);
            }
            if (dict.TryGetValue("relative_alt", out var relative_altValue))
            {
                obj.relative_alt = PduRuntime.ConvertValue<int>(relative_altValue);
            }
            if (dict.TryGetValue("vx", out var vxValue))
            {
                obj.vx = PduRuntime.ConvertValue<short>(vxValue);
            }
            if (dict.TryGetValue("vy", out var vyValue))
            {
                obj.vy = PduRuntime.ConvertValue<short>(vyValue);
            }
            if (dict.TryGetValue("vz", out var vzValue))
            {
                obj.vz = PduRuntime.ConvertValue<short>(vzValue);
            }
            if (dict.TryGetValue("hdg", out var hdgValue))
            {
                obj.hdg = PduRuntime.ConvertValue<ushort>(hdgValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoGLOBAL_POSITION_INT FromJson(string json)
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
