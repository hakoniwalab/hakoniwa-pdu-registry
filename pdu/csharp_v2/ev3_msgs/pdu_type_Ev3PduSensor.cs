using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2.ev3_msgs
{
    public class Ev3PduSensor
    {
        public Ev3PduSensorHeader head { get; set; } = new Ev3PduSensorHeader();
        public List<byte> buttons { get; set; } = new List<byte>();
        public List<Ev3PduColorSensor> color_sensors { get; set; } = new List<Ev3PduColorSensor>();
        public List<Ev3PduTouchSensor> touch_sensors { get; set; } = new List<Ev3PduTouchSensor>();
        public List<uint> motor_angle { get; set; } = new List<uint>();
        public int gyro_degree { get; set; } = 0;
        public int gyro_degree_rate { get; set; } = 0;
        public uint sensor_ultrasonic { get; set; } = 0;
        public double gps_lat { get; set; } = 0.0;
        public double gps_lon { get; set; } = 0.0;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["head"] = ToSerializableValue(head);
            dict["buttons"] = ToSerializableValue(buttons);
            dict["color_sensors"] = ToSerializableValue(color_sensors);
            dict["touch_sensors"] = ToSerializableValue(touch_sensors);
            dict["motor_angle"] = ToSerializableValue(motor_angle);
            dict["gyro_degree"] = ToSerializableValue(gyro_degree);
            dict["gyro_degree_rate"] = ToSerializableValue(gyro_degree_rate);
            dict["sensor_ultrasonic"] = ToSerializableValue(sensor_ultrasonic);
            dict["gps_lat"] = ToSerializableValue(gps_lat);
            dict["gps_lon"] = ToSerializableValue(gps_lon);
            return dict;
        }

        public static Ev3PduSensor FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new Ev3PduSensor();
            if (dict.TryGetValue("head", out var headValue))
            {
                obj.head = PduRuntime.ConvertObject<Ev3PduSensorHeader>(headValue, item => Ev3PduSensorHeader.FromDictionary(item));
            }
            if (dict.TryGetValue("buttons", out var buttonsValue))
            {
                obj.buttons = PduRuntime.ConvertList<byte>(buttonsValue);
            }
            if (dict.TryGetValue("color_sensors", out var color_sensorsValue))
            {
                obj.color_sensors = PduRuntime.ConvertObjectList<Ev3PduColorSensor>(color_sensorsValue, item => Ev3PduColorSensor.FromDictionary(item));
            }
            if (dict.TryGetValue("touch_sensors", out var touch_sensorsValue))
            {
                obj.touch_sensors = PduRuntime.ConvertObjectList<Ev3PduTouchSensor>(touch_sensorsValue, item => Ev3PduTouchSensor.FromDictionary(item));
            }
            if (dict.TryGetValue("motor_angle", out var motor_angleValue))
            {
                obj.motor_angle = PduRuntime.ConvertList<uint>(motor_angleValue);
            }
            if (dict.TryGetValue("gyro_degree", out var gyro_degreeValue))
            {
                obj.gyro_degree = PduRuntime.ConvertValue<int>(gyro_degreeValue);
            }
            if (dict.TryGetValue("gyro_degree_rate", out var gyro_degree_rateValue))
            {
                obj.gyro_degree_rate = PduRuntime.ConvertValue<int>(gyro_degree_rateValue);
            }
            if (dict.TryGetValue("sensor_ultrasonic", out var sensor_ultrasonicValue))
            {
                obj.sensor_ultrasonic = PduRuntime.ConvertValue<uint>(sensor_ultrasonicValue);
            }
            if (dict.TryGetValue("gps_lat", out var gps_latValue))
            {
                obj.gps_lat = PduRuntime.ConvertValue<double>(gps_latValue);
            }
            if (dict.TryGetValue("gps_lon", out var gps_lonValue))
            {
                obj.gps_lon = PduRuntime.ConvertValue<double>(gps_lonValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static Ev3PduSensor FromJson(string json)
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
