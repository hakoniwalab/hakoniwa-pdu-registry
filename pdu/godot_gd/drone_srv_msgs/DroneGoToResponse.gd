class_name HakoPdu_drone_srv_msgs_DroneGoToResponse
extends RefCounted


var ok: bool = false
var message: String = ""

static func from_dict(d: Dictionary) -> HakoPdu_drone_srv_msgs_DroneGoToResponse:
    var obj := HakoPdu_drone_srv_msgs_DroneGoToResponse.new()
    if d.has("ok"):
        obj.ok = d["ok"]
    if d.has("message"):
        obj.message = d["message"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["ok"] = ok
    d["message"] = message
    return d
