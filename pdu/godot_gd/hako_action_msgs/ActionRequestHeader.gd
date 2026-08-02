class_name HakoPdu_hako_action_msgs_ActionRequestHeader
extends RefCounted


var version: int = 0
var request_kind: int = 0
var reserved: PackedByteArray = PackedByteArray()
var goal_id: PackedByteArray = PackedByteArray()

static func from_dict(d: Dictionary) -> HakoPdu_hako_action_msgs_ActionRequestHeader:
    var obj := HakoPdu_hako_action_msgs_ActionRequestHeader.new()
    if d.has("version"):
        obj.version = d["version"]
    if d.has("request_kind"):
        obj.request_kind = d["request_kind"]
    if d.has("reserved"):
        obj.reserved = d["reserved"]
    if d.has("goal_id"):
        obj.goal_id = d["goal_id"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["version"] = version
    d["request_kind"] = request_kind
    d["reserved"] = reserved
    d["goal_id"] = goal_id
    return d
