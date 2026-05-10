class_name HakoPdu_sensor_msgs_MultiEchoLaserScan
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const LaserEchoScript = preload("./LaserEcho.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var angle_min: float = 0.0
var angle_max: float = 0.0
var angle_increment: float = 0.0
var time_increment: float = 0.0
var scan_time: float = 0.0
var range_min: float = 0.0
var range_max: float = 0.0
var ranges: Array = []
var intensities: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_MultiEchoLaserScan:
    var obj := HakoPdu_sensor_msgs_MultiEchoLaserScan.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("angle_min"):
        obj.angle_min = d["angle_min"]
    if d.has("angle_max"):
        obj.angle_max = d["angle_max"]
    if d.has("angle_increment"):
        obj.angle_increment = d["angle_increment"]
    if d.has("time_increment"):
        obj.time_increment = d["time_increment"]
    if d.has("scan_time"):
        obj.scan_time = d["scan_time"]
    if d.has("range_min"):
        obj.range_min = d["range_min"]
    if d.has("range_max"):
        obj.range_max = d["range_max"]
    if d.has("ranges"):
        obj.ranges = []
        for item in d["ranges"]:
            obj.ranges.append(LaserEchoScript.from_dict(item))
    if d.has("intensities"):
        obj.intensities = []
        for item in d["intensities"]:
            obj.intensities.append(LaserEchoScript.from_dict(item))
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["angle_min"] = angle_min
    d["angle_max"] = angle_max
    d["angle_increment"] = angle_increment
    d["time_increment"] = time_increment
    d["scan_time"] = scan_time
    d["range_min"] = range_min
    d["range_max"] = range_max
    var ranges_array: Array = []
    for item in ranges:
        ranges_array.append(item.to_dict())
    d["ranges"] = ranges_array
    var intensities_array: Array = []
    for item in intensities:
        intensities_array.append(item.to_dict())
    d["intensities"] = intensities_array
    return d
