class_name HakoPdu_geometry_msgs_AccelStamped
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const AccelScript = preload("./Accel.gd")


const Vector3Script = preload("./Vector3.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var accel: HakoPdu_geometry_msgs_Accel = HakoPdu_geometry_msgs_Accel.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_AccelStamped:
    var obj := HakoPdu_geometry_msgs_AccelStamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("accel"):
        obj.accel = AccelScript.from_dict(d["accel"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["accel"] = accel.to_dict()
    return d
