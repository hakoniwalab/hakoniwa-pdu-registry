class_name HakoPdu_std_msgs_ColorRGBA
extends RefCounted


var r: float = 0.0
var g: float = 0.0
var b: float = 0.0
var a: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_std_msgs_ColorRGBA:
    var obj := HakoPdu_std_msgs_ColorRGBA.new()
    if d.has("r"):
        obj.r = d["r"]
    if d.has("g"):
        obj.g = d["g"]
    if d.has("b"):
        obj.b = d["b"]
    if d.has("a"):
        obj.a = d["a"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["r"] = r
    d["g"] = g
    d["b"] = b
    d["a"] = a
    return d
