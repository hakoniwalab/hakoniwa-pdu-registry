using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public class DroneStatus
    {
        public int flight_mode { get; set; } = 0;
        public int internal_state { get; set; } = 0;
        public Vector3 propeller_wind { get; set; } = new Vector3();
        public int collided_counts { get; set; } = 0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["flight_mode"] = ToSerializableValue(flight_mode);
            dict["internal_state"] = ToSerializableValue(internal_state);
            dict["propeller_wind"] = ToSerializableValue(propeller_wind);
            dict["collided_counts"] = ToSerializableValue(collided_counts);
            return dict;
        }

        public static DroneStatus FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new DroneStatus();
            if (dict.TryGetValue("flight_mode", out var flight_modeValue))
            {
                obj.flight_mode = PduRuntime.ConvertValue<int>(flight_modeValue);
            }
            if (dict.TryGetValue("internal_state", out var internal_stateValue))
            {
                obj.internal_state = PduRuntime.ConvertValue<int>(internal_stateValue);
            }
            if (dict.TryGetValue("propeller_wind", out var propeller_windValue))
            {
                obj.propeller_wind = PduRuntime.ConvertObject<Vector3>(propeller_windValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("collided_counts", out var collided_countsValue))
            {
                obj.collided_counts = PduRuntime.ConvertValue<int>(collided_countsValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static DroneStatus FromJson(string json)
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
