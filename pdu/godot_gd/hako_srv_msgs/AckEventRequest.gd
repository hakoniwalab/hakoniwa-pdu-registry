class_name HakoPdu_hako_srv_msgs_AckEventRequest
extends RefCounted


var name: String = ""
var event_code: int = 0
var result_code: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_AckEventRequest:
    var obj := HakoPdu_hako_srv_msgs_AckEventRequest.new()
    if d.has("name"):
        obj.name = d["name"]
    if d.has("event_code"):
        obj.event_code = d["event_code"]
    if d.has("result_code"):
        obj.result_code = d["result_code"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["name"] = name
    d["event_code"] = event_code
    d["result_code"] = result_code
    return d
