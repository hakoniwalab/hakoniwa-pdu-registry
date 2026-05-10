class_name HakoPdu_sensor_msgs_NavSatStatus
extends RefCounted


var status: int = 0
var service: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_NavSatStatus:
    var obj := HakoPdu_sensor_msgs_NavSatStatus.new()
    if d.has("status"):
        obj.status = d["status"]
    if d.has("service"):
        obj.service = d["service"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["status"] = status
    d["service"] = service
    return d
