class_name HakoPdu_hako_action_msgs_ActionResponseHeader
extends RefCounted


var version: int = 0
var response_kind: int = 0
var status: int = 0
var reserved: int = 0
var goal_id: PackedByteArray = PackedByteArray()

static func from_dict(d: Dictionary) -> HakoPdu_hako_action_msgs_ActionResponseHeader:
    var obj := HakoPdu_hako_action_msgs_ActionResponseHeader.new()
    if d.has("version"):
        obj.version = d["version"]
    if d.has("response_kind"):
        obj.response_kind = d["response_kind"]
    if d.has("status"):
        obj.status = d["status"]
    if d.has("reserved"):
        obj.reserved = d["reserved"]
    if d.has("goal_id"):
        obj.goal_id = d["goal_id"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["version"] = version
    d["response_kind"] = response_kind
    d["status"] = status
    d["reserved"] = reserved
    d["goal_id"] = goal_id
    return d
