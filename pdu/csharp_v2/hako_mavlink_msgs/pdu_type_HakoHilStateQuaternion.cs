using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public class HakoHilStateQuaternion
    {
        public ulong time_usec { get; set; } = 0;
        public List<float> attitude_quaternion { get; set; } = new List<float>();
        public float rollspeed { get; set; } = 0.0F;
        public float pitchspeed { get; set; } = 0.0F;
        public float yawspeed { get; set; } = 0.0F;
        public int lat { get; set; } = 0;
        public int lon { get; set; } = 0;
        public int alt { get; set; } = 0;
        public short vx { get; set; } = 0;
        public short vy { get; set; } = 0;
        public short vz { get; set; } = 0;
        public ushort ind_airspeed { get; set; } = 0;
        public ushort true_airspeed { get; set; } = 0;
        public short xacc { get; set; } = 0;
        public short yacc { get; set; } = 0;
        public short zacc { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["time_usec"] = ToSerializableValue(time_usec);
            dict["attitude_quaternion"] = ToSerializableValue(attitude_quaternion);
            dict["rollspeed"] = ToSerializableValue(rollspeed);
            dict["pitchspeed"] = ToSerializableValue(pitchspeed);
            dict["yawspeed"] = ToSerializableValue(yawspeed);
            dict["lat"] = ToSerializableValue(lat);
            dict["lon"] = ToSerializableValue(lon);
            dict["alt"] = ToSerializableValue(alt);
            dict["vx"] = ToSerializableValue(vx);
            dict["vy"] = ToSerializableValue(vy);
            dict["vz"] = ToSerializableValue(vz);
            dict["ind_airspeed"] = ToSerializableValue(ind_airspeed);
            dict["true_airspeed"] = ToSerializableValue(true_airspeed);
            dict["xacc"] = ToSerializableValue(xacc);
            dict["yacc"] = ToSerializableValue(yacc);
            dict["zacc"] = ToSerializableValue(zacc);
            return dict;
        }

        public static HakoHilStateQuaternion FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoHilStateQuaternion();
            if (dict.TryGetValue("time_usec", out var time_usecValue))
            {
                obj.time_usec = PduRuntime.ConvertValue<ulong>(time_usecValue);
            }
            if (dict.TryGetValue("attitude_quaternion", out var attitude_quaternionValue))
            {
                obj.attitude_quaternion = PduRuntime.ConvertList<float>(attitude_quaternionValue);
            }
            if (dict.TryGetValue("rollspeed", out var rollspeedValue))
            {
                obj.rollspeed = PduRuntime.ConvertValue<float>(rollspeedValue);
            }
            if (dict.TryGetValue("pitchspeed", out var pitchspeedValue))
            {
                obj.pitchspeed = PduRuntime.ConvertValue<float>(pitchspeedValue);
            }
            if (dict.TryGetValue("yawspeed", out var yawspeedValue))
            {
                obj.yawspeed = PduRuntime.ConvertValue<float>(yawspeedValue);
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
            if (dict.TryGetValue("ind_airspeed", out var ind_airspeedValue))
            {
                obj.ind_airspeed = PduRuntime.ConvertValue<ushort>(ind_airspeedValue);
            }
            if (dict.TryGetValue("true_airspeed", out var true_airspeedValue))
            {
                obj.true_airspeed = PduRuntime.ConvertValue<ushort>(true_airspeedValue);
            }
            if (dict.TryGetValue("xacc", out var xaccValue))
            {
                obj.xacc = PduRuntime.ConvertValue<short>(xaccValue);
            }
            if (dict.TryGetValue("yacc", out var yaccValue))
            {
                obj.yacc = PduRuntime.ConvertValue<short>(yaccValue);
            }
            if (dict.TryGetValue("zacc", out var zaccValue))
            {
                obj.zacc = PduRuntime.ConvertValue<short>(zaccValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoHilStateQuaternion FromJson(string json)
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
