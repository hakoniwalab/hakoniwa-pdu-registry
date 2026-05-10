class_name HakoPdu_nav_msgs_Path
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const PointScript = preload("../geometry_msgs/Point.gd")


const PoseScript = preload("../geometry_msgs/Pose.gd")


const PoseStampedScript = preload("../geometry_msgs/PoseStamped.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var poses: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_nav_msgs_Path:
    var obj := HakoPdu_nav_msgs_Path.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("poses"):
        obj.poses = []
        for item in d["poses"]:
            obj.poses.append(PoseStampedScript.from_dict(item))
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    var poses_array: Array = []
    for item in poses:
        poses_array.append(item.to_dict())
    d["poses"] = poses_array
    return d
