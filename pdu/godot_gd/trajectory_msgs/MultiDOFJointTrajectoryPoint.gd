class_name HakoPdu_trajectory_msgs_MultiDOFJointTrajectoryPoint
extends RefCounted


const DurationScript = preload("../builtin_interfaces/Duration.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const TransformScript = preload("../geometry_msgs/Transform.gd")


const TwistScript = preload("../geometry_msgs/Twist.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


var transforms: Array = []
var velocities: Array = []
var accelerations: Array = []
var time_from_start: HakoPdu_builtin_interfaces_Duration = HakoPdu_builtin_interfaces_Duration.new()

static func from_dict(d: Dictionary) -> HakoPdu_trajectory_msgs_MultiDOFJointTrajectoryPoint:
    var obj := HakoPdu_trajectory_msgs_MultiDOFJointTrajectoryPoint.new()
    if d.has("transforms"):
        obj.transforms = []
        for item in d["transforms"]:
            obj.transforms.append(TransformScript.from_dict(item))
    if d.has("velocities"):
        obj.velocities = []
        for item in d["velocities"]:
            obj.velocities.append(TwistScript.from_dict(item))
    if d.has("accelerations"):
        obj.accelerations = []
        for item in d["accelerations"]:
            obj.accelerations.append(TwistScript.from_dict(item))
    if d.has("time_from_start"):
        obj.time_from_start = DurationScript.from_dict(d["time_from_start"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    var transforms_array: Array = []
    for item in transforms:
        transforms_array.append(item.to_dict())
    d["transforms"] = transforms_array
    var velocities_array: Array = []
    for item in velocities:
        velocities_array.append(item.to_dict())
    d["velocities"] = velocities_array
    var accelerations_array: Array = []
    for item in accelerations:
        accelerations_array.append(item.to_dict())
    d["accelerations"] = accelerations_array
    d["time_from_start"] = time_from_start.to_dict()
    return d
