class_name HakoPdu_sensor_msgs_JoyFeedbackArray
extends RefCounted


const JoyFeedbackScript = preload("./JoyFeedback.gd")


var array: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_JoyFeedbackArray:
    var obj := HakoPdu_sensor_msgs_JoyFeedbackArray.new()
    if d.has("array"):
        obj.array = []
        for item in d["array"]:
            obj.array.append(JoyFeedbackScript.from_dict(item))
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    var array_array: Array = []
    for item in array:
        array_array.append(item.to_dict())
    d["array"] = array_array
    return d
