class_name HakoPdu_hako_srv_msgs_RenderCameraFrameResponse
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const ImageScript = preload("../sensor_msgs/Image.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var result_code: int = 0
var sim_time_usec: int = 0
var rgb: HakoPdu_sensor_msgs_Image = HakoPdu_sensor_msgs_Image.new()
var depth: HakoPdu_sensor_msgs_Image = HakoPdu_sensor_msgs_Image.new()
var segmentation: HakoPdu_sensor_msgs_Image = HakoPdu_sensor_msgs_Image.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_RenderCameraFrameResponse:
    var obj := HakoPdu_hako_srv_msgs_RenderCameraFrameResponse.new()
    if d.has("result_code"):
        obj.result_code = d["result_code"]
    if d.has("sim_time_usec"):
        obj.sim_time_usec = d["sim_time_usec"]
    if d.has("rgb"):
        obj.rgb = ImageScript.from_dict(d["rgb"])
    if d.has("depth"):
        obj.depth = ImageScript.from_dict(d["depth"])
    if d.has("segmentation"):
        obj.segmentation = ImageScript.from_dict(d["segmentation"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["result_code"] = result_code
    d["sim_time_usec"] = sim_time_usec
    d["rgb"] = rgb.to_dict()
    d["depth"] = depth.to_dict()
    d["segmentation"] = segmentation.to_dict()
    return d
