class_name HakoPdu_sensor_msgs_PointCloud
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const Point32Script = preload("../geometry_msgs/Point32.gd")


const ChannelFloat32Script = preload("./ChannelFloat32.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var points: Array = []
var channels: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_PointCloud:
    var obj := HakoPdu_sensor_msgs_PointCloud.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("points"):
        obj.points = []
        for item in d["points"]:
            obj.points.append(Point32Script.from_dict(item))
    if d.has("channels"):
        obj.channels = []
        for item in d["channels"]:
            obj.channels.append(ChannelFloat32Script.from_dict(item))
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    var points_array: Array = []
    for item in points:
        points_array.append(item.to_dict())
    d["points"] = points_array
    var channels_array: Array = []
    for item in channels:
        channels_array.append(item.to_dict())
    d["channels"] = channels_array
    return d
