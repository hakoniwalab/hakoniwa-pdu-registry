class_name HakoPdu_sample_action_msgs_FibonacciGoal
extends RefCounted


var order: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_sample_action_msgs_FibonacciGoal:
    var obj := HakoPdu_sample_action_msgs_FibonacciGoal.new()
    if d.has("order"):
        obj.order = d["order"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["order"] = order
    return d
