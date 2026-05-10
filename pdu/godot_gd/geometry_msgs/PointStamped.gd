class_name HakoPdu_geometry_msgs_PointStamped
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const PointScript = preload("./Point.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var point: HakoPdu_geometry_msgs_Point = HakoPdu_geometry_msgs_Point.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_PointStamped:
    var obj := HakoPdu_geometry_msgs_PointStamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("point"):
        obj.point = PointScript.from_dict(d["point"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["point"] = point.to_dict()
    return d
