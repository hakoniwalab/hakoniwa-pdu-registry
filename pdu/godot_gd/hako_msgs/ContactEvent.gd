class_name HakoPdu_hako_msgs_ContactEvent
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const PointScript = preload("../geometry_msgs/Point.gd")


var stamp: HakoPdu_builtin_interfaces_Time = HakoPdu_builtin_interfaces_Time.new()
var self_name: String = ""
var other_name: String = ""
var other_kind: String = ""
var position: HakoPdu_geometry_msgs_Point = HakoPdu_geometry_msgs_Point.new()
var relative_speed: float = 0.0
var started: bool = false

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_ContactEvent:
    var obj := HakoPdu_hako_msgs_ContactEvent.new()
    if d.has("stamp"):
        obj.stamp = TimeScript.from_dict(d["stamp"])
    if d.has("self_name"):
        obj.self_name = d["self_name"]
    if d.has("other_name"):
        obj.other_name = d["other_name"]
    if d.has("other_kind"):
        obj.other_kind = d["other_kind"]
    if d.has("position"):
        obj.position = PointScript.from_dict(d["position"])
    if d.has("relative_speed"):
        obj.relative_speed = d["relative_speed"]
    if d.has("started"):
        obj.started = d["started"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["stamp"] = stamp.to_dict()
    d["self_name"] = self_name
    d["other_name"] = other_name
    d["other_kind"] = other_kind
    d["position"] = position.to_dict()
    d["relative_speed"] = relative_speed
    d["started"] = started
    return d
