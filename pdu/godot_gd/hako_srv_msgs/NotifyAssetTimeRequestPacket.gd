class_name HakoPdu_hako_srv_msgs_NotifyAssetTimeRequestPacket
extends RefCounted


const LogicalTimeScript = preload("./LogicalTime.gd")


const NotifyAssetTimeRequestScript = preload("./NotifyAssetTimeRequest.gd")


const ServiceRequestHeaderScript = preload("./ServiceRequestHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceRequestHeader = HakoPdu_hako_srv_msgs_ServiceRequestHeader.new()
var body: HakoPdu_hako_srv_msgs_NotifyAssetTimeRequest = HakoPdu_hako_srv_msgs_NotifyAssetTimeRequest.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_NotifyAssetTimeRequestPacket:
    var obj := HakoPdu_hako_srv_msgs_NotifyAssetTimeRequestPacket.new()
    if d.has("header"):
        obj.header = ServiceRequestHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = NotifyAssetTimeRequestScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
