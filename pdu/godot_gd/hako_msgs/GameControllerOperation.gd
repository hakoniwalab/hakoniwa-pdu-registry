class_name HakoPdu_hako_msgs_GameControllerOperation
extends RefCounted


var axis: PackedFloat64Array = PackedFloat64Array()
var button: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_GameControllerOperation:
    var obj := HakoPdu_hako_msgs_GameControllerOperation.new()
    if d.has("axis"):
        obj.axis = d["axis"]
    if d.has("button"):
        obj.button = d["button"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["axis"] = axis
    d["button"] = button
    return d
