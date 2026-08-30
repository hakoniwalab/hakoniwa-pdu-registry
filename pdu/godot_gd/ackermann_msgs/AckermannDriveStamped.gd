class_name HakoPdu_ackermann_msgs_AckermannDriveStamped
extends RefCounted


const AckermannDriveScript = preload("./AckermannDrive.gd")


const TimeScript = preload("../builtin_interfaces/Time.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var drive: HakoPdu_ackermann_msgs_AckermannDrive = HakoPdu_ackermann_msgs_AckermannDrive.new()

static func from_dict(d: Dictionary) -> HakoPdu_ackermann_msgs_AckermannDriveStamped:
    var obj := HakoPdu_ackermann_msgs_AckermannDriveStamped.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("drive"):
        obj.drive = AckermannDriveScript.from_dict(d["drive"])
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["drive"] = drive.to_dict()
    return d
