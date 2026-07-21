class_name HakoPdu_trajectory_msgs_JointTrajectory
extends RefCounted


const DurationScript = preload("../builtin_interfaces/Duration.gd")


const TimeScript = preload("../builtin_interfaces/Time.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


const JointTrajectoryPointScript = preload("./JointTrajectoryPoint.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var joint_names: Array[String] = []
var points: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_trajectory_msgs_JointTrajectory:
    var obj := HakoPdu_trajectory_msgs_JointTrajectory.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("joint_names"):
        obj.joint_names = d["joint_names"]
    if d.has("points"):
        obj.points = []
        for item in d["points"]:
            obj.points.append(JointTrajectoryPointScript.from_dict(item))
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["joint_names"] = joint_names
    var points_array: Array = []
    for item in points:
        points_array.append(item.to_dict())
    d["points"] = points_array
    return d
