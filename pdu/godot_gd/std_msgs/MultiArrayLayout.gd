class_name HakoPdu_std_msgs_MultiArrayLayout
extends RefCounted


const MultiArrayDimensionScript = preload("./MultiArrayDimension.gd")


var dim: Array = []
var data_offset: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_std_msgs_MultiArrayLayout:
    var obj := HakoPdu_std_msgs_MultiArrayLayout.new()
    if d.has("dim"):
        obj.dim = []
        for item in d["dim"]:
            obj.dim.append(MultiArrayDimensionScript.from_dict(item))
    if d.has("data_offset"):
        obj.data_offset = d["data_offset"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    var dim_array: Array = []
    for item in dim:
        dim_array.append(item.to_dict())
    d["dim"] = dim_array
    d["data_offset"] = data_offset
    return d
