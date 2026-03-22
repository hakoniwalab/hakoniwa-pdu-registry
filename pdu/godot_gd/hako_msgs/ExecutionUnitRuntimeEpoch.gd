class_name HakoPdu_hako_msgs_ExecutionUnitRuntimeEpoch
extends RefCounted


var epoch: PackedByteArray = PackedByteArray()

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_ExecutionUnitRuntimeEpoch:
    var obj := HakoPdu_hako_msgs_ExecutionUnitRuntimeEpoch.new()
    if d.has("epoch"):
        obj.epoch = d["epoch"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["epoch"] = epoch
    return d
