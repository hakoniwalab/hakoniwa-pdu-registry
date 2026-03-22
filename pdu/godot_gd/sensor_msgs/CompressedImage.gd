class_name HakoPdu_sensor_msgs_CompressedImage
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var format: String = ""
var data: PackedByteArray = PackedByteArray()

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_CompressedImage:
    var obj := HakoPdu_sensor_msgs_CompressedImage.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("format"):
        obj.format = d["format"]
    if d.has("data"):
        obj.data = d["data"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["format"] = format
    d["data"] = data
    return d
