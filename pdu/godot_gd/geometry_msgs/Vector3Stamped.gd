class_name HakoPdu_geometry_msgs_Vector3Stamped
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const Vector3Script = preload("./Vector3.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var vector: HakoPdu_geometry_msgs_Vector3 = HakoPdu_geometry_msgs_Vector3.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_Vector3Stamped:
    var obj := HakoPdu_geometry_msgs_Vector3Stamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("vector"):
        obj.vector = Vector3Script.from_dict(d["vector"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["vector"] = vector.to_dict()
    return d
