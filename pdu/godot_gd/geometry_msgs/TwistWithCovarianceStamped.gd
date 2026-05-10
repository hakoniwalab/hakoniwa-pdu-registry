class_name HakoPdu_geometry_msgs_TwistWithCovarianceStamped
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const TwistScript = preload("./Twist.gd")


const TwistWithCovarianceScript = preload("./TwistWithCovariance.gd")


const Vector3Script = preload("./Vector3.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var twist: HakoPdu_geometry_msgs_TwistWithCovariance = HakoPdu_geometry_msgs_TwistWithCovariance.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_TwistWithCovarianceStamped:
    var obj := HakoPdu_geometry_msgs_TwistWithCovarianceStamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("twist"):
        obj.twist = TwistWithCovarianceScript.from_dict(d["twist"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["twist"] = twist.to_dict()
    return d
