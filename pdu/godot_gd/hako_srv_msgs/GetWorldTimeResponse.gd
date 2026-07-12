class_name HakoPdu_hako_srv_msgs_GetWorldTimeResponse
extends RefCounted


const LogicalTimeScript = preload("./LogicalTime.gd")


var result_code: int = 0
var world_time: HakoPdu_hako_srv_msgs_LogicalTime = HakoPdu_hako_srv_msgs_LogicalTime.new()

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_GetWorldTimeResponse:
    var obj := HakoPdu_hako_srv_msgs_GetWorldTimeResponse.new()
    if d.has("result_code"):
        obj.result_code = d["result_code"]
    if d.has("world_time"):
        obj.world_time = LogicalTimeScript.from_dict(d["world_time"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["result_code"] = result_code
    d["world_time"] = world_time.to_dict()
    return d
