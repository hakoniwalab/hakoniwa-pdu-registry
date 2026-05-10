class_name HakoPdu_geometry_msgs_PoseArray
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const PointScript = preload("./Point.gd")


const PoseScript = preload("./Pose.gd")


const QuaternionScript = preload("./Quaternion.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var poses: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_PoseArray:
    var obj := HakoPdu_geometry_msgs_PoseArray.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("poses"):
        obj.poses = []
        for item in d["poses"]:
            obj.poses.append(PoseScript.from_dict(item))
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    var poses_array: Array = []
    for item in poses:
        poses_array.append(item.to_dict())
    d["poses"] = poses_array
    return d
