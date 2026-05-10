class_name HakoPdu_sensor_msgs_BatteryState
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var voltage: float = 0.0
var temperature: float = 0.0
var current: float = 0.0
var charge: float = 0.0
var capacity: float = 0.0
var design_capacity: float = 0.0
var percentage: float = 0.0
var power_supply_status: int = 0
var power_supply_health: int = 0
var power_supply_technology: int = 0
var present: bool = false
var cell_voltage: PackedFloat32Array = PackedFloat32Array()
var cell_temperature: PackedFloat32Array = PackedFloat32Array()
var location: String = ""
var serial_number: String = ""

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_BatteryState:
    var obj := HakoPdu_sensor_msgs_BatteryState.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("voltage"):
        obj.voltage = d["voltage"]
    if d.has("temperature"):
        obj.temperature = d["temperature"]
    if d.has("current"):
        obj.current = d["current"]
    if d.has("charge"):
        obj.charge = d["charge"]
    if d.has("capacity"):
        obj.capacity = d["capacity"]
    if d.has("design_capacity"):
        obj.design_capacity = d["design_capacity"]
    if d.has("percentage"):
        obj.percentage = d["percentage"]
    if d.has("power_supply_status"):
        obj.power_supply_status = d["power_supply_status"]
    if d.has("power_supply_health"):
        obj.power_supply_health = d["power_supply_health"]
    if d.has("power_supply_technology"):
        obj.power_supply_technology = d["power_supply_technology"]
    if d.has("present"):
        obj.present = d["present"]
    if d.has("cell_voltage"):
        obj.cell_voltage = d["cell_voltage"]
    if d.has("cell_temperature"):
        obj.cell_temperature = d["cell_temperature"]
    if d.has("location"):
        obj.location = d["location"]
    if d.has("serial_number"):
        obj.serial_number = d["serial_number"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["voltage"] = voltage
    d["temperature"] = temperature
    d["current"] = current
    d["charge"] = charge
    d["capacity"] = capacity
    d["design_capacity"] = design_capacity
    d["percentage"] = percentage
    d["power_supply_status"] = power_supply_status
    d["power_supply_health"] = power_supply_health
    d["power_supply_technology"] = power_supply_technology
    d["present"] = present
    d["cell_voltage"] = cell_voltage
    d["cell_temperature"] = cell_temperature
    d["location"] = location
    d["serial_number"] = serial_number
    return d
