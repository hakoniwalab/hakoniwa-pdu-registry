class_name HakoPdu_hako_msgs_DisturbanceAtm
extends RefCounted


var sea_level_atm: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_DisturbanceAtm:
    var obj := HakoPdu_hako_msgs_DisturbanceAtm.new()
    if d.has("sea_level_atm"):
        obj.sea_level_atm = d["sea_level_atm"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["sea_level_atm"] = sea_level_atm
    return d
