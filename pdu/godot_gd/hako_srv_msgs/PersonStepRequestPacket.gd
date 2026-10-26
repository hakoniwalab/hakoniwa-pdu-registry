class_name HakoPdu_hako_srv_msgs_PersonStepRequestPacket
extends RefCounted


const TwistScript = preload("../geometry_msgs/Twist.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


const PersonStepRequestScript = preload("./PersonStepRequest.gd")


const ServiceRequestHeaderScript = preload("./ServiceRequestHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceRequestHeader = HakoPdu_hako_srv_msgs_ServiceRequestHeader.new()
var body: HakoPdu_hako_srv_msgs_PersonStepRequest = HakoPdu_hako_srv_msgs_PersonStepRequest.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_PersonStepRequestPacket:
    var obj := HakoPdu_hako_srv_msgs_PersonStepRequestPacket.new()
    if d.has("header"):
        obj.header = ServiceRequestHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = PersonStepRequestScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
