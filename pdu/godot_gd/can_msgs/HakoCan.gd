class_name HakoPdu_can_msgs_HakoCan
extends RefCounted


const HakoCanBodyScript = preload("./HakoCanBody.gd")


const HakoCanHeadScript = preload("./HakoCanHead.gd")


var head: HakoPdu_can_msgs_HakoCanHead = HakoPdu_can_msgs_HakoCanHead.new()
var body: HakoPdu_can_msgs_HakoCanBody = HakoPdu_can_msgs_HakoCanBody.new()

static func from_dict(d: Dictionary) -> HakoPdu_can_msgs_HakoCan:
    var obj := HakoPdu_can_msgs_HakoCan.new()
    if d.has("head"):
        obj.head = HakoCanHeadScript.from_dict(d["head"])
    if d.has("body"):
        obj.body = HakoCanBodyScript.from_dict(d["body"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["head"] = head.to_dict()
    d["body"] = body.to_dict()
    return d
