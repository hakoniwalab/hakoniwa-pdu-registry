class_name HakoPdu_mavros_msgs_AttitudeTarget
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var type_mask: int = 0
var orientation: HakoPdu_geometry_msgs_Quaternion = HakoPdu_geometry_msgs_Quaternion.new()
var body_rate: HakoPdu_geometry_msgs_Vector3 = HakoPdu_geometry_msgs_Vector3.new()
var thrust: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_mavros_msgs_AttitudeTarget:
    var obj := HakoPdu_mavros_msgs_AttitudeTarget.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("type_mask"):
        obj.type_mask = d["type_mask"]
    if d.has("orientation"):
        obj.orientation = QuaternionScript.from_dict(d["orientation"])
    if d.has("body_rate"):
        obj.body_rate = Vector3Script.from_dict(d["body_rate"])
    if d.has("thrust"):
        obj.thrust = d["thrust"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["type_mask"] = type_mask
    d["orientation"] = orientation.to_dict()
    d["body_rate"] = body_rate.to_dict()
    d["thrust"] = thrust
    return d
