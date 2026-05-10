class_name HakoPdu_sensor_msgs_Range
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var radiation_type: int = 0
var field_of_view: float = 0.0
var min_range: float = 0.0
var max_range: float = 0.0
var range: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_Range:
    var obj := HakoPdu_sensor_msgs_Range.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("radiation_type"):
        obj.radiation_type = d["radiation_type"]
    if d.has("field_of_view"):
        obj.field_of_view = d["field_of_view"]
    if d.has("min_range"):
        obj.min_range = d["min_range"]
    if d.has("max_range"):
        obj.max_range = d["max_range"]
    if d.has("range"):
        obj.range = d["range"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["radiation_type"] = radiation_type
    d["field_of_view"] = field_of_view
    d["min_range"] = min_range
    d["max_range"] = max_range
    d["range"] = range
    return d
