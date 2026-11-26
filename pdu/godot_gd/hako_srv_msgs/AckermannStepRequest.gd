class_name HakoPdu_hako_srv_msgs_AckermannStepRequest
extends RefCounted


const AckermannDriveScript = preload("../ackermann_msgs/AckermannDrive.gd")


var step: int = 0
var drive: HakoPdu_ackermann_msgs_AckermannDrive = HakoPdu_ackermann_msgs_AckermannDrive.new()
var tire_friction: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_hako_srv_msgs_AckermannStepRequest:
    var obj := HakoPdu_hako_srv_msgs_AckermannStepRequest.new()
    if d.has("step"):
        obj.step = d["step"]
    if d.has("drive"):
        obj.drive = AckermannDriveScript.from_dict(d["drive"])
    if d.has("tire_friction"):
        obj.tire_friction = d["tire_friction"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["step"] = step
    d["drive"] = drive.to_dict()
    d["tire_friction"] = tire_friction
    return d
