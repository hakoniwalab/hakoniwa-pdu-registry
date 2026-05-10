#ifndef _PDU_CTYPE_CONV_HAKO_sensor_msgs_MultiEchoLaserScan_HPP_
#define _PDU_CTYPE_CONV_HAKO_sensor_msgs_MultiEchoLaserScan_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_MultiEchoLaserScan.h"
/*
 * Dependent ros data
 */
#include "sensor_msgs/msg/multi_echo_laser_scan.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "sensor_msgs/pdu_ctype_conv_LaserEcho.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_MultiEchoLaserScan_ranges(const char* heap_ptr, Hako_MultiEchoLaserScan &src, sensor_msgs::msg::MultiEchoLaserScan &dst)
{
    // Convert using len and off
    int offset = src._ranges_off;
    int length = src._ranges_len;
    if (length > 0) {
        dst.ranges.resize(length);
        Hako_LaserEcho *temp_struct_ptr = (Hako_LaserEcho *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_LaserEcho(heap_ptr, *temp_struct_ptr, dst.ranges[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}
static inline int _pdu2ros_struct_array_MultiEchoLaserScan_intensities(const char* heap_ptr, Hako_MultiEchoLaserScan &src, sensor_msgs::msg::MultiEchoLaserScan &dst)
{
    // Convert using len and off
    int offset = src._intensities_off;
    int length = src._intensities_len;
    if (length > 0) {
        dst.intensities.resize(length);
        Hako_LaserEcho *temp_struct_ptr = (Hako_LaserEcho *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_LaserEcho(heap_ptr, *temp_struct_ptr, dst.intensities[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int _pdu2ros_MultiEchoLaserScan(const char* heap_ptr, Hako_MultiEchoLaserScan &src, sensor_msgs::msg::MultiEchoLaserScan &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // primitive convert
    hako_convert_pdu2ros(src.angle_min, dst.angle_min);
    // primitive convert
    hako_convert_pdu2ros(src.angle_max, dst.angle_max);
    // primitive convert
    hako_convert_pdu2ros(src.angle_increment, dst.angle_increment);
    // primitive convert
    hako_convert_pdu2ros(src.time_increment, dst.time_increment);
    // primitive convert
    hako_convert_pdu2ros(src.scan_time, dst.scan_time);
    // primitive convert
    hako_convert_pdu2ros(src.range_min, dst.range_min);
    // primitive convert
    hako_convert_pdu2ros(src.range_max, dst.range_max);
    // struct array convertor
    _pdu2ros_struct_array_MultiEchoLaserScan_ranges(heap_ptr, src, dst);
    // struct array convertor
    _pdu2ros_struct_array_MultiEchoLaserScan_intensities(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_MultiEchoLaserScan(Hako_MultiEchoLaserScan &src, sensor_msgs::msg::MultiEchoLaserScan &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_MultiEchoLaserScan((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_MultiEchoLaserScan_ranges(sensor_msgs::msg::MultiEchoLaserScan &src, Hako_MultiEchoLaserScan &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._ranges_len = src.ranges.size();
    if (dst._ranges_len > 0) {
        Hako_LaserEcho* temp_struct_ptr = (Hako_LaserEcho*)dynamic_memory.allocate(dst._ranges_len, sizeof(Hako_LaserEcho));
        dst._ranges_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._ranges_len; ++i) {
            _ros2pdu_LaserEcho(src.ranges[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._ranges_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool _ros2pdu_struct_array_MultiEchoLaserScan_intensities(sensor_msgs::msg::MultiEchoLaserScan &src, Hako_MultiEchoLaserScan &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._intensities_len = src.intensities.size();
    if (dst._intensities_len > 0) {
        Hako_LaserEcho* temp_struct_ptr = (Hako_LaserEcho*)dynamic_memory.allocate(dst._intensities_len, sizeof(Hako_LaserEcho));
        dst._intensities_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._intensities_len; ++i) {
            _ros2pdu_LaserEcho(src.intensities[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._intensities_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_MultiEchoLaserScan(sensor_msgs::msg::MultiEchoLaserScan &src, Hako_MultiEchoLaserScan &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_Header(src.header, dst.header, dynamic_memory);
        // primitive convert
        hako_convert_ros2pdu(src.angle_min, dst.angle_min);
        // primitive convert
        hako_convert_ros2pdu(src.angle_max, dst.angle_max);
        // primitive convert
        hako_convert_ros2pdu(src.angle_increment, dst.angle_increment);
        // primitive convert
        hako_convert_ros2pdu(src.time_increment, dst.time_increment);
        // primitive convert
        hako_convert_ros2pdu(src.scan_time, dst.scan_time);
        // primitive convert
        hako_convert_ros2pdu(src.range_min, dst.range_min);
        // primitive convert
        hako_convert_ros2pdu(src.range_max, dst.range_max);
        //struct array convert
        _ros2pdu_struct_array_MultiEchoLaserScan_ranges(src, dst, dynamic_memory);
        //struct array convert
        _ros2pdu_struct_array_MultiEchoLaserScan_intensities(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_MultiEchoLaserScan(sensor_msgs::msg::MultiEchoLaserScan &src, Hako_MultiEchoLaserScan** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_MultiEchoLaserScan out;
    if (!_ros2pdu_MultiEchoLaserScan(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_MultiEchoLaserScan), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_MultiEchoLaserScan));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_MultiEchoLaserScan*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_MultiEchoLaserScan* hako_create_empty_pdu_MultiEchoLaserScan(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_MultiEchoLaserScan), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_MultiEchoLaserScan*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sensor_msgs_MultiEchoLaserScan_HPP_ */
