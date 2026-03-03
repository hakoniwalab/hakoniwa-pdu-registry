using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public class DroneGetStateResponse
    {
        public bool ok { get; set; } = false;
        public bool is_ready { get; set; } = false;
        public Pose current_pose { get; set; } = new Pose();
        public HakoBatteryStatus battery_status { get; set; } = new HakoBatteryStatus();
        public string mode { get; set; } = string.Empty;
        public string message { get; set; } = string.Empty;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["ok"] = ToSerializableValue(ok);
            dict["is_ready"] = ToSerializableValue(is_ready);
            dict["current_pose"] = ToSerializableValue(current_pose);
            dict["battery_status"] = ToSerializableValue(battery_status);
            dict["mode"] = ToSerializableValue(mode);
            dict["message"] = ToSerializableValue(message);
            return dict;
        }

        public static DroneGetStateResponse FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new DroneGetStateResponse();
            if (dict.TryGetValue("ok", out var okValue))
            {
                obj.ok = PduRuntime.ConvertValue<bool>(okValue);
            }
            if (dict.TryGetValue("is_ready", out var is_readyValue))
            {
                obj.is_ready = PduRuntime.ConvertValue<bool>(is_readyValue);
            }
            if (dict.TryGetValue("current_pose", out var current_poseValue))
            {
                obj.current_pose = PduRuntime.ConvertObject<Pose>(current_poseValue, item => Pose.FromDictionary(item));
            }
            if (dict.TryGetValue("battery_status", out var battery_statusValue))
            {
                obj.battery_status = PduRuntime.ConvertObject<HakoBatteryStatus>(battery_statusValue, item => HakoBatteryStatus.FromDictionary(item));
            }
            if (dict.TryGetValue("mode", out var modeValue))
            {
                obj.mode = PduRuntime.ConvertValue<string>(modeValue);
            }
            if (dict.TryGetValue("message", out var messageValue))
            {
                obj.message = PduRuntime.ConvertValue<string>(messageValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static DroneGetStateResponse FromJson(string json)
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
