class_name HakoPdu_nav_msgs_MapMetaData
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const PointScript = preload("../geometry_msgs/Point.gd")


const PoseScript = preload("../geometry_msgs/Pose.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


var map_load_time: HakoPdu_builtin_interfaces_Time = HakoPdu_builtin_interfaces_Time.new()
var resolution: float = 0.0
var width: int = 0
var height: int = 0
var origin: HakoPdu_geometry_msgs_Pose = HakoPdu_geometry_msgs_Pose.new()

static func from_dict(d: Dictionary) -> HakoPdu_nav_msgs_MapMetaData:
    var obj := HakoPdu_nav_msgs_MapMetaData.new()
    if d.has("map_load_time"):
        obj.map_load_time = TimeScript.from_dict(d["map_load_time"])
    if d.has("resolution"):
        obj.resolution = d["resolution"]
    if d.has("width"):
        obj.width = d["width"]
    if d.has("height"):
        obj.height = d["height"]
    if d.has("origin"):
        obj.origin = PoseScript.from_dict(d["origin"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["map_load_time"] = map_load_time.to_dict()
    d["resolution"] = resolution
    d["width"] = width
    d["height"] = height
    d["origin"] = origin.to_dict()
    return d
