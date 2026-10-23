class_name HakoPdu_hako_srv_msgs_RenderCameraFrameResponsePacket
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const RenderCameraFrameResponseScript = preload("./RenderCameraFrameResponse.gd")


const ServiceResponseHeaderScript = preload("./ServiceResponseHeader.gd")


const ImageScript = preload("../sensor_msgs/Image.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_hako_srv_msgs_RenderCameraFrameResponse = HakoPdu_hako_srv_msgs_RenderCameraFrameResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_RenderCameraFrameResponsePacket:
    var obj := HakoPdu_hako_srv_msgs_RenderCameraFrameResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = RenderCameraFrameResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
