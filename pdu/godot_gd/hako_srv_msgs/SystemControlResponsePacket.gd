class_name HakoPdu_hako_srv_msgs_SystemControlResponsePacket
extends RefCounted


const ServiceResponseHeaderScript = preload("./ServiceResponseHeader.gd")


const SystemControlResponseScript = preload("./SystemControlResponse.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_hako_srv_msgs_SystemControlResponse = HakoPdu_hako_srv_msgs_SystemControlResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_SystemControlResponsePacket:
    var obj := HakoPdu_hako_srv_msgs_SystemControlResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = SystemControlResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
