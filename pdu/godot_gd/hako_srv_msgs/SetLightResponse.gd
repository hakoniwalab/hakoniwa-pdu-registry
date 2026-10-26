class_name HakoPdu_hako_srv_msgs_SetLightResponse
extends RefCounted


var result_code: int = 0
var message: String = ""

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_SetLightResponse:
    var obj := HakoPdu_hako_srv_msgs_SetLightResponse.new()
    if d.has("result_code"):
        obj.result_code = d["result_code"]
    if d.has("message"):
        obj.message = d["message"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["result_code"] = result_code
    d["message"] = message
    return d
