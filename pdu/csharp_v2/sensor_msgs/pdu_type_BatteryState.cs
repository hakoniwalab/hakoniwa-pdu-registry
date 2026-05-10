using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public class BatteryState
    {
        public Header header { get; set; } = new Header();
        public float voltage { get; set; } = 0.0F;
        public float temperature { get; set; } = 0.0F;
        public float current { get; set; } = 0.0F;
        public float charge { get; set; } = 0.0F;
        public float capacity { get; set; } = 0.0F;
        public float design_capacity { get; set; } = 0.0F;
        public float percentage { get; set; } = 0.0F;
        public byte power_supply_status { get; set; } = 0;
        public byte power_supply_health { get; set; } = 0;
        public byte power_supply_technology { get; set; } = 0;
        public bool present { get; set; } = false;
        public List<float> cell_voltage { get; set; } = new List<float>();
        public List<float> cell_temperature { get; set; } = new List<float>();
        public string location { get; set; } = string.Empty;
        public string serial_number { get; set; } = string.Empty;

        public Dictionary<string, object?> ToDictionary()
        {
            var dict = new Dictionary<string, object?>();
            dict["header"] = ToSerializableValue(header);
            dict["voltage"] = ToSerializableValue(voltage);
            dict["temperature"] = ToSerializableValue(temperature);
            dict["current"] = ToSerializableValue(current);
            dict["charge"] = ToSerializableValue(charge);
            dict["capacity"] = ToSerializableValue(capacity);
            dict["design_capacity"] = ToSerializableValue(design_capacity);
            dict["percentage"] = ToSerializableValue(percentage);
            dict["power_supply_status"] = ToSerializableValue(power_supply_status);
            dict["power_supply_health"] = ToSerializableValue(power_supply_health);
            dict["power_supply_technology"] = ToSerializableValue(power_supply_technology);
            dict["present"] = ToSerializableValue(present);
            dict["cell_voltage"] = ToSerializableValue(cell_voltage);
            dict["cell_temperature"] = ToSerializableValue(cell_temperature);
            dict["location"] = ToSerializableValue(location);
            dict["serial_number"] = ToSerializableValue(serial_number);
            return dict;
        }

        public static BatteryState FromDictionary(Dictionary<string, object?> dict)
        {
            var obj = new BatteryState();
            if (dict.TryGetValue("header", out var headerValue))
            {
                obj.header = PduRuntime.ConvertObject<Header>(headerValue, item => Header.FromDictionary(item));
            }
            if (dict.TryGetValue("voltage", out var voltageValue))
            {
                obj.voltage = PduRuntime.ConvertValue<float>(voltageValue);
            }
            if (dict.TryGetValue("temperature", out var temperatureValue))
            {
                obj.temperature = PduRuntime.ConvertValue<float>(temperatureValue);
            }
            if (dict.TryGetValue("current", out var currentValue))
            {
                obj.current = PduRuntime.ConvertValue<float>(currentValue);
            }
            if (dict.TryGetValue("charge", out var chargeValue))
            {
                obj.charge = PduRuntime.ConvertValue<float>(chargeValue);
            }
            if (dict.TryGetValue("capacity", out var capacityValue))
            {
                obj.capacity = PduRuntime.ConvertValue<float>(capacityValue);
            }
            if (dict.TryGetValue("design_capacity", out var design_capacityValue))
            {
                obj.design_capacity = PduRuntime.ConvertValue<float>(design_capacityValue);
            }
            if (dict.TryGetValue("percentage", out var percentageValue))
            {
                obj.percentage = PduRuntime.ConvertValue<float>(percentageValue);
            }
            if (dict.TryGetValue("power_supply_status", out var power_supply_statusValue))
            {
                obj.power_supply_status = PduRuntime.ConvertValue<byte>(power_supply_statusValue);
            }
            if (dict.TryGetValue("power_supply_health", out var power_supply_healthValue))
            {
                obj.power_supply_health = PduRuntime.ConvertValue<byte>(power_supply_healthValue);
            }
            if (dict.TryGetValue("power_supply_technology", out var power_supply_technologyValue))
            {
                obj.power_supply_technology = PduRuntime.ConvertValue<byte>(power_supply_technologyValue);
            }
            if (dict.TryGetValue("present", out var presentValue))
            {
                obj.present = PduRuntime.ConvertValue<bool>(presentValue);
            }
            if (dict.TryGetValue("cell_voltage", out var cell_voltageValue))
            {
                obj.cell_voltage = PduRuntime.ConvertList<float>(cell_voltageValue);
            }
            if (dict.TryGetValue("cell_temperature", out var cell_temperatureValue))
            {
                obj.cell_temperature = PduRuntime.ConvertList<float>(cell_temperatureValue);
            }
            if (dict.TryGetValue("location", out var locationValue))
            {
                obj.location = PduRuntime.ConvertValue<string>(locationValue);
            }
            if (dict.TryGetValue("serial_number", out var serial_numberValue))
            {
                obj.serial_number = PduRuntime.ConvertValue<string>(serial_numberValue);
            }
            return obj;
        }

        public string ToJson()
        {
            return JsonSerializer.Serialize(ToDictionary());
        }

        public static BatteryState FromJson(string json)
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
