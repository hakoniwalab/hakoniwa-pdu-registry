class_name HakoPdu_std_msgs_MultiArrayDimension
extends RefCounted


var label: String = ""
var size: int = 0
var stride: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_std_msgs_MultiArrayDimension:
    var obj := HakoPdu_std_msgs_MultiArrayDimension.new()
    if d.has("label"):
        obj.label = d["label"]
    if d.has("size"):
        obj.size = d["size"]
    if d.has("stride"):
        obj.stride = d["stride"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["label"] = label
    d["size"] = size
    d["stride"] = stride
    return d
