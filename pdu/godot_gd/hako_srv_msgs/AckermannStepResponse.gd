class_name HakoPdu_hako_srv_msgs_AckermannStepResponse
extends RefCounted


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const TransformScript = preload("../geometry_msgs/Transform.gd")


const TwistScript = preload("../geometry_msgs/Twist.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


var step: int = 0
var result_code: int = 0
var sim_time_usec: int = 0
var pose: HakoPdu_geometry_msgs_Transform = HakoPdu_geometry_msgs_Transform.new()
var twist: HakoPdu_geometry_msgs_Twist = HakoPdu_geometry_msgs_Twist.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_AckermannStepResponse:
    var obj := HakoPdu_hako_srv_msgs_AckermannStepResponse.new()
    if d.has("step"):
        obj.step = d["step"]
    if d.has("result_code"):
        obj.result_code = d["result_code"]
    if d.has("sim_time_usec"):
        obj.sim_time_usec = d["sim_time_usec"]
    if d.has("pose"):
        obj.pose = TransformScript.from_dict(d["pose"])
    if d.has("twist"):
        obj.twist = TwistScript.from_dict(d["twist"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["step"] = step
    d["result_code"] = result_code
    d["sim_time_usec"] = sim_time_usec
    d["pose"] = pose.to_dict()
    d["twist"] = twist.to_dict()
    return d
