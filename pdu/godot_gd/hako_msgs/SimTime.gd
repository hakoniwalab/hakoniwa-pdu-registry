class_name HakoPdu_hako_msgs_SimTime
extends RefCounted


var time_usec: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_SimTime:
    var obj := HakoPdu_hako_msgs_SimTime.new()
    if d.has("time_usec"):
        obj.time_usec = d["time_usec"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["time_usec"] = time_usec
    return d
