#ifndef _PDU_CTYPE_CONV_HAKO_ackermann_msgs_AckermannDrive_HPP_
#define _PDU_CTYPE_CONV_HAKO_ackermann_msgs_AckermannDrive_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "ackermann_msgs/pdu_ctype_AckermannDrive.h"
/*
 * Dependent ros data
 */
#include "ackermann_msgs/msg/ackermann_drive.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_AckermannDrive(const char* heap_ptr, Hako_AckermannDrive &src, ackermann_msgs::msg::AckermannDrive &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.steering_angle, dst.steering_angle);
    // primitive convert
    hako_convert_pdu2ros(src.steering_angle_velocity, dst.steering_angle_velocity);
    // primitive convert
    hako_convert_pdu2ros(src.speed, dst.speed);
    // primitive convert
    hako_convert_pdu2ros(src.acceleration, dst.acceleration);
    // primitive convert
    hako_convert_pdu2ros(src.jerk, dst.jerk);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_AckermannDrive(Hako_AckermannDrive &src, ackermann_msgs::msg::AckermannDrive &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_AckermannDrive((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_AckermannDrive(ackermann_msgs::msg::AckermannDrive &src, Hako_AckermannDrive &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.steering_angle, dst.steering_angle);
        // primitive convert
        hako_convert_ros2pdu(src.steering_angle_velocity, dst.steering_angle_velocity);
        // primitive convert
        hako_convert_ros2pdu(src.speed, dst.speed);
        // primitive convert
        hako_convert_ros2pdu(src.acceleration, dst.acceleration);
        // primitive convert
        hako_convert_ros2pdu(src.jerk, dst.jerk);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_AckermannDrive(ackermann_msgs::msg::AckermannDrive &src, Hako_AckermannDrive** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_AckermannDrive out;
    if (!_ros2pdu_AckermannDrive(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_AckermannDrive), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_AckermannDrive));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_AckermannDrive*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_AckermannDrive* hako_create_empty_pdu_AckermannDrive(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_AckermannDrive), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_AckermannDrive*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_ackermann_msgs_AckermannDrive_HPP_ */
