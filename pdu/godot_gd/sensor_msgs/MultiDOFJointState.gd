class_name HakoPdu_sensor_msgs_MultiDOFJointState
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const TransformScript = preload("../geometry_msgs/Transform.gd")


const TwistScript = preload("../geometry_msgs/Twist.gd")


const Vector3Script = preload("../geometry_msgs/Vector3.gd")


const WrenchScript = preload("../geometry_msgs/Wrench.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var header: HakoPdu_std_msgs_Header = HakoPdu_std_msgs_Header.new()
var joint_names: Array[String] = []
var transforms: Array = []
var twist: Array = []
var wrench: Array = []

static func from_dict(d: Dictionary) -> HakoPdu_sensor_msgs_MultiDOFJointState:
    var obj := HakoPdu_sensor_msgs_MultiDOFJointState.new()
    if d.has("header"):
        obj.header = HeaderScript.from_dict(d["header"])
    if d.has("joint_names"):
        obj.joint_names = d["joint_names"]
    if d.has("transforms"):
        obj.transforms = []
        for item in d["transforms"]:
            obj.transforms.append(TransformScript.from_dict(item))
    if d.has("twist"):
        obj.twist = []
        for item in d["twist"]:
            obj.twist.append(TwistScript.from_dict(item))
    if d.has("wrench"):
        obj.wrench = []
        for item in d["wrench"]:
            obj.wrench.append(WrenchScript.from_dict(item))
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["header"] = header.to_dict()
    d["joint_names"] = joint_names
    var transforms_array: Array = []
    for item in transforms:
        transforms_array.append(item.to_dict())
    d["transforms"] = transforms_array
    var twist_array: Array = []
    for item in twist:
        twist_array.append(item.to_dict())
    d["twist"] = twist_array
    var wrench_array: Array = []
    for item in wrench:
        wrench_array.append(item.to_dict())
    d["wrench"] = wrench_array
    return d
