class_name HakoPdu_hako_msgs_LightState
extends RefCounted


var source: String = ""
var mode: int = 0
var luminous_intensity_scale: float = 0.0
var is_lit: bool = false

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_LightState:
    var obj := HakoPdu_hako_msgs_LightState.new()
    if d.has("source"):
        obj.source = d["source"]
    if d.has("mode"):
        obj.mode = d["mode"]
    if d.has("luminous_intensity_scale"):
        obj.luminous_intensity_scale = d["luminous_intensity_scale"]
    if d.has("is_lit"):
        obj.is_lit = d["is_lit"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["source"] = source
    d["mode"] = mode
    d["luminous_intensity_scale"] = luminous_intensity_scale
    d["is_lit"] = is_lit
    return d
