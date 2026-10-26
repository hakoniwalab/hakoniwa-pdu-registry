class_name HakoPdu_hako_srv_msgs_AckermannStepResponsePacket
extends RefCounted


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const TransformScript = preload("../geometry_msgs/Transform.gd")


const TwistScript = preload("../geometry_msgs/Twist.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


const AckermannStepResponseScript = preload("./AckermannStepResponse.gd")


const ServiceResponseHeaderScript = preload("./ServiceResponseHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_hako_srv_msgs_AckermannStepResponse = HakoPdu_hako_srv_msgs_AckermannStepResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_AckermannStepResponsePacket:
    var obj := HakoPdu_hako_srv_msgs_AckermannStepResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = AckermannStepResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
