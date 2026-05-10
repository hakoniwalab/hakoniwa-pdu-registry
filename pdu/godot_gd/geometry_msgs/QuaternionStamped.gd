class_name HakoPdu_geometry_msgs_QuaternionStamped
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const QuaternionScript = preload("./Quaternion.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var quaternion: HakoPdu_geometry_msgs_Quaternion = HakoPdu_geometry_msgs_Quaternion.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_QuaternionStamped:
    var obj := HakoPdu_geometry_msgs_QuaternionStamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("quaternion"):
        obj.quaternion = QuaternionScript.from_dict(d["quaternion"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["quaternion"] = quaternion.to_dict()
    return d
