class_name HakoPdu_hako_action_msgs_ActionFeedbackHeader
extends RefCounted


var version: int = 0
var reserved: PackedByteArray = PackedByteArray()
var goal_id: PackedByteArray = PackedByteArray()
var sequence_no: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_hako_action_msgs_ActionFeedbackHeader:
    var obj := HakoPdu_hako_action_msgs_ActionFeedbackHeader.new()
    if d.has("version"):
        obj.version = d["version"]
    if d.has("reserved"):
        obj.reserved = d["reserved"]
    if d.has("goal_id"):
        obj.goal_id = d["goal_id"]
    if d.has("sequence_no"):
        obj.sequence_no = d["sequence_no"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["version"] = version
    d["reserved"] = reserved
    d["goal_id"] = goal_id
    d["sequence_no"] = sequence_no
    return d
