class_name HakoPdu_std_msgs_Int16
extends RefCounted


var data: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_std_msgs_Int16:
    var obj := HakoPdu_std_msgs_Int16.new()
    if d.has("data"):
        obj.data = d["data"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["data"] = data
    return d
