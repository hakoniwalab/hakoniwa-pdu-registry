class_name HakoPdu_hako_msgs_HakoCameraData
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const CompressedImageScript = preload("../sensor_msgs/CompressedImage.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var request_id: int = 0
var image: HakoPdu_sensor_msgs_CompressedImage = HakoPdu_sensor_msgs_CompressedImage.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_HakoCameraData:
    var obj := HakoPdu_hako_msgs_HakoCameraData.new()
    if d.has("request_id"):
        obj.request_id = d["request_id"]
    if d.has("image"):
        obj.image = CompressedImageScript.from_dict(d["image"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["request_id"] = request_id
    d["image"] = image.to_dict()
    return d
