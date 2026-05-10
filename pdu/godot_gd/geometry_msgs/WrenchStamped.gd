class_name HakoPdu_geometry_msgs_WrenchStamped
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const Vector3Script = preload("./Vector3.gd")


const WrenchScript = preload("./Wrench.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var wrench: HakoPdu_geometry_msgs_Wrench = HakoPdu_geometry_msgs_Wrench.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_WrenchStamped:
    var obj := HakoPdu_geometry_msgs_WrenchStamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("wrench"):
        obj.wrench = WrenchScript.from_dict(d["wrench"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["wrench"] = wrench.to_dict()
    return d
