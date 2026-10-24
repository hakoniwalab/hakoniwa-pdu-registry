class_name HakoPdu_hako_srv_msgs_RenderObject
extends RefCounted


const PointScript = preload("../geometry_msgs/Point.gd")


const PoseScript = preload("../geometry_msgs/Pose.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


var name: String = ""
var model: String = ""
var pose: HakoPdu_geometry_msgs_Pose = HakoPdu_geometry_msgs_Pose.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_RenderObject:
    var obj := HakoPdu_hako_srv_msgs_RenderObject.new()
    if d.has("name"):
        obj.name = d["name"]
    if d.has("model"):
        obj.model = d["model"]
    if d.has("pose"):
        obj.pose = PoseScript.from_dict(d["pose"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["name"] = name
    d["model"] = model
    d["pose"] = pose.to_dict()
    return d
