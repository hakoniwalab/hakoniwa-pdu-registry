class_name HakoPdu_sample_action_msgs_FibonacciFeedback
extends RefCounted


var partial_sequence: PackedInt32Array = PackedInt32Array()

static func from_dict(d: Dictionary) -> HakoPdu_sample_action_msgs_FibonacciFeedback:
    var obj := HakoPdu_sample_action_msgs_FibonacciFeedback.new()
    if d.has("partial_sequence"):
        obj.partial_sequence = d["partial_sequence"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["partial_sequence"] = partial_sequence
    return d
