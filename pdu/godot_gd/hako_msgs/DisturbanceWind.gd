class_name HakoPdu_hako_msgs_DisturbanceWind
extends RefCounted


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


var value: HakoPdu_geometry_msgs_Vector3 = HakoPdu_geometry_msgs_Vector3.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_DisturbanceWind:
    var obj := HakoPdu_hako_msgs_DisturbanceWind.new()
    if d.has("value"):
        obj.value = Vector3Script.from_dict(d["value"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["value"] = value.to_dict()
    return d
