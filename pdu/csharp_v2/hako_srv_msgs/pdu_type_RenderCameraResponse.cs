using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class RenderCameraResponse
    {
        public uint result_code { get; set; } = 0;
        public ulong sim_time_usec { get; set; } = 0;
        public Image image { get; set; } = new Image();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["result_code"] = ToSerializableValue(result_code);
            dict["sim_time_usec"] = ToSerializableValue(sim_time_usec);
            dict["image"] = ToSerializableValue(image);
            return dict;
        }

        public static RenderCameraResponse FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new RenderCameraResponse();
            if (dict.TryGetValue("result_code", out var result_codeValue))
            {
                obj.result_code = PduRuntime.ConvertValue<uint>(result_codeValue);
            }
            if (dict.TryGetValue("sim_time_usec", out var sim_time_usecValue))
            {
                obj.sim_time_usec = PduRuntime.ConvertValue<ulong>(sim_time_usecValue);
            }
            if (dict.TryGetValue("image", out var imageValue))
            {
                obj.image = PduRuntime.ConvertObject<Image>(imageValue, item => Image.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static RenderCameraResponse FromJson(string json)
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
