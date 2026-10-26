class_name HakoPdu_hako_srv_msgs_SetLightResponsePacket
extends RefCounted


const ServiceResponseHeaderScript = preload("./ServiceResponseHeader.gd")


const SetLightResponseScript = preload("./SetLightResponse.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_hako_srv_msgs_SetLightResponse = HakoPdu_hako_srv_msgs_SetLightResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_SetLightResponsePacket:
    var obj := HakoPdu_hako_srv_msgs_SetLightResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = SetLightResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
