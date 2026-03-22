class_name HakoPdu_drone_srv_msgs_DroneGetStateResponsePacket
extends RefCounted


const DroneGetStateResponseScript = preload("./DroneGetStateResponse.gd")


const PointScript = preload("../geometry_msgs/Point.gd")


const PoseScript = preload("../geometry_msgs/Pose.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const HakoBatteryStatusScript = preload("../hako_msgs/HakoBatteryStatus.gd")


const ServiceResponseHeaderScript = preload("../hako_srv_msgs/ServiceResponseHeader.gd")


var header: HakoPdu_hako_srv_msgs_ServiceResponseHeader = HakoPdu_hako_srv_msgs_ServiceResponseHeader.new()
var body: HakoPdu_drone_srv_msgs_DroneGetStateResponse = HakoPdu_drone_srv_msgs_DroneGetStateResponse.new()

static func from_dict(d: Dictionary) -> HakoPdu_drone_srv_msgs_DroneGetStateResponsePacket:
    var obj := HakoPdu_drone_srv_msgs_DroneGetStateResponsePacket.new()
    if d.has("header"):
        obj.header = ServiceResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = DroneGetStateResponseScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
