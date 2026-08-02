class_name HakoPdu_sample_action_msgs_FibonacciResult
extends RefCounted


var sequence: PackedInt32Array = PackedInt32Array()

static func from_dict(d: Dictionary) -> HakoPdu_sample_action_msgs_FibonacciResult:
    var obj := HakoPdu_sample_action_msgs_FibonacciResult.new()
    if d.has("sequence"):
        obj.sequence = d["sequence"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["sequence"] = sequence
    return d
