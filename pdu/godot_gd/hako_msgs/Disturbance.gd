class_name HakoPdu_hako_msgs_Disturbance
extends RefCounted


const PointScript = preload("../geometry_msgs/Point.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


const DisturbanceAtmScript = preload("./DisturbanceAtm.gd")


const DisturbanceBoundaryScript = preload("./DisturbanceBoundary.gd")


const DisturbanceTemperatureScript = preload("./DisturbanceTemperature.gd")


const DisturbanceUserCustomScript = preload("./DisturbanceUserCustom.gd")


const DisturbanceWindScript = preload("./DisturbanceWind.gd")


var d_temp: HakoPdu_hako_msgs_DisturbanceTemperature = HakoPdu_hako_msgs_DisturbanceTemperature.new()
var d_wind: HakoPdu_hako_msgs_DisturbanceWind = HakoPdu_hako_msgs_DisturbanceWind.new()
var d_atm: HakoPdu_hako_msgs_DisturbanceAtm = HakoPdu_hako_msgs_DisturbanceAtm.new()
var d_boundary: HakoPdu_hako_msgs_DisturbanceBoundary = HakoPdu_hako_msgs_DisturbanceBoundary.new()
var d_user_custom: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_hako_msgs_Disturbance:
    var obj := HakoPdu_hako_msgs_Disturbance.new()
    if d.has("d_temp"):
        obj.d_temp = DisturbanceTemperatureScript.from_dict(d["d_temp"])
    if d.has("d_wind"):
        obj.d_wind = DisturbanceWindScript.from_dict(d["d_wind"])
    if d.has("d_atm"):
        obj.d_atm = DisturbanceAtmScript.from_dict(d["d_atm"])
    if d.has("d_boundary"):
        obj.d_boundary = DisturbanceBoundaryScript.from_dict(d["d_boundary"])
    if d.has("d_user_custom"):
        obj.d_user_custom = []
        for item in d["d_user_custom"]:
            obj.d_user_custom.append(DisturbanceUserCustomScript.from_dict(item))
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["d_temp"] = d_temp.to_dict()
    d["d_wind"] = d_wind.to_dict()
    d["d_atm"] = d_atm.to_dict()
    d["d_boundary"] = d_boundary.to_dict()
    var d_user_custom_array: Array = []
    for item in d_user_custom:
        d_user_custom_array.append(item.to_dict())
    d["d_user_custom"] = d_user_custom_array
    return d
