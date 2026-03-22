class_name HakoPdu_drone_srv_msgs_LiDARScanResponse
extends RefCounted


const TimeScript = preload("../builtin_interfaces/Time.gd")


const PointScript = preload("../geometry_msgs/Point.gd")


const PoseScript = preload("../geometry_msgs/Pose.gd")


const QuaternionScript = preload("../geometry_msgs/Quaternion.gd")


const PointCloud2Script = preload("../sensor_msgs/PointCloud2.gd")


const PointFieldScript = preload("../sensor_msgs/PointField.gd")


const HeaderScript = preload("../std_msgs/Header.gd")


var ok: bool = false
var point_cloud: HakoPdu_sensor_msgs_PointCloud2 = HakoPdu_sensor_msgs_PointCloud2.new()
var lidar_pose: HakoPdu_geometry_msgs_Pose = HakoPdu_geometry_msgs_Pose.new()
var message: String = ""

static func from_dict(d: Dictionary) -> HakoPdu_drone_srv_msgs_LiDARScanResponse:
    var obj := HakoPdu_drone_srv_msgs_LiDARScanResponse.new()
    if d.has("ok"):
        obj.ok = d["ok"]
    if d.has("point_cloud"):
        obj.point_cloud = PointCloud2Script.from_dict(d["point_cloud"])
    if d.has("lidar_pose"):
        obj.lidar_pose = PoseScript.from_dict(d["lidar_pose"])
    if d.has("message"):
        obj.message = d["message"]
    return obj

func to_dict() -> Dictionary:
    var d: Dictionary = {}
    d["ok"] = ok
    d["point_cloud"] = point_cloud.to_dict()
    d["lidar_pose"] = lidar_pose.to_dict()
    d["message"] = message
    return d
