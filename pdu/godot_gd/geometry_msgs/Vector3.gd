class_name HakoPdu_geometry_msgs_Vector3
extends RefCounted


var x: float = 0.0
var y: float = 0.0
var z: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_Vector3:
    var obj := HakoPdu_geometry_msgs_Vector3.new()
    if d.has("x"):
        obj.x = d["x"]
    if d.has("y"):
        obj.y = d["y"]
    if d.has("z"):
        obj.z = d["z"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["x"] = x
    d["y"] = y
    d["z"] = z
    return d
