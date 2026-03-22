class_name HakoPdu_std_msgs_Float64MultiArray
extends RefCounted


const MultiArrayDimensionScript = preload("./MultiArrayDimension.gd")


const MultiArrayLayoutScript = preload("./MultiArrayLayout.gd")


var layout: HakoPdu_std_msgs_MultiArrayLayout = HakoPdu_std_msgs_MultiArrayLayout.new()
var data: PackedFloat64Array = PackedFloat64Array()

static func from_dict(d: Dictionary) -> HakoPdu_std_msgs_Float64MultiArray:
    var obj := HakoPdu_std_msgs_Float64MultiArray.new()
    if d.has("layout"):
        obj.layout = MultiArrayLayoutScript.from_dict(d["layout"])
    if d.has("data"):
        obj.data = d["data"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["layout"] = layout.to_dict()
    d["data"] = data
    return d
