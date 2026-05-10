class_name HakoPdu_sensor_msgs_FluidPressure
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var fluid_pressure: float = 0.0
var variance: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_FluidPressure:
    var obj := HakoPdu_sensor_msgs_FluidPressure.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("fluid_pressure"):
        obj.fluid_pressure = d["fluid_pressure"]
    if d.has("variance"):
        obj.variance = d["variance"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["fluid_pressure"] = fluid_pressure
    d["variance"] = variance
    return d
