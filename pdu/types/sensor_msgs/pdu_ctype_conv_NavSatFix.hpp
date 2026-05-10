#ifndef _PDU_CTYPE_CONV_HAKO_sensor_msgs_NavSatFix_HPP_
#define _PDU_CTYPE_CONV_HAKO_sensor_msgs_NavSatFix_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_NavSatFix.h"
/*
 * Dependent ros data
 */
#include "sensor_msgs/msg/nav_sat_fix.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "sensor_msgs/pdu_ctype_conv_NavSatStatus.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_NavSatFix_position_covariance(const char* heap_ptr, Hako_NavSatFix &src, sensor_msgs::msg::NavSatFix &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 9; ++i) {
        hako_convert_pdu2ros(src.position_covariance[i], dst.position_covariance[i]);
    }
    return 0;
}

static inline int _pdu2ros_NavSatFix(const char* heap_ptr, Hako_NavSatFix &src, sensor_msgs::msg::NavSatFix &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // Struct convert
    _pdu2ros_NavSatStatus(heap_ptr, src.status, dst.status);
    // primitive convert
    hako_convert_pdu2ros(src.latitude, dst.latitude);
    // primitive convert
    hako_convert_pdu2ros(src.longitude, dst.longitude);
    // primitive convert
    hako_convert_pdu2ros(src.altitude, dst.altitude);
    // primitive array convertor
    _pdu2ros_primitive_array_NavSatFix_position_covariance(heap_ptr, src, dst);
    // primitive convert
    hako_convert_pdu2ros(src.position_covariance_type, dst.position_covariance_type);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_NavSatFix(Hako_NavSatFix &src, sensor_msgs::msg::NavSatFix &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_NavSatFix((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_NavSatFix_position_covariance(sensor_msgs::msg::NavSatFix &src, Hako_NavSatFix &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 9
    (void)dynamic_memory;
    (void)hako_convert_ros2pdu_array(
        src.position_covariance, src.position_covariance.size(),
        dst.position_covariance, M_ARRAY_SIZE(Hako_NavSatFix, Hako_float64, position_covariance));
    return true;
}

static inline bool _ros2pdu_NavSatFix(sensor_msgs::msg::NavSatFix &src, Hako_NavSatFix &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_Header(src.header, dst.header, dynamic_memory);
        // struct convert
        _ros2pdu_NavSatStatus(src.status, dst.status, dynamic_memory);
        // primitive convert
        hako_convert_ros2pdu(src.latitude, dst.latitude);
        // primitive convert
        hako_convert_ros2pdu(src.longitude, dst.longitude);
        // primitive convert
        hako_convert_ros2pdu(src.altitude, dst.altitude);
        //primitive array copy
        _ros2pdu_primitive_array_NavSatFix_position_covariance(src, dst, dynamic_memory);
        // primitive convert
        hako_convert_ros2pdu(src.position_covariance_type, dst.position_covariance_type);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_NavSatFix(sensor_msgs::msg::NavSatFix &src, Hako_NavSatFix** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_NavSatFix out;
    if (!_ros2pdu_NavSatFix(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_NavSatFix), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_NavSatFix));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_NavSatFix*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_NavSatFix* hako_create_empty_pdu_NavSatFix(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_NavSatFix), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_NavSatFix*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sensor_msgs_NavSatFix_HPP_ */
