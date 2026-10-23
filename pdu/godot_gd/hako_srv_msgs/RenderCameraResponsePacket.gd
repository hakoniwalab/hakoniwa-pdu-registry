class_name HakoPdu_hako_srv_msgs_RenderCameraResponsePacket
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const RenderCameraResponseScript = preload("./RenderCameraResponse.gd")


const ServiceResponseHeaderScript = preload("./ServiceResponseHeader.gd")


const ImageScript = preload("../sensor_msgs/Image.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_hako_srv_msgs_RenderCameraResponse = HakoPdu_hako_srv_msgs_RenderCameraResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_RenderCameraResponsePacket:
    var obj := HakoPdu_hako_srv_msgs_RenderCameraResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = RenderCameraResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
