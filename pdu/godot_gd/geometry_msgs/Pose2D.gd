class_name HakoPdu_geometry_msgs_Pose2D
extends RefCounted


var x: float = 0.0
var y: float = 0.0
var theta: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_Pose2D:
    var obj := HakoPdu_geometry_msgs_Pose2D.new()
    if d.has("x"):
        obj.x = d["x"]
    if d.has("y"):
        obj.y = d["y"]
    if d.has("theta"):
        obj.theta = d["theta"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["x"] = x
    d["y"] = y
    d["theta"] = theta
    return d
