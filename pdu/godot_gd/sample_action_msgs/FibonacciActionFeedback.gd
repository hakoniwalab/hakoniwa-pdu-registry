class_name HakoPdu_sample_action_msgs_FibonacciActionFeedback
extends RefCounted


const ActionFeedbackHeaderScript = preload("../hako_action_msgs/ActionFeedbackHeader.gd")


const FibonacciFeedbackScript = preload("./FibonacciFeedback.gd")


var header: HakoPdu_hako_action_msgs_ActionFeedbackHeader = HakoPdu_hako_action_msgs_ActionFeedbackHeader.new()
var body: HakoPdu_sample_action_msgs_FibonacciFeedback = HakoPdu_sample_action_msgs_FibonacciFeedback.new()

static func from_dict(d: Dictionary) -> HakoPdu_sample_action_msgs_FibonacciActionFeedback:
    var obj := HakoPdu_sample_action_msgs_FibonacciActionFeedback.new()
    if d.has("header"):
        obj.header = ActionFeedbackHeaderScript.from_dict(d["header"])
    if d.has("body"):
        obj.body = FibonacciFeedbackScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["body"] = body.to_dict()
    return d
