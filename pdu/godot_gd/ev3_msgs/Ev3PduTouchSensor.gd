class_name HakoPdu_ev3_msgs_Ev3PduTouchSensor
extends RefCounted


var value: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_ev3_msgs_Ev3PduTouchSensor:
    var obj := HakoPdu_ev3_msgs_Ev3PduTouchSensor.new()
    if d.has("value"):
        obj.value = d["value"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["value"] = value
    return d
