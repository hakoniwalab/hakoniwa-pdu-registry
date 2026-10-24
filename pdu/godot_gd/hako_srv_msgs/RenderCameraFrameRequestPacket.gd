class_name HakoPdu_hako_srv_msgs_RenderCameraFrameRequestPacket
extends RefCounted


const PointScript = preload("../geometry_msgs/Point.gd")


const PoseScript = preload("../geometry_msgs/Pose.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const RenderCameraFrameRequestScript = preload("./RenderCameraFrameRequest.gd")


const RenderObjectScript = preload("./RenderObject.gd")


const ServiceRequestHeaderScript = preload("./ServiceRequestHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceRequestHeader = HakoPdu_hako_srv_msgs_ServiceRequestHeader.new()
var body: HakoPdu_hako_srv_msgs_RenderCameraFrameRequest = HakoPdu_hako_srv_msgs_RenderCameraFrameRequest.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_RenderCameraFrameRequestPacket:
    var obj := HakoPdu_hako_srv_msgs_RenderCameraFrameRequestPacket.new()
    if d.has("header"):
        obj.header = ServiceRequestHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = RenderCameraFrameRequestScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
