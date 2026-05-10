class_name HakoPdu_geometry_msgs_AccelWithCovarianceStamped
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const AccelScript = preload("./Accel.gd")


const AccelWithCovarianceScript = preload("./AccelWithCovariance.gd")


const Vector3Script = preload("./Vector3.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var accel: HakoPdu_geometry_msgs_AccelWithCovariance = HakoPdu_geometry_msgs_AccelWithCovariance.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_AccelWithCovarianceStamped:
    var obj := HakoPdu_geometry_msgs_AccelWithCovarianceStamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("accel"):
        obj.accel = AccelWithCovarianceScript.from_dict(d["accel"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["accel"] = accel.to_dict()
    return d
