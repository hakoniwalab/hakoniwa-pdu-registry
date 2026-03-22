class_name HakoPdu_std_msgs_Float64
extends RefCounted


var data: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_std_msgs_Float64:
    var obj := HakoPdu_std_msgs_Float64.new()
    if d.has("data"):
        obj.data = d["data"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["data"] = data
    return d
