class_name HakoPdu_hako_msgs_ContactEventArray
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const PointScript = preload("../geometry_msgs/Point.gd")


const ContactEventScript = preload("./ContactEvent.gd")


var events: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_ContactEventArray:
    var obj := HakoPdu_hako_msgs_ContactEventArray.new()
    if d.has("events"):
        obj.events = []
        for item in d["events"]:
            obj.events.append(ContactEventScript.from_dict(item))
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    var events_array: Array = []
    for item in events:
        events_array.append(item.to_dict())
    d["events"] = events_array
    return d
