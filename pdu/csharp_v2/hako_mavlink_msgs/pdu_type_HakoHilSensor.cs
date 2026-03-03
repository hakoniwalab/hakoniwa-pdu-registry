using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public class HakoHilSensor
    {
        public ulong time_usec { get; set; } = 0;
        public float xacc { get; set; } = 0.0F;
        public float yacc { get; set; } = 0.0F;
        public float zacc { get; set; } = 0.0F;
        public float xgyro { get; set; } = 0.0F;
        public float ygyro { get; set; } = 0.0F;
        public float zgyro { get; set; } = 0.0F;
        public float xmag { get; set; } = 0.0F;
        public float ymag { get; set; } = 0.0F;
        public float zmag { get; set; } = 0.0F;
        public float abs_pressure { get; set; } = 0.0F;
        public float diff_pressure { get; set; } = 0.0F;
        public float pressure_alt { get; set; } = 0.0F;
        public float temperature { get; set; } = 0.0F;
        public uint fields_updated { get; set; } = 0;
        public byte id { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["time_usec"] = ToSerializableValue(time_usec);
            dict["xacc"] = ToSerializableValue(xacc);
            dict["yacc"] = ToSerializableValue(yacc);
            dict["zacc"] = ToSerializableValue(zacc);
            dict["xgyro"] = ToSerializableValue(xgyro);
            dict["ygyro"] = ToSerializableValue(ygyro);
            dict["zgyro"] = ToSerializableValue(zgyro);
            dict["xmag"] = ToSerializableValue(xmag);
            dict["ymag"] = ToSerializableValue(ymag);
            dict["zmag"] = ToSerializableValue(zmag);
            dict["abs_pressure"] = ToSerializableValue(abs_pressure);
            dict["diff_pressure"] = ToSerializableValue(diff_pressure);
            dict["pressure_alt"] = ToSerializableValue(pressure_alt);
            dict["temperature"] = ToSerializableValue(temperature);
            dict["fields_updated"] = ToSerializableValue(fields_updated);
            dict["id"] = ToSerializableValue(id);
            return dict;
        }

        public static HakoHilSensor FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new HakoHilSensor();
            if (dict.TryGetValue("time_usec", out var time_usecValue))
            {
                obj.time_usec = PduRuntime.ConvertValue<ulong>(time_usecValue);
            }
            if (dict.TryGetValue("xacc", out var xaccValue))
            {
                obj.xacc = PduRuntime.ConvertValue<float>(xaccValue);
            }
            if (dict.TryGetValue("yacc", out var yaccValue))
            {
                obj.yacc = PduRuntime.ConvertValue<float>(yaccValue);
            }
            if (dict.TryGetValue("zacc", out var zaccValue))
            {
                obj.zacc = PduRuntime.ConvertValue<float>(zaccValue);
            }
            if (dict.TryGetValue("xgyro", out var xgyroValue))
            {
                obj.xgyro = PduRuntime.ConvertValue<float>(xgyroValue);
            }
            if (dict.TryGetValue("ygyro", out var ygyroValue))
            {
                obj.ygyro = PduRuntime.ConvertValue<float>(ygyroValue);
            }
            if (dict.TryGetValue("zgyro", out var zgyroValue))
            {
                obj.zgyro = PduRuntime.ConvertValue<float>(zgyroValue);
            }
            if (dict.TryGetValue("xmag", out var xmagValue))
            {
                obj.xmag = PduRuntime.ConvertValue<float>(xmagValue);
            }
            if (dict.TryGetValue("ymag", out var ymagValue))
            {
                obj.ymag = PduRuntime.ConvertValue<float>(ymagValue);
            }
            if (dict.TryGetValue("zmag", out var zmagValue))
            {
                obj.zmag = PduRuntime.ConvertValue<float>(zmagValue);
            }
            if (dict.TryGetValue("abs_pressure", out var abs_pressureValue))
            {
                obj.abs_pressure = PduRuntime.ConvertValue<float>(abs_pressureValue);
            }
            if (dict.TryGetValue("diff_pressure", out var diff_pressureValue))
            {
                obj.diff_pressure = PduRuntime.ConvertValue<float>(diff_pressureValue);
            }
            if (dict.TryGetValue("pressure_alt", out var pressure_altValue))
            {
                obj.pressure_alt = PduRuntime.ConvertValue<float>(pressure_altValue);
            }
            if (dict.TryGetValue("temperature", out var temperatureValue))
            {
                obj.temperature = PduRuntime.ConvertValue<float>(temperatureValue);
            }
            if (dict.TryGetValue("fields_updated", out var fields_updatedValue))
            {
                obj.fields_updated = PduRuntime.ConvertValue<uint>(fields_updatedValue);
            }
            if (dict.TryGetValue("id", out var idValue))
            {
                obj.id = PduRuntime.ConvertValue<byte>(idValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static HakoHilSensor FromJson(string json)
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
