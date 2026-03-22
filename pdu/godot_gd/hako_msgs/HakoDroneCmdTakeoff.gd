class_name HakoPdu_hako_msgs_HakoDroneCmdTakeoff
extends RefCounted


const HakoDroneCmdHeaderScript = preload("./HakoDroneCmdHeader.gd")


var header: HakoPdu_hako_msgs_HakoDroneCmdHeader = HakoPdu_hako_msgs_HakoDroneCmdHeader.new()
var height: float = 0.0
var speed: float = 0.0
var yaw_deg: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_HakoDroneCmdTakeoff:
    var obj := HakoPdu_hako_msgs_HakoDroneCmdTakeoff.new()
    if d.has("header"):
        obj.header = HakoDroneCmdHeaderScript.from_dict(d["header"])
    if d.has("height"):
        obj.height = d["height"]
    if d.has("speed"):
        obj.speed = d["speed"]
    if d.has("yaw_deg"):
        obj.yaw_deg = d["yaw_deg"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["height"] = height
    d["speed"] = speed
    d["yaw_deg"] = yaw_deg
    return d
