class_name HakoPdu_nav_msgs_OccupancyGrid
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const PointScript = preload("../geometry_msgs/Point.gd")


const PoseScript = preload("../geometry_msgs/Pose.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const MapMetaDataScript = preload("./MapMetaData.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var info: HakoPdu_nav_msgs_MapMetaData = HakoPdu_nav_msgs_MapMetaData.new()
var data: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_nav_msgs_OccupancyGrid:
    var obj := HakoPdu_nav_msgs_OccupancyGrid.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("info"):
        obj.info = MapMetaDataScript.from_dict(d["info"])
    if d.has("data"):
        obj.data = d["data"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["info"] = info.to_dict()
    d["data"] = data
    return d
