#ifndef _PDU_CTYPE_CONV_HAKO_sensor_msgs_LaserEcho_HPP_
#define _PDU_CTYPE_CONV_HAKO_sensor_msgs_LaserEcho_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_LaserEcho.h"
/*
 * Dependent ros data
 */
#include "sensor_msgs/msg/laser_echo.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_LaserEcho_echoes(const char* heap_ptr, Hako_LaserEcho &src, sensor_msgs::msg::LaserEcho &dst)
{
    // Convert using len and off
    int offset = src._echoes_off;
    int length = src._echoes_len;
    if (length > 0) {
        dst.echoes.resize(length);
        memcpy(dst.echoes.data(), heap_ptr + offset, length * sizeof(Hako_float32));
    }
    return 0;
}

static inline int _pdu2ros_LaserEcho(const char* heap_ptr, Hako_LaserEcho &src, sensor_msgs::msg::LaserEcho &dst)
{
    // primitive array convertor
    _pdu2ros_primitive_array_LaserEcho_echoes(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_LaserEcho(Hako_LaserEcho &src, sensor_msgs::msg::LaserEcho &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_LaserEcho((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_LaserEcho_echoes(sensor_msgs::msg::LaserEcho &src, Hako_LaserEcho &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray
    dst._echoes_len = src.echoes.size();
    if (dst._echoes_len > 0) {
        void* temp_ptr = dynamic_memory.allocate(dst._echoes_len, sizeof(Hako_float32));
        memcpy(temp_ptr, src.echoes.data(), dst._echoes_len * sizeof(Hako_float32));
        dst._echoes_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._echoes_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_LaserEcho(sensor_msgs::msg::LaserEcho &src, Hako_LaserEcho &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //primitive array copy
        _ros2pdu_primitive_array_LaserEcho_echoes(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_LaserEcho(sensor_msgs::msg::LaserEcho &src, Hako_LaserEcho** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_LaserEcho out;
    if (!_ros2pdu_LaserEcho(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_LaserEcho), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_LaserEcho));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_LaserEcho*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_LaserEcho* hako_create_empty_pdu_LaserEcho(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_LaserEcho), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_LaserEcho*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sensor_msgs_LaserEcho_HPP_ */
