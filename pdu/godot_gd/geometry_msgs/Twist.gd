class_name HakoPdu_geometry_msgs_Twist
extends RefCounted


const Vector3Script = preload("./Vector3.gd")


var linear: HakoPdu_geometry_msgs_Vector3 = HakoPdu_geometry_msgs_Vector3.new()
var angular: HakoPdu_geometry_msgs_Vector3 = HakoPdu_geometry_msgs_Vector3.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_Twist:
    var obj := HakoPdu_geometry_msgs_Twist.new()
    if d.has("linear"):
        obj.linear = Vector3Script.from_dict(d["linear"])
    if d.has("angular"):
        obj.angular = Vector3Script.from_dict(d["angular"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["linear"] = linear.to_dict()
    d["angular"] = angular.to_dict()
    return d
