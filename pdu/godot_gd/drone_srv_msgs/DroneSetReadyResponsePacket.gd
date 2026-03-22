class_name HakoPdu_drone_srv_msgs_DroneSetReadyResponsePacket
extends RefCounted


const DroneSetReadyResponseScript = preload("./DroneSetReadyResponse.gd")


const ServiceResponseHeaderScript = preload("../hako_srv_msgs/ServiceResponseHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_drone_srv_msgs_DroneSetReadyResponse = HakoPdu_drone_srv_msgs_DroneSetReadyResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_drone_srv_msgs_DroneSetReadyResponsePacket:
    var obj := HakoPdu_drone_srv_msgs_DroneSetReadyResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = DroneSetReadyResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
