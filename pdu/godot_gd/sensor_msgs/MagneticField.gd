class_name HakoPdu_sensor_msgs_MagneticField
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var magnetic_field: HakoPdu_geometry_msgs_Vector3 = HakoPdu_geometry_msgs_Vector3.new()
var magnetic_field_covariance: PackedFloat64Array = PackedFloat64Array()

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_MagneticField:
    var obj := HakoPdu_sensor_msgs_MagneticField.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("magnetic_field"):
        obj.magnetic_field = Vector3Script.from_dict(d["magnetic_field"])
    if d.has("magnetic_field_covariance"):
        obj.magnetic_field_covariance = d["magnetic_field_covariance"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["magnetic_field"] = magnetic_field.to_dict()
    d["magnetic_field_covariance"] = magnetic_field_covariance
    return d
