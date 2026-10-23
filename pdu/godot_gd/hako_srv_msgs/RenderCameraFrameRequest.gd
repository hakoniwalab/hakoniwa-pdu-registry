class_name HakoPdu_hako_srv_msgs_RenderCameraFrameRequest
extends RefCounted


const PointScript = preload("../geometry_msgs/Point.gd")


const PoseScript = preload("../geometry_msgs/Pose.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


var camera_name: String = ""
var sim_time_usec: int = 0
var camera_pose: HakoPdu_geometry_msgs_Pose = HakoPdu_geometry_msgs_Pose.new()
var outputs: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_RenderCameraFrameRequest:
    var obj := HakoPdu_hako_srv_msgs_RenderCameraFrameRequest.new()
    if d.has("camera_name"):
        obj.camera_name = d["camera_name"]
    if d.has("sim_time_usec"):
        obj.sim_time_usec = d["sim_time_usec"]
    if d.has("camera_pose"):
        obj.camera_pose = PoseScript.from_dict(d["camera_pose"])
    if d.has("outputs"):
        obj.outputs = d["outputs"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["camera_name"] = camera_name
    d["sim_time_usec"] = sim_time_usec
    d["camera_pose"] = camera_pose.to_dict()
    d["outputs"] = outputs
    return d
