class_name HakoPdu_hako_srv_msgs_AddTwoIntsResponse
extends RefCounted


var sum: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_AddTwoIntsResponse:
    var obj := HakoPdu_hako_srv_msgs_AddTwoIntsResponse.new()
    if d.has("sum"):
        obj.sum = d["sum"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["sum"] = sum
    return d
