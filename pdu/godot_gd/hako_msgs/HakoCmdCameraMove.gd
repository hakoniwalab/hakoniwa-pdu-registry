class_name HakoPdu_hako_msgs_HakoCmdCameraMove
extends RefCounted


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


const HakoCmdHeaderScript = preload("./HakoCmdHeader.gd")


var header: HakoPdu_hako_msgs_HakoCmdHeader = HakoPdu_hako_msgs_HakoCmdHeader.new()
var request_id: int = 0
var angle: HakoPdu_geometry_msgs_Vector3 = HakoPdu_geometry_msgs_Vector3.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_HakoCmdCameraMove:
    var obj := HakoPdu_hako_msgs_HakoCmdCameraMove.new()
    if d.has("header"):
        obj.header = HakoCmdHeaderScript.from_dict(d["header"])
    if d.has("request_id"):
        obj.request_id = d["request_id"]
    if d.has("angle"):
        obj.angle = Vector3Script.from_dict(d["angle"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["request_id"] = request_id
    d["angle"] = angle.to_dict()
    return d
