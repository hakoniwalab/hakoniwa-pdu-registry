class_name HakoPdu_geometry_msgs_Transform
extends RefCounted


const QuaternionScript = preload("./Quaternion.gd")


const Vector3Script = preload("./Vector3.gd")


var translation: HakoPdu_geometry_msgs_Vector3 = HakoPdu_geometry_msgs_Vector3.new()
var rotation: HakoPdu_geometry_msgs_Quaternion = HakoPdu_geometry_msgs_Quaternion.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_Transform:
    var obj := HakoPdu_geometry_msgs_Transform.new()
    if d.has("translation"):
        obj.translation = Vector3Script.from_dict(d["translation"])
    if d.has("rotation"):
        obj.rotation = QuaternionScript.from_dict(d["rotation"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["translation"] = translation.to_dict()
    d["rotation"] = rotation.to_dict()
    return d
