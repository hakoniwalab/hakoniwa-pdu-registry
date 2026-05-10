class_name HakoPdu_sensor_msgs_LaserEcho
extends RefCounted


var echoes: PackedFloat32Array = PackedFloat32Array()

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_LaserEcho:
    var obj := HakoPdu_sensor_msgs_LaserEcho.new()
    if d.has("echoes"):
        obj.echoes = d["echoes"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["echoes"] = echoes
    return d
