using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class RenderCameraRequest
    {
        public string camera_name { get; set; } = string.Empty;
        public ulong sim_time_usec { get; set; } = 0;
        public Pose camera_pose { get; set; } = new Pose();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["camera_name"] = ToSerializableValue(camera_name);
            dict["sim_time_usec"] = ToSerializableValue(sim_time_usec);
            dict["camera_pose"] = ToSerializableValue(camera_pose);
            return dict;
        }

        public static RenderCameraRequest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new RenderCameraRequest();
            if (dict.TryGetValue("camera_name", out var camera_nameValue))
            {
                obj.camera_name = PduRuntime.ConvertValue<string>(camera_nameValue);
            }
            if (dict.TryGetValue("sim_time_usec", out var sim_time_usecValue))
            {
                obj.sim_time_usec = PduRuntime.ConvertValue<ulong>(sim_time_usecValue);
            }
            if (dict.TryGetValue("camera_pose", out var camera_poseValue))
            {
                obj.camera_pose = PduRuntime.ConvertObject<Pose>(camera_poseValue, item => Pose.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static RenderCameraRequest FromJson(string json)
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
