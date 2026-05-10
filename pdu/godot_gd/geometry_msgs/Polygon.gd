class_name HakoPdu_geometry_msgs_Polygon
extends RefCounted


const Point32Script = preload("./Point32.gd")


var points: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_Polygon:
    var obj := HakoPdu_geometry_msgs_Polygon.new()
    if d.has("points"):
        obj.points = []
        for item in d["points"]:
            obj.points.append(Point32Script.from_dict(item))
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    var points_array: Array = []
    for item in points:
        points_array.append(item.to_dict())
    d["points"] = points_array
    return d
