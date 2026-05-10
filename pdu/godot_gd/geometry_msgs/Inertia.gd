class_name HakoPdu_geometry_msgs_Inertia
extends RefCounted


const Vector3Script = preload("./Vector3.gd")


var m: float = 0.0
var com: HakoPdu_geometry_msgs_Vector3 = HakoPdu_geometry_msgs_Vector3.new()
var ixx: float = 0.0
var ixy: float = 0.0
var ixz: float = 0.0
var iyy: float = 0.0
var iyz: float = 0.0
var izz: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_geometry_msgs_Inertia:
    var obj := HakoPdu_geometry_msgs_Inertia.new()
    if d.has("m"):
        obj.m = d["m"]
    if d.has("com"):
        obj.com = Vector3Script.from_dict(d["com"])
    if d.has("ixx"):
        obj.ixx = d["ixx"]
    if d.has("ixy"):
        obj.ixy = d["ixy"]
    if d.has("ixz"):
        obj.ixz = d["ixz"]
    if d.has("iyy"):
        obj.iyy = d["iyy"]
    if d.has("iyz"):
        obj.iyz = d["iyz"]
    if d.has("izz"):
        obj.izz = d["izz"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["m"] = m
    d["com"] = com.to_dict()
    d["ixx"] = ixx
    d["ixy"] = ixy
    d["ixz"] = ixz
    d["iyy"] = iyy
    d["iyz"] = iyz
    d["izz"] = izz
    return d
