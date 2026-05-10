class_name HakoPdu_sensor_msgs_Joy
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var axes: PackedFloat32Array = PackedFloat32Array()
var buttons: PackedInt32Array = PackedInt32Array()

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_Joy:
    var obj := HakoPdu_sensor_msgs_Joy.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("axes"):
        obj.axes = d["axes"]
    if d.has("buttons"):
        obj.buttons = d["buttons"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["axes"] = axes
    d["buttons"] = buttons
    return d
