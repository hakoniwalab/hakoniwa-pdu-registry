class_name HakoPdu_hako_srv_msgs_NotifyAssetTimeResponse
extends RefCounted


var result_code: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_NotifyAssetTimeResponse:
    var obj := HakoPdu_hako_srv_msgs_NotifyAssetTimeResponse.new()
    if d.has("result_code"):
        obj.result_code = d["result_code"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["result_code"] = result_code
    return d
