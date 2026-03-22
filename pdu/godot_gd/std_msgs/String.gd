class_name HakoPdu_std_msgs_String
extends RefCounted


var data: String = ""

static func from_dict(d: Dictionary) -> HakoPdu_std_msgs_String:
    var obj := HakoPdu_std_msgs_String.new()
    if d.has("data"):
        obj.data = d["data"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["data"] = data
    return d
