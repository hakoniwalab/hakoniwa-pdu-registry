class_name HakoPdu_can_msgs_HakoCanBody
extends RefCounted


var data: PackedByteArray = PackedByteArray()

static func from_dict(d: Dictionary) -> HakoPdu_can_msgs_HakoCanBody:
    var obj := HakoPdu_can_msgs_HakoCanBody.new()
    if d.has("data"):
        obj.data = d["data"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["data"] = data
    return d
