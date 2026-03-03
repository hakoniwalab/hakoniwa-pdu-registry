#ifndef _PDU_CTYPE_CONV_HAKO_hako_msgs_DroneVisualState_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_msgs_DroneVisualState_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_DroneVisualState.h"
/*
 * Dependent ros data
 */
#include "hako_msgs/msg/drone_visual_state.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_DroneVisualState_pwm_duty(const char* heap_ptr, Hako_DroneVisualState &src, hako_msgs::msg::DroneVisualState &dst)
{
    // Convert using len and off
    int offset = src._pwm_duty_off;
    int length = src._pwm_duty_len;
    if (length > 0) {
        dst.pwm_duty.resize(length);
        memcpy(dst.pwm_duty.data(), heap_ptr + offset, length * sizeof(Hako_float32));
    }
    return 0;
}

static inline int _pdu2ros_DroneVisualState(const char* heap_ptr, Hako_DroneVisualState &src, hako_msgs::msg::DroneVisualState &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.x, dst.x);
    // primitive convert
    hako_convert_pdu2ros(src.y, dst.y);
    // primitive convert
    hako_convert_pdu2ros(src.z, dst.z);
    // primitive convert
    hako_convert_pdu2ros(src.roll, dst.roll);
    // primitive convert
    hako_convert_pdu2ros(src.pitch, dst.pitch);
    // primitive convert
    hako_convert_pdu2ros(src.yaw, dst.yaw);
    // primitive array convertor
    _pdu2ros_primitive_array_DroneVisualState_pwm_duty(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_DroneVisualState(Hako_DroneVisualState &src, hako_msgs::msg::DroneVisualState &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_DroneVisualState((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_DroneVisualState_pwm_duty(hako_msgs::msg::DroneVisualState &src, Hako_DroneVisualState &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray
    dst._pwm_duty_len = src.pwm_duty.size();
    if (dst._pwm_duty_len > 0) {
        void* temp_ptr = dynamic_memory.allocate(dst._pwm_duty_len, sizeof(Hako_float32));
        memcpy(temp_ptr, src.pwm_duty.data(), dst._pwm_duty_len * sizeof(Hako_float32));
        dst._pwm_duty_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._pwm_duty_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_DroneVisualState(hako_msgs::msg::DroneVisualState &src, Hako_DroneVisualState &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.x, dst.x);
        // primitive convert
        hako_convert_ros2pdu(src.y, dst.y);
        // primitive convert
        hako_convert_ros2pdu(src.z, dst.z);
        // primitive convert
        hako_convert_ros2pdu(src.roll, dst.roll);
        // primitive convert
        hako_convert_ros2pdu(src.pitch, dst.pitch);
        // primitive convert
        hako_convert_ros2pdu(src.yaw, dst.yaw);
        //primitive array copy
        _ros2pdu_primitive_array_DroneVisualState_pwm_duty(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_DroneVisualState(hako_msgs::msg::DroneVisualState &src, Hako_DroneVisualState** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_DroneVisualState out;
    if (!_ros2pdu_DroneVisualState(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_DroneVisualState), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_DroneVisualState));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_DroneVisualState*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_DroneVisualState* hako_create_empty_pdu_DroneVisualState(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_DroneVisualState), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_DroneVisualState*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_msgs_DroneVisualState_HPP_ */
