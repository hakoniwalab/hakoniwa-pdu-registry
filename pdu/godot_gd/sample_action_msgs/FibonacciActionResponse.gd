class_name HakoPdu_sample_action_msgs_FibonacciActionResponse
extends RefCounted


const ActionResponseHeaderScript = preload("../hako_action_msgs/ActionResponseHeader.gd")


const FibonacciResultScript = preload("./FibonacciResult.gd")


var header: HakoPdu_hako_action_msgs_ActionResponseHeader = HakoPdu_hako_action_msgs_ActionResponseHeader.new()
var body: HakoPdu_sample_action_msgs_FibonacciResult = HakoPdu_sample_action_msgs_FibonacciResult.new()

static func from_dict(d: Dictionary) -> HakoPdu_sample_action_msgs_FibonacciActionResponse:
    var obj := HakoPdu_sample_action_msgs_FibonacciActionResponse.new()
    if d.has("header"):
        obj.header = ActionResponseHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = FibonacciResultScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
