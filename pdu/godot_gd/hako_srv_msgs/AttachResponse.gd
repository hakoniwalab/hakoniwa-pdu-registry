class_name HakoPdu_hako_srv_msgs_AttachResponse
extends RefCounted


const LogicalTimeScript = preload("./LogicalTime.gd")


var result_code: int = 0
var session_id: int = 0
var world_time: HakoPdu_hako_srv_msgs_LogicalTime = HakoPdu_hako_srv_msgs_LogicalTime.new()
var delta_asset_tick: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_AttachResponse:
    var obj := HakoPdu_hako_srv_msgs_AttachResponse.new()
    if d.has("result_code"):
        obj.result_code = d["result_code"]
    if d.has("session_id"):
        obj.session_id = d["session_id"]
    if d.has("world_time"):
        obj.world_time = LogicalTimeScript.from_dict(d["world_time"])
    if d.has("delta_asset_tick"):
        obj.delta_asset_tick = d["delta_asset_tick"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["result_code"] = result_code
    d["session_id"] = session_id
    d["world_time"] = world_time.to_dict()
    d["delta_asset_tick"] = delta_asset_tick
    return d
