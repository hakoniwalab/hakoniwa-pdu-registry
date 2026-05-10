class_name HakoPdu_geometry_msgs_TwistStamped
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const TwistScript = preload("./Twist.gd")


const Vector3Script = preload("./Vector3.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var twist: HakoPdu_geometry_msgs_Twist = HakoPdu_geometry_msgs_Twist.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_TwistStamped:
    var obj := HakoPdu_geometry_msgs_TwistStamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("twist"):
        obj.twist = TwistScript.from_dict(d["twist"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["twist"] = twist.to_dict()
    return d
