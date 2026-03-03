using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public class LiDARScanResponse
    {
        public bool ok { get; set; } = false;
        public PointCloud2 point_cloud { get; set; } = new PointCloud2();
        public Pose lidar_pose { get; set; } = new Pose();
        public string message { get; set; } = string.Empty;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["ok"] = ToSerializableValue(ok);
            dict["point_cloud"] = ToSerializableValue(point_cloud);
            dict["lidar_pose"] = ToSerializableValue(lidar_pose);
            dict["message"] = ToSerializableValue(message);
            return dict;
        }

        public static LiDARScanResponse FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new LiDARScanResponse();
            if (dict.TryGetValue("ok", out var okValue))
            {
                obj.ok = PduRuntime.ConvertValue<bool>(okValue);
            }
            if (dict.TryGetValue("point_cloud", out var point_cloudValue))
            {
                obj.point_cloud = PduRuntime.ConvertObject<PointCloud2>(point_cloudValue, item => PointCloud2.FromDictionary(item));
            }
            if (dict.TryGetValue("lidar_pose", out var lidar_poseValue))
            {
                obj.lidar_pose = PduRuntime.ConvertObject<Pose>(lidar_poseValue, item => Pose.FromDictionary(item));
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

        public static LiDARScanResponse FromJson(string json)
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
