class_name HakoPdu_std_msgs_Header
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


var stamp: HakoPdu_builtin_interfaces_Time = HakoPdu_builtin_interfaces_Time.new()
var frame_id: String = ""

static func from_dict(d: Dictionary) -> HakoPdu_std_msgs_Header:
    var obj := HakoPdu_std_msgs_Header.new()
    if d.has("stamp"):
        obj.stamp = TimeScript.from_dict(d["stamp"])
    if d.has("frame_id"):
        obj.frame_id = d["frame_id"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["stamp"] = stamp.to_dict()
    d["frame_id"] = frame_id
    return d
