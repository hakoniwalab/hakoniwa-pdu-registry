class_name HakoPdu_geometry_msgs_AccelWithCovariance
extends RefCounted


const AccelScript = preload("./Accel.gd")


const Vector3Script = preload("./Vector3.gd")


var accel: HakoPdu_geometry_msgs_Accel = HakoPdu_geometry_msgs_Accel.new()
var covariance: PackedFloat64Array = PackedFloat64Array()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_AccelWithCovariance:
    var obj := HakoPdu_geometry_msgs_AccelWithCovariance.new()
    if d.has("accel"):
        obj.accel = AccelScript.from_dict(d["accel"])
    if d.has("covariance"):
        obj.covariance = d["covariance"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["accel"] = accel.to_dict()
    d["covariance"] = covariance
    return d
