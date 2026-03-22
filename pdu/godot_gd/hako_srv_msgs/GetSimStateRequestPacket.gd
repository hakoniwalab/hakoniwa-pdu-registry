class_name HakoPdu_hako_srv_msgs_GetSimStateRequestPacket
extends RefCounted


const GetSimStateRequestScript = preload("./GetSimStateRequest.gd")


const ServiceRequestHeaderScript = preload("./ServiceRequestHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceRequestHeader = HakoPdu_hako_srv_msgs_ServiceRequestHeader.new()
var body: HakoPdu_hako_srv_msgs_GetSimStateRequest = HakoPdu_hako_srv_msgs_GetSimStateRequest.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_GetSimStateRequestPacket:
    var obj := HakoPdu_hako_srv_msgs_GetSimStateRequestPacket.new()
    if d.has("header"):
        obj.header = ServiceRequestHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = GetSimStateRequestScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
