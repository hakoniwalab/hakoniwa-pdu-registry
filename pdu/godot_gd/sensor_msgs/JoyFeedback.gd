class_name HakoPdu_sensor_msgs_JoyFeedback
extends RefCounted


var type: int = 0
var id: int = 0
var intensity: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_JoyFeedback:
    var obj := HakoPdu_sensor_msgs_JoyFeedback.new()
    if d.has("type"):
        obj.type = d["type"]
    if d.has("id"):
        obj.id = d["id"]
    if d.has("intensity"):
        obj.intensity = d["intensity"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["type"] = type
    d["id"] = id
    d["intensity"] = intensity
    return d
