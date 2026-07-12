class_name HakoPdu_hako_srv_msgs_AttachRequest
extends RefCounted


var asset_name: String = ""
var delta_asset_tick: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_AttachRequest:
    var obj := HakoPdu_hako_srv_msgs_AttachRequest.new()
    if d.has("asset_name"):
        obj.asset_name = d["asset_name"]
    if d.has("delta_asset_tick"):
        obj.delta_asset_tick = d["delta_asset_tick"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["asset_name"] = asset_name
    d["delta_asset_tick"] = delta_asset_tick
    return d
