class_name HakoPdu_sample_action_msgs_FibonacciActionRequest
extends RefCounted


const ActionRequestHeaderScript = preload("../hako_action_msgs/ActionRequestHeader.gd")


const FibonacciGoalScript = preload("./FibonacciGoal.gd")


var header: HakoPdu_hako_action_msgs_ActionRequestHeader = HakoPdu_hako_action_msgs_ActionRequestHeader.new()
var body: HakoPdu_sample_action_msgs_FibonacciGoal = HakoPdu_sample_action_msgs_FibonacciGoal.new()

static func from_dict(d: Dictionary) -> HakoPdu_sample_action_msgs_FibonacciActionRequest:
    var obj := HakoPdu_sample_action_msgs_FibonacciActionRequest.new()
    if d.has("header"):
        obj.header = ActionRequestHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = FibonacciGoalScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
