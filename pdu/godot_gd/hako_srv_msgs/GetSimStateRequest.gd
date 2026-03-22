class_name HakoPdu_hako_srv_msgs_GetSimStateRequest
extends RefCounted


var name: String = ""

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_GetSimStateRequest:
    var obj := HakoPdu_hako_srv_msgs_GetSimStateRequest.new()
    if d.has("name"):
        obj.name = d["name"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["name"] = name
    return d
