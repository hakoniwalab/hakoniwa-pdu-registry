class_name HakoPdu_hako_srv_msgs_PersonStepResponse
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const TransformScript = preload("../geometry_msgs/Transform.gd")


const TwistScript = preload("../geometry_msgs/Twist.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


const JointStateScript = preload("../sensor_msgs/JointState.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var step: int = 0
var result_code: int = 0
var sim_time_usec: int = 0
var pose: HakoPdu_geometry_msgs_Transform = HakoPdu_geometry_msgs_Transform.new()
var twist: HakoPdu_geometry_msgs_Twist = HakoPdu_geometry_msgs_Twist.new()
var joints: HakoPdu_sensor_msgs_JointState = HakoPdu_sensor_msgs_JointState.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_PersonStepResponse:
    var obj := HakoPdu_hako_srv_msgs_PersonStepResponse.new()
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
    if d.has("joints"):
        obj.joints = JointStateScript.from_dict(d["joints"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["step"] = step
    d["result_code"] = result_code
    d["sim_time_usec"] = sim_time_usec
    d["pose"] = pose.to_dict()
    d["twist"] = twist.to_dict()
    d["joints"] = joints.to_dict()
    return d
