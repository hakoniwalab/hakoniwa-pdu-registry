#include "godot_pdu_smoke_bridge.hpp"

#include "hako_msgs/pdu_conv_GameControllerOperation.hpp"
#include "hako_msgs/pdu_conv_Disturbance.hpp"
#include "hako_msgs/pdu_conv_DisturbanceUserCustom.hpp"
#include "hako_msgs/pdu_conv_SimpleStructVarray.hpp"
#include "sensor_msgs/pdu_conv_CameraInfo.hpp"
#include "sensor_msgs/pdu_conv_JointState.hpp"
#include "sensor_msgs/pdu_conv_LaserScan.hpp"
#include "sensor_msgs/pdu_conv_PointCloud2.hpp"
#include "std_msgs/pdu_conv_Float64MultiArray.hpp"
#include "std_msgs/pdu_conv_MultiArrayLayout.hpp"

namespace godot {

void HakoPduGodotSmokeBridge::_bind_methods()
{
    ClassDB::bind_method(
        D_METHOD("pdu_to_godot_game_controller_operation", "binary_data"),
        &HakoPduGodotSmokeBridge::pdu_to_godot_game_controller_operation);
    ClassDB::bind_method(
        D_METHOD("godot_to_pdu_game_controller_operation", "obj"),
        &HakoPduGodotSmokeBridge::godot_to_pdu_game_controller_operation);

    ClassDB::bind_method(
        D_METHOD("pdu_to_godot_disturbance_user_custom", "binary_data"),
        &HakoPduGodotSmokeBridge::pdu_to_godot_disturbance_user_custom);
    ClassDB::bind_method(
        D_METHOD("godot_to_pdu_disturbance_user_custom", "obj"),
        &HakoPduGodotSmokeBridge::godot_to_pdu_disturbance_user_custom);

    ClassDB::bind_method(
        D_METHOD("pdu_to_godot_disturbance", "binary_data"),
        &HakoPduGodotSmokeBridge::pdu_to_godot_disturbance);
    ClassDB::bind_method(
        D_METHOD("godot_to_pdu_disturbance", "obj"),
        &HakoPduGodotSmokeBridge::godot_to_pdu_disturbance);

    ClassDB::bind_method(
        D_METHOD("pdu_to_godot_joint_state", "binary_data"),
        &HakoPduGodotSmokeBridge::pdu_to_godot_joint_state);
    ClassDB::bind_method(
        D_METHOD("godot_to_pdu_joint_state", "obj"),
        &HakoPduGodotSmokeBridge::godot_to_pdu_joint_state);

    ClassDB::bind_method(
        D_METHOD("pdu_to_godot_simple_struct_varray", "binary_data"),
        &HakoPduGodotSmokeBridge::pdu_to_godot_simple_struct_varray);
    ClassDB::bind_method(
        D_METHOD("godot_to_pdu_simple_struct_varray", "obj"),
        &HakoPduGodotSmokeBridge::godot_to_pdu_simple_struct_varray);

    ClassDB::bind_method(
        D_METHOD("pdu_to_godot_point_cloud2", "binary_data"),
        &HakoPduGodotSmokeBridge::pdu_to_godot_point_cloud2);
    ClassDB::bind_method(
        D_METHOD("godot_to_pdu_point_cloud2", "obj"),
        &HakoPduGodotSmokeBridge::godot_to_pdu_point_cloud2);

    ClassDB::bind_method(
        D_METHOD("pdu_to_godot_laser_scan", "binary_data"),
        &HakoPduGodotSmokeBridge::pdu_to_godot_laser_scan);
    ClassDB::bind_method(
        D_METHOD("godot_to_pdu_laser_scan", "obj"),
        &HakoPduGodotSmokeBridge::godot_to_pdu_laser_scan);

    ClassDB::bind_method(
        D_METHOD("pdu_to_godot_camera_info", "binary_data"),
        &HakoPduGodotSmokeBridge::pdu_to_godot_camera_info);
    ClassDB::bind_method(
        D_METHOD("godot_to_pdu_camera_info", "obj"),
        &HakoPduGodotSmokeBridge::godot_to_pdu_camera_info);

    ClassDB::bind_method(
        D_METHOD("pdu_to_godot_multi_array_layout", "binary_data"),
        &HakoPduGodotSmokeBridge::pdu_to_godot_multi_array_layout);
    ClassDB::bind_method(
        D_METHOD("godot_to_pdu_multi_array_layout", "obj"),
        &HakoPduGodotSmokeBridge::godot_to_pdu_multi_array_layout);

    ClassDB::bind_method(
        D_METHOD("pdu_to_godot_float64_multi_array", "binary_data"),
        &HakoPduGodotSmokeBridge::pdu_to_godot_float64_multi_array);
    ClassDB::bind_method(
        D_METHOD("godot_to_pdu_float64_multi_array", "obj"),
        &HakoPduGodotSmokeBridge::godot_to_pdu_float64_multi_array);
}

Dictionary HakoPduGodotSmokeBridge::pdu_to_godot_disturbance_user_custom(const PackedByteArray &binary_data) const
{
    return hako::godot_pdu::hako_msgs::pdu_to_godot_DisturbanceUserCustom(binary_data);
}

PackedByteArray HakoPduGodotSmokeBridge::godot_to_pdu_disturbance_user_custom(const Dictionary &obj) const
{
    return hako::godot_pdu::hako_msgs::godot_to_pdu_DisturbanceUserCustom(obj);
}

Dictionary HakoPduGodotSmokeBridge::pdu_to_godot_game_controller_operation(const PackedByteArray &binary_data) const
{
    return hako::godot_pdu::hako_msgs::pdu_to_godot_GameControllerOperation(binary_data);
}

PackedByteArray HakoPduGodotSmokeBridge::godot_to_pdu_game_controller_operation(const Dictionary &obj) const
{
    return hako::godot_pdu::hako_msgs::godot_to_pdu_GameControllerOperation(obj);
}

Dictionary HakoPduGodotSmokeBridge::pdu_to_godot_disturbance(const PackedByteArray &binary_data) const
{
    return hako::godot_pdu::hako_msgs::pdu_to_godot_Disturbance(binary_data);
}

PackedByteArray HakoPduGodotSmokeBridge::godot_to_pdu_disturbance(const Dictionary &obj) const
{
    return hako::godot_pdu::hako_msgs::godot_to_pdu_Disturbance(obj);
}

Dictionary HakoPduGodotSmokeBridge::pdu_to_godot_joint_state(const PackedByteArray &binary_data) const
{
    return hako::godot_pdu::sensor_msgs::pdu_to_godot_JointState(binary_data);
}

PackedByteArray HakoPduGodotSmokeBridge::godot_to_pdu_joint_state(const Dictionary &obj) const
{
    return hako::godot_pdu::sensor_msgs::godot_to_pdu_JointState(obj);
}

Dictionary HakoPduGodotSmokeBridge::pdu_to_godot_simple_struct_varray(const PackedByteArray &binary_data) const
{
    return hako::godot_pdu::hako_msgs::pdu_to_godot_SimpleStructVarray(binary_data);
}

PackedByteArray HakoPduGodotSmokeBridge::godot_to_pdu_simple_struct_varray(const Dictionary &obj) const
{
    return hako::godot_pdu::hako_msgs::godot_to_pdu_SimpleStructVarray(obj);
}

Dictionary HakoPduGodotSmokeBridge::pdu_to_godot_point_cloud2(const PackedByteArray &binary_data) const
{
    return hako::godot_pdu::sensor_msgs::pdu_to_godot_PointCloud2(binary_data);
}

PackedByteArray HakoPduGodotSmokeBridge::godot_to_pdu_point_cloud2(const Dictionary &obj) const
{
    return hako::godot_pdu::sensor_msgs::godot_to_pdu_PointCloud2(obj);
}

Dictionary HakoPduGodotSmokeBridge::pdu_to_godot_laser_scan(const PackedByteArray &binary_data) const
{
    return hako::godot_pdu::sensor_msgs::pdu_to_godot_LaserScan(binary_data);
}

PackedByteArray HakoPduGodotSmokeBridge::godot_to_pdu_laser_scan(const Dictionary &obj) const
{
    return hako::godot_pdu::sensor_msgs::godot_to_pdu_LaserScan(obj);
}

Dictionary HakoPduGodotSmokeBridge::pdu_to_godot_camera_info(const PackedByteArray &binary_data) const
{
    return hako::godot_pdu::sensor_msgs::pdu_to_godot_CameraInfo(binary_data);
}

PackedByteArray HakoPduGodotSmokeBridge::godot_to_pdu_camera_info(const Dictionary &obj) const
{
    return hako::godot_pdu::sensor_msgs::godot_to_pdu_CameraInfo(obj);
}

Dictionary HakoPduGodotSmokeBridge::pdu_to_godot_multi_array_layout(const PackedByteArray &binary_data) const
{
    return hako::godot_pdu::std_msgs::pdu_to_godot_MultiArrayLayout(binary_data);
}

PackedByteArray HakoPduGodotSmokeBridge::godot_to_pdu_multi_array_layout(const Dictionary &obj) const
{
    return hako::godot_pdu::std_msgs::godot_to_pdu_MultiArrayLayout(obj);
}

Dictionary HakoPduGodotSmokeBridge::pdu_to_godot_float64_multi_array(const PackedByteArray &binary_data) const
{
    return hako::godot_pdu::std_msgs::pdu_to_godot_Float64MultiArray(binary_data);
}

PackedByteArray HakoPduGodotSmokeBridge::godot_to_pdu_float64_multi_array(const Dictionary &obj) const
{
    return hako::godot_pdu::std_msgs::godot_to_pdu_Float64MultiArray(obj);
}

} // namespace godot
