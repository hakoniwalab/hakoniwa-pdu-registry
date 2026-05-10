class_name HakoPdu_sensor_msgs_TimeReference
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var time_ref: HakoPdu_builtin_interfaces_Time = HakoPdu_builtin_interfaces_Time.new()
var source: String = ""

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_TimeReference:
    var obj := HakoPdu_sensor_msgs_TimeReference.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("time_ref"):
        obj.time_ref = TimeScript.from_dict(d["time_ref"])
    if d.has("source"):
        obj.source = d["source"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["time_ref"] = time_ref.to_dict()
    d["source"] = source
    return d
