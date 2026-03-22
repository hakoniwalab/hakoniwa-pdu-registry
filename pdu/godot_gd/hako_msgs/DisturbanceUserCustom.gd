class_name HakoPdu_hako_msgs_DisturbanceUserCustom
extends RefCounted


var data: PackedFloat64Array = PackedFloat64Array()

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_DisturbanceUserCustom:
    var obj := HakoPdu_hako_msgs_DisturbanceUserCustom.new()
    if d.has("data"):
        obj.data = d["data"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["data"] = data
    return d
