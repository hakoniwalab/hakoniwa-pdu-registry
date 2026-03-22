class_name HakoPdu_hako_msgs_ExecutionUnitRuntimeNode
extends RefCounted


var node_id: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_ExecutionUnitRuntimeNode:
    var obj := HakoPdu_hako_msgs_ExecutionUnitRuntimeNode.new()
    if d.has("node_id"):
        obj.node_id = d["node_id"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["node_id"] = node_id
    return d
