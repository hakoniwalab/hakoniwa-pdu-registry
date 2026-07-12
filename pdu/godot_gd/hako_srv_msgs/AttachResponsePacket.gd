class_name HakoPdu_hako_srv_msgs_AttachResponsePacket
extends RefCounted


const AttachResponseScript = preload("./AttachResponse.gd")


const LogicalTimeScript = preload("./LogicalTime.gd")


const ServiceResponseHeaderScript = preload("./ServiceResponseHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_hako_srv_msgs_AttachResponse = HakoPdu_hako_srv_msgs_AttachResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_AttachResponsePacket:
    var obj := HakoPdu_hako_srv_msgs_AttachResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = AttachResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
