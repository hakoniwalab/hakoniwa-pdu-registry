class_name HakoPdu_std_msgs_Empty
extends RefCounted


var hako_dummy: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_std_msgs_Empty:
    var obj := HakoPdu_std_msgs_Empty.new()
    if d.has("hako_dummy"):
        obj.hako_dummy = d["hako_dummy"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["hako_dummy"] = hako_dummy
    return d
