class_name HakoPdu_geometry_msgs_InertiaStamped
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const InertiaScript = preload("./Inertia.gd")


const Vector3Script = preload("./Vector3.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var inertia: HakoPdu_geometry_msgs_Inertia = HakoPdu_geometry_msgs_Inertia.new()

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_InertiaStamped:
    var obj := HakoPdu_geometry_msgs_InertiaStamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("inertia"):
        obj.inertia = InertiaScript.from_dict(d["inertia"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["inertia"] = inertia.to_dict()
    return d
