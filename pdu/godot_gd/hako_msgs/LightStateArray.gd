class_name HakoPdu_hako_msgs_LightStateArray
extends RefCounted


const LightStateScript = preload("./LightState.gd")


var stamp_usec: int = 0
var carrier: String = ""
var lights: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_LightStateArray:
    var obj := HakoPdu_hako_msgs_LightStateArray.new()
    if d.has("stamp_usec"):
        obj.stamp_usec = d["stamp_usec"]
    if d.has("carrier"):
        obj.carrier = d["carrier"]
    if d.has("lights"):
        obj.lights = []
        for item in d["lights"]:
            obj.lights.append(LightStateScript.from_dict(item))
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["stamp_usec"] = stamp_usec
    d["carrier"] = carrier
    var lights_array: Array = []
    for item in lights:
        lights_array.append(item.to_dict())
    d["lights"] = lights_array
    return d
