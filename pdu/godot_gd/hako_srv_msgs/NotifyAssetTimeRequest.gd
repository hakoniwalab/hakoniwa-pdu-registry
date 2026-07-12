class_name HakoPdu_hako_srv_msgs_NotifyAssetTimeRequest
extends RefCounted


const LogicalTimeScript = preload("./LogicalTime.gd")


var session_id: int = 0
var asset_time: HakoPdu_hako_srv_msgs_LogicalTime = HakoPdu_hako_srv_msgs_LogicalTime.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_NotifyAssetTimeRequest:
    var obj := HakoPdu_hako_srv_msgs_NotifyAssetTimeRequest.new()
    if d.has("session_id"):
        obj.session_id = d["session_id"]
    if d.has("asset_time"):
        obj.asset_time = LogicalTimeScript.from_dict(d["asset_time"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["session_id"] = session_id
    d["asset_time"] = asset_time.to_dict()
    return d
