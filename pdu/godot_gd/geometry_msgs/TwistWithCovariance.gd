class_name HakoPdu_geometry_msgs_TwistWithCovariance
extends RefCounted


const TwistScript = preload("./Twist.gd")


const Vector3Script = preload("./Vector3.gd")


var twist: HakoPdu_geometry_msgs_Twist = HakoPdu_geometry_msgs_Twist.new()
var covariance: PackedFloat64Array = PackedFloat64Array()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_TwistWithCovariance:
    var obj := HakoPdu_geometry_msgs_TwistWithCovariance.new()
    if d.has("twist"):
        obj.twist = TwistScript.from_dict(d["twist"])
    if d.has("covariance"):
        obj.covariance = d["covariance"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["twist"] = twist.to_dict()
    d["covariance"] = covariance
    return d
