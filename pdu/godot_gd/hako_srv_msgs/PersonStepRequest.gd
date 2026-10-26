class_name HakoPdu_hako_srv_msgs_PersonStepRequest
extends RefCounted


const TwistScript = preload("../geometry_msgs/Twist.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


var step: int = 0
var cmd_vel: HakoPdu_geometry_msgs_Twist = HakoPdu_geometry_msgs_Twist.new()
var animation: String = ""
var ride: String = ""

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_PersonStepRequest:
    var obj := HakoPdu_hako_srv_msgs_PersonStepRequest.new()
    if d.has("step"):
        obj.step = d["step"]
    if d.has("cmd_vel"):
        obj.cmd_vel = TwistScript.from_dict(d["cmd_vel"])
    if d.has("animation"):
        obj.animation = d["animation"]
    if d.has("ride"):
        obj.ride = d["ride"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["step"] = step
    d["cmd_vel"] = cmd_vel.to_dict()
    d["animation"] = animation
    d["ride"] = ride
    return d
