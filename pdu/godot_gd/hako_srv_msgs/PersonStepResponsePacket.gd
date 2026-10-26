class_name HakoPdu_hako_srv_msgs_PersonStepResponsePacket
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const TransformScript = preload("../geometry_msgs/Transform.gd")


const TwistScript = preload("../geometry_msgs/Twist.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


const PersonStepResponseScript = preload("./PersonStepResponse.gd")


const ServiceResponseHeaderScript = preload("./ServiceResponseHeader.gd")


const JointStateScript = preload("../sensor_msgs/JointState.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_hako_srv_msgs_PersonStepResponse = HakoPdu_hako_srv_msgs_PersonStepResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_PersonStepResponsePacket:
    var obj := HakoPdu_hako_srv_msgs_PersonStepResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = PersonStepResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
