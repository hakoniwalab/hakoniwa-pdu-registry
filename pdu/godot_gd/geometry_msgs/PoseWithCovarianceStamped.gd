class_name HakoPdu_geometry_msgs_PoseWithCovarianceStamped
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const PointScript = preload("./Point.gd")


const PoseScript = preload("./Pose.gd")


const PoseWithCovarianceScript = preload("./PoseWithCovariance.gd")


const QuaternionScript = preload("./Quaternion.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var pose: HakoPdu_geometry_msgs_PoseWithCovariance = HakoPdu_geometry_msgs_PoseWithCovariance.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_PoseWithCovarianceStamped:
    var obj := HakoPdu_geometry_msgs_PoseWithCovarianceStamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("pose"):
        obj.pose = PoseWithCovarianceScript.from_dict(d["pose"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["pose"] = pose.to_dict()
    return d
