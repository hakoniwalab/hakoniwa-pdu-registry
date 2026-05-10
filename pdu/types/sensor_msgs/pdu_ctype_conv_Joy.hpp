#ifndef _PDU_CTYPE_CONV_HAKO_sensor_msgs_Joy_HPP_
#define _PDU_CTYPE_CONV_HAKO_sensor_msgs_Joy_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_Joy.h"
/*
 * Dependent ros data
 */
#include "sensor_msgs/msg/joy.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_Joy_axes(const char* heap_ptr, Hako_Joy &src, sensor_msgs::msg::Joy &dst)
{
    // Convert using len and off
    int offset = src._axes_off;
    int length = src._axes_len;
    if (length > 0) {
        dst.axes.resize(length);
        memcpy(dst.axes.data(), heap_ptr + offset, length * sizeof(Hako_float32));
    }
    return 0;
}
static inline int _pdu2ros_primitive_array_Joy_buttons(const char* heap_ptr, Hako_Joy &src, sensor_msgs::msg::Joy &dst)
{
    // Convert using len and off
    int offset = src._buttons_off;
    int length = src._buttons_len;
    if (length > 0) {
        dst.buttons.resize(length);
        memcpy(dst.buttons.data(), heap_ptr + offset, length * sizeof(Hako_int32));
    }
    return 0;
}

static inline int _pdu2ros_Joy(const char* heap_ptr, Hako_Joy &src, sensor_msgs::msg::Joy &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // primitive array convertor
    _pdu2ros_primitive_array_Joy_axes(heap_ptr, src, dst);
    // primitive array convertor
    _pdu2ros_primitive_array_Joy_buttons(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_Joy(Hako_Joy &src, sensor_msgs::msg::Joy &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_Joy((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_Joy_axes(sensor_msgs::msg::Joy &src, Hako_Joy &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray
    dst._axes_len = src.axes.size();
    if (dst._axes_len > 0) {
        void* temp_ptr = dynamic_memory.allocate(dst._axes_len, sizeof(Hako_float32));
        memcpy(temp_ptr, src.axes.data(), dst._axes_len * sizeof(Hako_float32));
        dst._axes_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._axes_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool _ros2pdu_primitive_array_Joy_buttons(sensor_msgs::msg::Joy &src, Hako_Joy &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray
    dst._buttons_len = src.buttons.size();
    if (dst._buttons_len > 0) {
        void* temp_ptr = dynamic_memory.allocate(dst._buttons_len, sizeof(Hako_int32));
        memcpy(temp_ptr, src.buttons.data(), dst._buttons_len * sizeof(Hako_int32));
        dst._buttons_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._buttons_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_Joy(sensor_msgs::msg::Joy &src, Hako_Joy &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_Header(src.header, dst.header, dynamic_memory);
        //primitive array copy
        _ros2pdu_primitive_array_Joy_axes(src, dst, dynamic_memory);
        //primitive array copy
        _ros2pdu_primitive_array_Joy_buttons(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_Joy(sensor_msgs::msg::Joy &src, Hako_Joy** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Joy out;
    if (!_ros2pdu_Joy(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Joy), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Joy));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Joy*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Joy* hako_create_empty_pdu_Joy(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Joy), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Joy*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sensor_msgs_Joy_HPP_ */
