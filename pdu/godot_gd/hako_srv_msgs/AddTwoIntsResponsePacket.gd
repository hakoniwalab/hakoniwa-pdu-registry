class_name HakoPdu_hako_srv_msgs_AddTwoIntsResponsePacket
extends RefCounted


const AddTwoIntsResponseScript = preload("./AddTwoIntsResponse.gd")


const ServiceResponseHeaderScript = preload("./ServiceResponseHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_hako_srv_msgs_AddTwoIntsResponse = HakoPdu_hako_srv_msgs_AddTwoIntsResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_AddTwoIntsResponsePacket:
    var obj := HakoPdu_hako_srv_msgs_AddTwoIntsResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = AddTwoIntsResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
