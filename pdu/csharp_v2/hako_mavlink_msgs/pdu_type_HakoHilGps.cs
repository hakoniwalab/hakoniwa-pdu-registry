using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public class HakoHilGps
    {
        public ulong time_usec { get; set; } = 0;
        public int lat { get; set; } = 0;
        public int lon { get; set; } = 0;
        public int alt { get; set; } = 0;
        public ushort eph { get; set; } = 0;
        public ushort epv { get; set; } = 0;
        public ushort vel { get; set; } = 0;
        public short vn { get; set; } = 0;
        public short ve { get; set; } = 0;
        public short vd { get; set; } = 0;
        public ushort cog { get; set; } = 0;
        public byte satellites_visible { get; set; } = 0;
        public byte id { get; set; } = 0;
        public byte yaw { get; set; } = 0;
        public byte fix_type { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["time_usec"] = ToSerializableValue(time_usec);
            dict["lat"] = ToSerializableValue(lat);
            dict["lon"] = ToSerializableValue(lon);
            dict["alt"] = ToSerializableValue(alt);
            dict["eph"] = ToSerializableValue(eph);
            dict["epv"] = ToSerializableValue(epv);
            dict["vel"] = ToSerializableValue(vel);
            dict["vn"] = ToSerializableValue(vn);
            dict["ve"] = ToSerializableValue(ve);
            dict["vd"] = ToSerializableValue(vd);
            dict["cog"] = ToSerializableValue(cog);
            dict["satellites_visible"] = ToSerializableValue(satellites_visible);
            dict["id"] = ToSerializableValue(id);
            dict["yaw"] = ToSerializableValue(yaw);
            dict["fix_type"] = ToSerializableValue(fix_type);
            return dict;
        }

        public static HakoHilGps FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoHilGps();
            if (dict.TryGetValue("time_usec", out var time_usecValue))
            {
                obj.time_usec = PduRuntime.ConvertValue<ulong>(time_usecValue);
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
            if (dict.TryGetValue("eph", out var ephValue))
            {
                obj.eph = PduRuntime.ConvertValue<ushort>(ephValue);
            }
            if (dict.TryGetValue("epv", out var epvValue))
            {
                obj.epv = PduRuntime.ConvertValue<ushort>(epvValue);
            }
            if (dict.TryGetValue("vel", out var velValue))
            {
                obj.vel = PduRuntime.ConvertValue<ushort>(velValue);
            }
            if (dict.TryGetValue("vn", out var vnValue))
            {
                obj.vn = PduRuntime.ConvertValue<short>(vnValue);
            }
            if (dict.TryGetValue("ve", out var veValue))
            {
                obj.ve = PduRuntime.ConvertValue<short>(veValue);
            }
            if (dict.TryGetValue("vd", out var vdValue))
            {
                obj.vd = PduRuntime.ConvertValue<short>(vdValue);
            }
            if (dict.TryGetValue("cog", out var cogValue))
            {
                obj.cog = PduRuntime.ConvertValue<ushort>(cogValue);
            }
            if (dict.TryGetValue("satellites_visible", out var satellites_visibleValue))
            {
                obj.satellites_visible = PduRuntime.ConvertValue<byte>(satellites_visibleValue);
            }
            if (dict.TryGetValue("id", out var idValue))
            {
                obj.id = PduRuntime.ConvertValue<byte>(idValue);
            }
            if (dict.TryGetValue("yaw", out var yawValue))
            {
                obj.yaw = PduRuntime.ConvertValue<byte>(yawValue);
            }
            if (dict.TryGetValue("fix_type", out var fix_typeValue))
            {
                obj.fix_type = PduRuntime.ConvertValue<byte>(fix_typeValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoHilGps FromJson(string json)
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
