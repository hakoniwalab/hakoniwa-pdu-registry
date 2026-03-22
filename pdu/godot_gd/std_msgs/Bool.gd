class_name HakoPdu_std_msgs_Bool
extends RefCounted


var data: bool = false

static func from_dict(d: Dictionary) -> HakoPdu_std_msgs_Bool:
    var obj := HakoPdu_std_msgs_Bool.new()
    if d.has("data"):
        obj.data = d["data"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["data"] = data
    return d
