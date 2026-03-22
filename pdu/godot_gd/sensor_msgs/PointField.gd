class_name HakoPdu_sensor_msgs_PointField
extends RefCounted


var name: String = ""
var offset: int = 0
var datatype: int = 0
var count: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_PointField:
    var obj := HakoPdu_sensor_msgs_PointField.new()
    if d.has("name"):
        obj.name = d["name"]
    if d.has("offset"):
        obj.offset = d["offset"]
    if d.has("datatype"):
        obj.datatype = d["datatype"]
    if d.has("count"):
        obj.count = d["count"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["name"] = name
    d["offset"] = offset
    d["datatype"] = datatype
    d["count"] = count
    return d
