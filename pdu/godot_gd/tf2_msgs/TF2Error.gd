class_name HakoPdu_tf2_msgs_TF2Error
extends RefCounted


var error: int = 0
var error_string: String = ""

static func from_dict(d: Dictionary) -> HakoPdu_tf2_msgs_TF2Error:
    var obj := HakoPdu_tf2_msgs_TF2Error.new()
    if d.has("error"):
        obj.error = d["error"]
    if d.has("error_string"):
        obj.error_string = d["error_string"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["error"] = error
    d["error_string"] = error_string
    return d
