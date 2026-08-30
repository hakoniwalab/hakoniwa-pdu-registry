class_name HakoPdu_ackermann_msgs_AckermannDrive
extends RefCounted


var steering_angle: float = 0.0
var steering_angle_velocity: float = 0.0
var speed: float = 0.0
var acceleration: float = 0.0
var jerk: float = 0.0

static func from_dict(d: Dictionary) -> HakoPdu_ackermann_msgs_AckermannDrive:
    var obj := HakoPdu_ackermann_msgs_AckermannDrive.new()
    if d.has("steering_angle"):
        obj.steering_angle = d["steering_angle"]
    if d.has("steering_angle_velocity"):
        obj.steering_angle_velocity = d["steering_angle_velocity"]
    if d.has("speed"):
        obj.speed = d["speed"]
    if d.has("acceleration"):
        obj.acceleration = d["acceleration"]
    if d.has("jerk"):
        obj.jerk = d["jerk"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["steering_angle"] = steering_angle
    d["steering_angle_velocity"] = steering_angle_velocity
    d["speed"] = speed
    d["acceleration"] = acceleration
    d["jerk"] = jerk
    return d
