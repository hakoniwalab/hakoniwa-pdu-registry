class_name HakoPdu_sensor_msgs_NavSatFix
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const NavSatStatusScript = preload("./NavSatStatus.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var status: HakoPdu_sensor_msgs_NavSatStatus = HakoPdu_sensor_msgs_NavSatStatus.new()
var latitude: float = 0.0
var longitude: float = 0.0
var altitude: float = 0.0
var position_covariance: PackedFloat64Array = PackedFloat64Array()
var position_covariance_type: int = 0

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_NavSatFix:
    var obj := HakoPdu_sensor_msgs_NavSatFix.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("status"):
        obj.status = NavSatStatusScript.from_dict(d["status"])
    if d.has("latitude"):
        obj.latitude = d["latitude"]
    if d.has("longitude"):
        obj.longitude = d["longitude"]
    if d.has("altitude"):
        obj.altitude = d["altitude"]
    if d.has("position_covariance"):
        obj.position_covariance = d["position_covariance"]
    if d.has("position_covariance_type"):
        obj.position_covariance_type = d["position_covariance_type"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["status"] = status.to_dict()
    d["latitude"] = latitude
    d["longitude"] = longitude
    d["altitude"] = altitude
    d["position_covariance"] = position_covariance
    d["position_covariance_type"] = position_covariance_type
    return d
