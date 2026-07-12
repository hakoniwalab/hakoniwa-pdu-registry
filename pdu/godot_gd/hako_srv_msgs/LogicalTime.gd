class_name HakoPdu_hako_srv_msgs_LogicalTime
extends RefCounted


var generation: int = 0
var offset_tick: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_LogicalTime:
    var obj := HakoPdu_hako_srv_msgs_LogicalTime.new()
    if d.has("generation"):
        obj.generation = d["generation"]
    if d.has("offset_tick"):
        obj.offset_tick = d["offset_tick"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["generation"] = generation
    d["offset_tick"] = offset_tick
    return d
