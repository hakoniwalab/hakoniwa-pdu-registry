class_name HakoPdu_drone_srv_msgs_DroneGoToRequestPacket
extends RefCounted


const DroneGoToRequestScript = preload("./DroneGoToRequest.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


const ServiceRequestHeaderScript = preload("../hako_srv_msgs/ServiceRequestHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceRequestHeader = HakoPdu_hako_srv_msgs_ServiceRequestHeader.new()
var body: HakoPdu_drone_srv_msgs_DroneGoToRequest = HakoPdu_drone_srv_msgs_DroneGoToRequest.new()

static func from_dict(d: Dictionary) -> HakoPdu_drone_srv_msgs_DroneGoToRequestPacket:
    var obj := HakoPdu_drone_srv_msgs_DroneGoToRequestPacket.new()
    if d.has("header"):
        obj.header = ServiceRequestHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = DroneGoToRequestScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
