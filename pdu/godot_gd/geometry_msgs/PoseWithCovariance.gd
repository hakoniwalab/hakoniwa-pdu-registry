class_name HakoPdu_geometry_msgs_PoseWithCovariance
extends RefCounted


const PointScript = preload("./Point.gd")


const PoseScript = preload("./Pose.gd")


const QuaternionScript = preload("./Quaternion.gd")


var pose: HakoPdu_geometry_msgs_Pose = HakoPdu_geometry_msgs_Pose.new()
var covariance: PackedFloat64Array = PackedFloat64Array()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_PoseWithCovariance:
    var obj := HakoPdu_geometry_msgs_PoseWithCovariance.new()
    if d.has("pose"):
        obj.pose = PoseScript.from_dict(d["pose"])
    if d.has("covariance"):
        obj.covariance = d["covariance"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["pose"] = pose.to_dict()
    d["covariance"] = covariance
    return d
