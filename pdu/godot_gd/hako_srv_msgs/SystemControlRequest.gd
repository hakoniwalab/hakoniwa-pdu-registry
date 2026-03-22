class_name HakoPdu_hako_srv_msgs_SystemControlRequest
extends RefCounted


var opcode: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_SystemControlRequest:
    var obj := HakoPdu_hako_srv_msgs_SystemControlRequest.new()
    if d.has("opcode"):
        obj.opcode = d["opcode"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["opcode"] = opcode
    return d
