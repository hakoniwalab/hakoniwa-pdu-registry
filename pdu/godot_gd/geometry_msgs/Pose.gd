class_name HakoPdu_geometry_msgs_Pose
extends RefCounted


const PointScript = preload("./Point.gd")


const QuaternionScript = preload("./Quaternion.gd")


var position: HakoPdu_geometry_msgs_Point = HakoPdu_geometry_msgs_Point.new()
var orientation: HakoPdu_geometry_msgs_Quaternion = HakoPdu_geometry_msgs_Quaternion.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_Pose:
    var obj := HakoPdu_geometry_msgs_Pose.new()
    if d.has("position"):
        obj.position = PointScript.from_dict(d["position"])
    if d.has("orientation"):
        obj.orientation = QuaternionScript.from_dict(d["orientation"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["position"] = position.to_dict()
    d["orientation"] = orientation.to_dict()
    return d
