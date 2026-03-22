class_name HakoPdu_drone_srv_msgs_MagnetGrabRequestPacket
extends RefCounted


const MagnetGrabRequestScript = preload("./MagnetGrabRequest.gd")


const ServiceRequestHeaderScript = preload("../hako_srv_msgs/ServiceRequestHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceRequestHeader = HakoPdu_hako_srv_msgs_ServiceRequestHeader.new()
var body: HakoPdu_drone_srv_msgs_MagnetGrabRequest = HakoPdu_drone_srv_msgs_MagnetGrabRequest.new()

static func from_dict(d: Dictionary) -> HakoPdu_drone_srv_msgs_MagnetGrabRequestPacket:
    var obj := HakoPdu_drone_srv_msgs_MagnetGrabRequestPacket.new()
    if d.has("header"):
        obj.header = ServiceRequestHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = MagnetGrabRequestScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
