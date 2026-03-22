class_name HakoPdu_hako_srv_msgs_SimControlRequestPacket
extends RefCounted


const ServiceRequestHeaderScript = preload("./ServiceRequestHeader.gd")


const SimControlRequestScript = preload("./SimControlRequest.gd")


var header: HakoPdu_hako_srv_msgs_ServiceRequestHeader = HakoPdu_hako_srv_msgs_ServiceRequestHeader.new()
var body: HakoPdu_hako_srv_msgs_SimControlRequest = HakoPdu_hako_srv_msgs_SimControlRequest.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_SimControlRequestPacket:
    var obj := HakoPdu_hako_srv_msgs_SimControlRequestPacket.new()
    if d.has("header"):
        obj.header = ServiceRequestHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = SimControlRequestScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
