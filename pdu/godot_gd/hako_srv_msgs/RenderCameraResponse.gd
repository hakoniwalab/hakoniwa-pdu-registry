class_name HakoPdu_hako_srv_msgs_RenderCameraResponse
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const ImageScript = preload("../sensor_msgs/Image.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var result_code: int = 0
var sim_time_usec: int = 0
var image: HakoPdu_sensor_msgs_Image = HakoPdu_sensor_msgs_Image.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_RenderCameraResponse:
    var obj := HakoPdu_hako_srv_msgs_RenderCameraResponse.new()
    if d.has("result_code"):
        obj.result_code = d["result_code"]
    if d.has("sim_time_usec"):
        obj.sim_time_usec = d["sim_time_usec"]
    if d.has("image"):
        obj.image = ImageScript.from_dict(d["image"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["result_code"] = result_code
    d["sim_time_usec"] = sim_time_usec
    d["image"] = image.to_dict()
    return d
