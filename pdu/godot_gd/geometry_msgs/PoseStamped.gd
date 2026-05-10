class_name HakoPdu_geometry_msgs_PoseStamped
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const PointScript = preload("./Point.gd")


const PoseScript = preload("./Pose.gd")


const QuaternionScript = preload("./Quaternion.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var pose: HakoPdu_geometry_msgs_Pose = HakoPdu_geometry_msgs_Pose.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_PoseStamped:
    var obj := HakoPdu_geometry_msgs_PoseStamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("pose"):
        obj.pose = PoseScript.from_dict(d["pose"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["pose"] = pose.to_dict()
    return d
