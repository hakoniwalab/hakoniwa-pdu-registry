using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public class PersonStepResponse
    {
        public ulong step { get; set; } = 0;
        public uint result_code { get; set; } = 0;
        public ulong sim_time_usec { get; set; } = 0;
        public Transform pose { get; set; } = new Transform();
        public Twist twist { get; set; } = new Twist();
        public JointState joints { get; set; } = new JointState();

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["step"] = ToSerializableValue(step);
            dict["result_code"] = ToSerializableValue(result_code);
            dict["sim_time_usec"] = ToSerializableValue(sim_time_usec);
            dict["pose"] = ToSerializableValue(pose);
            dict["twist"] = ToSerializableValue(twist);
            dict["joints"] = ToSerializableValue(joints);
            return dict;
        }

        public static PersonStepResponse FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new PersonStepResponse();
            if (dict.TryGetValue("step", out var stepValue))
            {
                obj.step = PduRuntime.ConvertValue<ulong>(stepValue);
            }
            if (dict.TryGetValue("result_code", out var result_codeValue))
            {
                obj.result_code = PduRuntime.ConvertValue<uint>(result_codeValue);
            }
            if (dict.TryGetValue("sim_time_usec", out var sim_time_usecValue))
            {
                obj.sim_time_usec = PduRuntime.ConvertValue<ulong>(sim_time_usecValue);
            }
            if (dict.TryGetValue("pose", out var poseValue))
            {
                obj.pose = PduRuntime.ConvertObject<Transform>(poseValue, item => Transform.FromDictionary(item));
            }
            if (dict.TryGetValue("twist", out var twistValue))
            {
                obj.twist = PduRuntime.ConvertObject<Twist>(twistValue, item => Twist.FromDictionary(item));
            }
            if (dict.TryGetValue("joints", out var jointsValue))
            {
                obj.joints = PduRuntime.ConvertObject<JointState>(jointsValue, item => JointState.FromDictionary(item));
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static PersonStepResponse FromJson(string json)
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
