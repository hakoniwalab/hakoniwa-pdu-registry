class_name HakoPdu_trajectory_msgs_JointTrajectoryPoint
extends RefCounted


const DurationScript = preload("../builtin_interfaces/Duration.gd")


var positions: PackedFloat64Array = PackedFloat64Array()
var velocities: PackedFloat64Array = PackedFloat64Array()
var accelerations: PackedFloat64Array = PackedFloat64Array()
var effort: PackedFloat64Array = PackedFloat64Array()
var time_from_start: HakoPdu_builtin_interfaces_Duration = HakoPdu_builtin_interfaces_Duration.new()

static func from_dict(d: Dictionary) -> HakoPdu_trajectory_msgs_JointTrajectoryPoint:
    var obj := HakoPdu_trajectory_msgs_JointTrajectoryPoint.new()
    if d.has("positions"):
        obj.positions = d["positions"]
    if d.has("velocities"):
        obj.velocities = d["velocities"]
    if d.has("accelerations"):
        obj.accelerations = d["accelerations"]
    if d.has("effort"):
        obj.effort = d["effort"]
    if d.has("time_from_start"):
        obj.time_from_start = DurationScript.from_dict(d["time_from_start"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["positions"] = positions
    d["velocities"] = velocities
    d["accelerations"] = accelerations
    d["effort"] = effort
    d["time_from_start"] = time_from_start.to_dict()
    return d
