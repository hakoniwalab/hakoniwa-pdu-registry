class_name HakoPdu_hako_srv_msgs_GetEventRequestPacket
extends RefCounted


const GetEventRequestScript = preload("./GetEventRequest.gd")


const ServiceRequestHeaderScript = preload("./ServiceRequestHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceRequestHeader = HakoPdu_hako_srv_msgs_ServiceRequestHeader.new()
var body: HakoPdu_hako_srv_msgs_GetEventRequest = HakoPdu_hako_srv_msgs_GetEventRequest.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_GetEventRequestPacket:
    var obj := HakoPdu_hako_srv_msgs_GetEventRequestPacket.new()
    if d.has("header"):
        obj.header = ServiceRequestHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = GetEventRequestScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
