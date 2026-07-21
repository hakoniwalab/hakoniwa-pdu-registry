#ifndef _PDU_CTYPE_CONV_HAKO_trajectory_msgs_MultiDOFJointTrajectoryPoint_HPP_
#define _PDU_CTYPE_CONV_HAKO_trajectory_msgs_MultiDOFJointTrajectoryPoint_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "trajectory_msgs/pdu_ctype_MultiDOFJointTrajectoryPoint.h"
/*
 * Dependent ros data
 */
#include "trajectory_msgs/msg/multi_d_o_f_joint_trajectory_point.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Duration.hpp"
#include "geometry_msgs/pdu_ctype_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_ctype_conv_Transform.hpp"
#include "geometry_msgs/pdu_ctype_conv_Twist.hpp"
#include "geometry_msgs/pdu_ctype_conv_Vector3.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_MultiDOFJointTrajectoryPoint_transforms(const char* heap_ptr, Hako_MultiDOFJointTrajectoryPoint &src, trajectory_msgs::msg::MultiDOFJointTrajectoryPoint &dst)
{
    // Convert using len and off
    int offset = src._transforms_off;
    int length = src._transforms_len;
    if (length > 0) {
        dst.transforms.resize(length);
        Hako_Transform *temp_struct_ptr = (Hako_Transform *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_Transform(heap_ptr, *temp_struct_ptr, dst.transforms[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}
static inline int _pdu2ros_struct_array_MultiDOFJointTrajectoryPoint_velocities(const char* heap_ptr, Hako_MultiDOFJointTrajectoryPoint &src, trajectory_msgs::msg::MultiDOFJointTrajectoryPoint &dst)
{
    // Convert using len and off
    int offset = src._velocities_off;
    int length = src._velocities_len;
    if (length > 0) {
        dst.velocities.resize(length);
        Hako_Twist *temp_struct_ptr = (Hako_Twist *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_Twist(heap_ptr, *temp_struct_ptr, dst.velocities[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}
static inline int _pdu2ros_struct_array_MultiDOFJointTrajectoryPoint_accelerations(const char* heap_ptr, Hako_MultiDOFJointTrajectoryPoint &src, trajectory_msgs::msg::MultiDOFJointTrajectoryPoint &dst)
{
    // Convert using len and off
    int offset = src._accelerations_off;
    int length = src._accelerations_len;
    if (length > 0) {
        dst.accelerations.resize(length);
        Hako_Twist *temp_struct_ptr = (Hako_Twist *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_Twist(heap_ptr, *temp_struct_ptr, dst.accelerations[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int _pdu2ros_MultiDOFJointTrajectoryPoint(const char* heap_ptr, Hako_MultiDOFJointTrajectoryPoint &src, trajectory_msgs::msg::MultiDOFJointTrajectoryPoint &dst)
{
    // struct array convertor
    _pdu2ros_struct_array_MultiDOFJointTrajectoryPoint_transforms(heap_ptr, src, dst);
    // struct array convertor
    _pdu2ros_struct_array_MultiDOFJointTrajectoryPoint_velocities(heap_ptr, src, dst);
    // struct array convertor
    _pdu2ros_struct_array_MultiDOFJointTrajectoryPoint_accelerations(heap_ptr, src, dst);
    // Struct convert
    _pdu2ros_Duration(heap_ptr, src.time_from_start, dst.time_from_start);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_MultiDOFJointTrajectoryPoint(Hako_MultiDOFJointTrajectoryPoint &src, trajectory_msgs::msg::MultiDOFJointTrajectoryPoint &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_MultiDOFJointTrajectoryPoint((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_MultiDOFJointTrajectoryPoint_transforms(trajectory_msgs::msg::MultiDOFJointTrajectoryPoint &src, Hako_MultiDOFJointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._transforms_len = src.transforms.size();
    if (dst._transforms_len > 0) {
        Hako_Transform* temp_struct_ptr = (Hako_Transform*)dynamic_memory.allocate(dst._transforms_len, sizeof(Hako_Transform));
        dst._transforms_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._transforms_len; ++i) {
            _ros2pdu_Transform(src.transforms[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._transforms_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool _ros2pdu_struct_array_MultiDOFJointTrajectoryPoint_velocities(trajectory_msgs::msg::MultiDOFJointTrajectoryPoint &src, Hako_MultiDOFJointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._velocities_len = src.velocities.size();
    if (dst._velocities_len > 0) {
        Hako_Twist* temp_struct_ptr = (Hako_Twist*)dynamic_memory.allocate(dst._velocities_len, sizeof(Hako_Twist));
        dst._velocities_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._velocities_len; ++i) {
            _ros2pdu_Twist(src.velocities[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._velocities_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool _ros2pdu_struct_array_MultiDOFJointTrajectoryPoint_accelerations(trajectory_msgs::msg::MultiDOFJointTrajectoryPoint &src, Hako_MultiDOFJointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._accelerations_len = src.accelerations.size();
    if (dst._accelerations_len > 0) {
        Hako_Twist* temp_struct_ptr = (Hako_Twist*)dynamic_memory.allocate(dst._accelerations_len, sizeof(Hako_Twist));
        dst._accelerations_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._accelerations_len; ++i) {
            _ros2pdu_Twist(src.accelerations[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._accelerations_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_MultiDOFJointTrajectoryPoint(trajectory_msgs::msg::MultiDOFJointTrajectoryPoint &src, Hako_MultiDOFJointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //struct array convert
        _ros2pdu_struct_array_MultiDOFJointTrajectoryPoint_transforms(src, dst, dynamic_memory);
        //struct array convert
        _ros2pdu_struct_array_MultiDOFJointTrajectoryPoint_velocities(src, dst, dynamic_memory);
        //struct array convert
        _ros2pdu_struct_array_MultiDOFJointTrajectoryPoint_accelerations(src, dst, dynamic_memory);
        // struct convert
        _ros2pdu_Duration(src.time_from_start, dst.time_from_start, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_MultiDOFJointTrajectoryPoint(trajectory_msgs::msg::MultiDOFJointTrajectoryPoint &src, Hako_MultiDOFJointTrajectoryPoint** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_MultiDOFJointTrajectoryPoint out;
    if (!_ros2pdu_MultiDOFJointTrajectoryPoint(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_MultiDOFJointTrajectoryPoint), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_MultiDOFJointTrajectoryPoint));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_MultiDOFJointTrajectoryPoint*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_MultiDOFJointTrajectoryPoint* hako_create_empty_pdu_MultiDOFJointTrajectoryPoint(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_MultiDOFJointTrajectoryPoint), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_MultiDOFJointTrajectoryPoint*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_trajectory_msgs_MultiDOFJointTrajectoryPoint_HPP_ */
