class_name HakoPdu_drone_srv_msgs_DroneGetStateRequest
extends RefCounted


var drone_name: String = ""

static func from_dict(d: Dictionary) -> HakoPdu_drone_srv_msgs_DroneGetStateRequest:
    var obj := HakoPdu_drone_srv_msgs_DroneGetStateRequest.new()
    if d.has("drone_name"):
        obj.drone_name = d["drone_name"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["drone_name"] = drone_name
    return d
