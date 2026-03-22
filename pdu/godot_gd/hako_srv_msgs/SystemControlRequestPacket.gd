class_name HakoPdu_hako_srv_msgs_SystemControlRequestPacket
extends RefCounted


const ServiceRequestHeaderScript = preload("./ServiceRequestHeader.gd")


const SystemControlRequestScript = preload("./SystemControlRequest.gd")


var header: HakoPdu_hako_srv_msgs_ServiceRequestHeader = HakoPdu_hako_srv_msgs_ServiceRequestHeader.new()
var body: HakoPdu_hako_srv_msgs_SystemControlRequest = HakoPdu_hako_srv_msgs_SystemControlRequest.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_SystemControlRequestPacket:
    var obj := HakoPdu_hako_srv_msgs_SystemControlRequestPacket.new()
    if d.has("header"):
        obj.header = ServiceRequestHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = SystemControlRequestScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
