using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public class DroneGoToRequest
    {
        public string drone_name { get; set; } = string.Empty;
        public Vector3 target_pose { get; set; } = new Vector3();
        public float speed_m_s { get; set; } = 0.0F;
        public float yaw_deg { get; set; } = 0.0F;
        public float tolerance_m { get; set; } = 0.0F;
        public float timeout_sec { get; set; } = 0.0F;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["drone_name"] = ToSerializableValue(drone_name);
            dict["target_pose"] = ToSerializableValue(target_pose);
            dict["speed_m_s"] = ToSerializableValue(speed_m_s);
            dict["yaw_deg"] = ToSerializableValue(yaw_deg);
            dict["tolerance_m"] = ToSerializableValue(tolerance_m);
            dict["timeout_sec"] = ToSerializableValue(timeout_sec);
            return dict;
        }

        public static DroneGoToRequest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new DroneGoToRequest();
            if (dict.TryGetValue("drone_name", out var drone_nameValue))
            {
                obj.drone_name = PduRuntime.ConvertValue<string>(drone_nameValue);
            }
            if (dict.TryGetValue("target_pose", out var target_poseValue))
            {
                obj.target_pose = PduRuntime.ConvertObject<Vector3>(target_poseValue, item => Vector3.FromDictionary(item));
            }
            if (dict.TryGetValue("speed_m_s", out var speed_m_sValue))
            {
                obj.speed_m_s = PduRuntime.ConvertValue<float>(speed_m_sValue);
            }
            if (dict.TryGetValue("yaw_deg", out var yaw_degValue))
            {
                obj.yaw_deg = PduRuntime.ConvertValue<float>(yaw_degValue);
            }
            if (dict.TryGetValue("tolerance_m", out var tolerance_mValue))
            {
                obj.tolerance_m = PduRuntime.ConvertValue<float>(tolerance_mValue);
            }
            if (dict.TryGetValue("timeout_sec", out var timeout_secValue))
            {
                obj.timeout_sec = PduRuntime.ConvertValue<float>(timeout_secValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static DroneGoToRequest FromJson(string json)
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
