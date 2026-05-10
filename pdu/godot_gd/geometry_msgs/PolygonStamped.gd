class_name HakoPdu_geometry_msgs_PolygonStamped
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const Point32Script = preload("./Point32.gd")


const PolygonScript = preload("./Polygon.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var polygon: HakoPdu_geometry_msgs_Polygon = HakoPdu_geometry_msgs_Polygon.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_PolygonStamped:
    var obj := HakoPdu_geometry_msgs_PolygonStamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("polygon"):
        obj.polygon = PolygonScript.from_dict(d["polygon"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["polygon"] = polygon.to_dict()
    return d
