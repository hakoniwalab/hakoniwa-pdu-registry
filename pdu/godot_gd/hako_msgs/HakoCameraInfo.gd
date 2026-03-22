class_name HakoPdu_hako_msgs_HakoCameraInfo
extends RefCounted


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


var request_id: int = 0
var angle: HakoPdu_geometry_msgs_Vector3 = HakoPdu_geometry_msgs_Vector3.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_HakoCameraInfo:
    var obj := HakoPdu_hako_msgs_HakoCameraInfo.new()
    if d.has("request_id"):
        obj.request_id = d["request_id"]
    if d.has("angle"):
        obj.angle = Vector3Script.from_dict(d["angle"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["request_id"] = request_id
    d["angle"] = angle.to_dict()
    return d
