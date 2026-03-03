using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public class MagnetGrabRequest
    {
        public string drone_name { get; set; } = string.Empty;
        public bool grab_on { get; set; } = false;
        public float timeout_sec { get; set; } = 0.0F;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["drone_name"] = ToSerializableValue(drone_name);
            dict["grab_on"] = ToSerializableValue(grab_on);
            dict["timeout_sec"] = ToSerializableValue(timeout_sec);
            return dict;
        }

        public static MagnetGrabRequest FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new MagnetGrabRequest();
            if (dict.TryGetValue("drone_name", out var drone_nameValue))
            {
                obj.drone_name = PduRuntime.ConvertValue<string>(drone_nameValue);
            }
            if (dict.TryGetValue("grab_on", out var grab_onValue))
            {
                obj.grab_on = PduRuntime.ConvertValue<bool>(grab_onValue);
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

        public static MagnetGrabRequest FromJson(string json)
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
