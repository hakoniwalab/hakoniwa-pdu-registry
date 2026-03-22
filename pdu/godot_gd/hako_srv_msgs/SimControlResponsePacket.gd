class_name HakoPdu_hako_srv_msgs_SimControlResponsePacket
extends RefCounted


const ServiceResponseHeaderScript = preload("./ServiceResponseHeader.gd")


const SimControlResponseScript = preload("./SimControlResponse.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_hako_srv_msgs_SimControlResponse = HakoPdu_hako_srv_msgs_SimControlResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_SimControlResponsePacket:
    var obj := HakoPdu_hako_srv_msgs_SimControlResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = SimControlResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
