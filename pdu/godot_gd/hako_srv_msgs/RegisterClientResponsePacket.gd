class_name HakoPdu_hako_srv_msgs_RegisterClientResponsePacket
extends RefCounted


const RegisterClientResponseScript = preload("./RegisterClientResponse.gd")


const ServiceResponseHeaderScript = preload("./ServiceResponseHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_hako_srv_msgs_RegisterClientResponse = HakoPdu_hako_srv_msgs_RegisterClientResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_RegisterClientResponsePacket:
    var obj := HakoPdu_hako_srv_msgs_RegisterClientResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = RegisterClientResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
