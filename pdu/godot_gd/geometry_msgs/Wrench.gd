class_name HakoPdu_geometry_msgs_Wrench
extends RefCounted


const Vector3Script = preload("./Vector3.gd")


var force: HakoPdu_geometry_msgs_Vector3 = HakoPdu_geometry_msgs_Vector3.new()
var torque: HakoPdu_geometry_msgs_Vector3 = HakoPdu_geometry_msgs_Vector3.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_Wrench:
    var obj := HakoPdu_geometry_msgs_Wrench.new()
    if d.has("force"):
        obj.force = Vector3Script.from_dict(d["force"])
    if d.has("torque"):
        obj.torque = Vector3Script.from_dict(d["torque"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["force"] = force.to_dict()
    d["torque"] = torque.to_dict()
    return d
