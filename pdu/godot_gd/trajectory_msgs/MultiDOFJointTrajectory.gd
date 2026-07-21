class_name HakoPdu_trajectory_msgs_MultiDOFJointTrajectory
extends RefCounted


const DurationScript = preload("../builtin_interfaces/Duration.gd")


const TimeScript = preload("../builtin_interfaces/Time.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const TransformScript = preload("../geometry_msgs/Transform.gd")


const TwistScript = preload("../geometry_msgs/Twist.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


const MultiDOFJointTrajectoryPointScript = preload("./MultiDOFJointTrajectoryPoint.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var joint_names: Array[String] = []
var points: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_trajectory_msgs_MultiDOFJointTrajectory:
    var obj := HakoPdu_trajectory_msgs_MultiDOFJointTrajectory.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("joint_names"):
        obj.joint_names = d["joint_names"]
    if d.has("points"):
        obj.points = []
        for item in d["points"]:
            obj.points.append(MultiDOFJointTrajectoryPointScript.from_dict(item))
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
