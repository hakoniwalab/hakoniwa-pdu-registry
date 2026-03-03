using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class Disturbance
    {
        public DisturbanceTemperature d_temp { get; set; } = new DisturbanceTemperature();
        public DisturbanceWind d_wind { get; set; } = new DisturbanceWind();
        public DisturbanceAtm d_atm { get; set; } = new DisturbanceAtm();
        public DisturbanceBoundary d_boundary { get; set; } = new DisturbanceBoundary();
        public List<DisturbanceUserCustom> d_user_custom { get; set; } = new List<DisturbanceUserCustom>();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["d_temp"] = ToSerializableValue(d_temp);
            dict["d_wind"] = ToSerializableValue(d_wind);
            dict["d_atm"] = ToSerializableValue(d_atm);
            dict["d_boundary"] = ToSerializableValue(d_boundary);
            dict["d_user_custom"] = ToSerializableValue(d_user_custom);
            return dict;
        }

        public static Disturbance FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Disturbance();
            if (dict.TryGetValue("d_temp", out var d_tempValue))
            {
                obj.d_temp = PduRuntime.ConvertObject<DisturbanceTemperature>(d_tempValue, item => DisturbanceTemperature.FromDictionary(item));
            }
            if (dict.TryGetValue("d_wind", out var d_windValue))
            {
                obj.d_wind = PduRuntime.ConvertObject<DisturbanceWind>(d_windValue, item => DisturbanceWind.FromDictionary(item));
            }
            if (dict.TryGetValue("d_atm", out var d_atmValue))
            {
                obj.d_atm = PduRuntime.ConvertObject<DisturbanceAtm>(d_atmValue, item => DisturbanceAtm.FromDictionary(item));
            }
            if (dict.TryGetValue("d_boundary", out var d_boundaryValue))
            {
                obj.d_boundary = PduRuntime.ConvertObject<DisturbanceBoundary>(d_boundaryValue, item => DisturbanceBoundary.FromDictionary(item));
            }
            if (dict.TryGetValue("d_user_custom", out var d_user_customValue))
            {
                obj.d_user_custom = PduRuntime.ConvertObjectList<DisturbanceUserCustom>(d_user_customValue, item => DisturbanceUserCustom.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Disturbance FromJson(string json)
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
