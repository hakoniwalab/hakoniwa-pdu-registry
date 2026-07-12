class_name HakoPdu_hako_srv_msgs_DetachRequest
extends RefCounted


var session_id: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_DetachRequest:
    var obj := HakoPdu_hako_srv_msgs_DetachRequest.new()
    if d.has("session_id"):
        obj.session_id = d["session_id"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["session_id"] = session_id
    return d
