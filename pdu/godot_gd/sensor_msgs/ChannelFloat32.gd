class_name HakoPdu_sensor_msgs_ChannelFloat32
extends RefCounted


var name: String = ""
var values: PackedFloat32Array = PackedFloat32Array()

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_ChannelFloat32:
    var obj := HakoPdu_sensor_msgs_ChannelFloat32.new()
    if d.has("name"):
        obj.name = d["name"]
    if d.has("values"):
        obj.values = d["values"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["name"] = name
    d["values"] = values
    return d
