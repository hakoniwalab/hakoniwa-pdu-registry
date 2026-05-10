#ifndef _PDU_CTYPE_CONV_HAKO_sensor_msgs_Range_HPP_
#define _PDU_CTYPE_CONV_HAKO_sensor_msgs_Range_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_Range.h"
/*
 * Dependent ros data
 */
#include "sensor_msgs/msg/range.hpp"

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

static inline int _pdu2ros_Range(const char* heap_ptr, Hako_Range &src, sensor_msgs::msg::Range &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // primitive convert
    hako_convert_pdu2ros(src.radiation_type, dst.radiation_type);
    // primitive convert
    hako_convert_pdu2ros(src.field_of_view, dst.field_of_view);
    // primitive convert
    hako_convert_pdu2ros(src.min_range, dst.min_range);
    // primitive convert
    hako_convert_pdu2ros(src.max_range, dst.max_range);
    // primitive convert
    hako_convert_pdu2ros(src.range, dst.range);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_Range(Hako_Range &src, sensor_msgs::msg::Range &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_Range((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_Range(sensor_msgs::msg::Range &src, Hako_Range &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_Header(src.header, dst.header, dynamic_memory);
        // primitive convert
        hako_convert_ros2pdu(src.radiation_type, dst.radiation_type);
        // primitive convert
        hako_convert_ros2pdu(src.field_of_view, dst.field_of_view);
        // primitive convert
        hako_convert_ros2pdu(src.min_range, dst.min_range);
        // primitive convert
        hako_convert_ros2pdu(src.max_range, dst.max_range);
        // primitive convert
        hako_convert_ros2pdu(src.range, dst.range);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_Range(sensor_msgs::msg::Range &src, Hako_Range** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Range out;
    if (!_ros2pdu_Range(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Range), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Range));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Range*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Range* hako_create_empty_pdu_Range(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Range), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Range*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sensor_msgs_Range_HPP_ */
