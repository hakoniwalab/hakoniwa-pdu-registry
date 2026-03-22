class_name HakoPdu_hako_srv_msgs_GetSimStateResponsePacket
extends RefCounted


const GetSimStateResponseScript = preload("./GetSimStateResponse.gd")


const ServiceResponseHeaderScript = preload("./ServiceResponseHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_hako_srv_msgs_GetSimStateResponse = HakoPdu_hako_srv_msgs_GetSimStateResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_GetSimStateResponsePacket:
    var obj := HakoPdu_hako_srv_msgs_GetSimStateResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = GetSimStateResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
