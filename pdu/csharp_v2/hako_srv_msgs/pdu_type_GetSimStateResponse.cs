using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class GetSimStateResponse
    {
        public uint sim_state { get; set; } = 0;
        public long master_time { get; set; } = 0;
        public bool is_pdu_created { get; set; } = false;
        public bool is_simulation_mode { get; set; } = false;
        public bool is_pdu_sync_mode { get; set; } = false;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["sim_state"] = ToSerializableValue(sim_state);
            dict["master_time"] = ToSerializableValue(master_time);
            dict["is_pdu_created"] = ToSerializableValue(is_pdu_created);
            dict["is_simulation_mode"] = ToSerializableValue(is_simulation_mode);
            dict["is_pdu_sync_mode"] = ToSerializableValue(is_pdu_sync_mode);
            return dict;
        }

        public static GetSimStateResponse FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new GetSimStateResponse();
            if (dict.TryGetValue("sim_state", out var sim_stateValue))
            {
                obj.sim_state = PduRuntime.ConvertValue<uint>(sim_stateValue);
            }
            if (dict.TryGetValue("master_time", out var master_timeValue))
            {
                obj.master_time = PduRuntime.ConvertValue<long>(master_timeValue);
            }
            if (dict.TryGetValue("is_pdu_created", out var is_pdu_createdValue))
            {
                obj.is_pdu_created = PduRuntime.ConvertValue<bool>(is_pdu_createdValue);
            }
            if (dict.TryGetValue("is_simulation_mode", out var is_simulation_modeValue))
            {
                obj.is_simulation_mode = PduRuntime.ConvertValue<bool>(is_simulation_modeValue);
            }
            if (dict.TryGetValue("is_pdu_sync_mode", out var is_pdu_sync_modeValue))
            {
                obj.is_pdu_sync_mode = PduRuntime.ConvertValue<bool>(is_pdu_sync_modeValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static GetSimStateResponse FromJson(string json)
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
