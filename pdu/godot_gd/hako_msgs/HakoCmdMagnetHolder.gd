class_name HakoPdu_hako_msgs_HakoCmdMagnetHolder
extends RefCounted


const HakoCmdHeaderScript = preload("./HakoCmdHeader.gd")


var header: HakoPdu_hako_msgs_HakoCmdHeader = HakoPdu_hako_msgs_HakoCmdHeader.new()
var magnet_on: bool = false

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_HakoCmdMagnetHolder:
    var obj := HakoPdu_hako_msgs_HakoCmdMagnetHolder.new()
    if d.has("header"):
        obj.header = HakoCmdHeaderScript.from_dict(d["header"])
    if d.has("magnet_on"):
        obj.magnet_on = d["magnet_on"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["magnet_on"] = magnet_on
    return d
