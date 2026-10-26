class_name HakoPdu_hako_srv_msgs_SetLightRequest
extends RefCounted


var source: String = ""
var mode: int = 0
var luminous_intensity_scale: float = 0.0
var flashing_on_s: float = 0.0
var flashing_off_s: float = 0.0
var transition_s: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_SetLightRequest:
    var obj := HakoPdu_hako_srv_msgs_SetLightRequest.new()
    if d.has("source"):
        obj.source = d["source"]
    if d.has("mode"):
        obj.mode = d["mode"]
    if d.has("luminous_intensity_scale"):
        obj.luminous_intensity_scale = d["luminous_intensity_scale"]
    if d.has("flashing_on_s"):
        obj.flashing_on_s = d["flashing_on_s"]
    if d.has("flashing_off_s"):
        obj.flashing_off_s = d["flashing_off_s"]
    if d.has("transition_s"):
        obj.transition_s = d["transition_s"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["source"] = source
    d["mode"] = mode
    d["luminous_intensity_scale"] = luminous_intensity_scale
    d["flashing_on_s"] = flashing_on_s
    d["flashing_off_s"] = flashing_off_s
    d["transition_s"] = transition_s
    return d
