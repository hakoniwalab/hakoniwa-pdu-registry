#ifndef _PDU_CTYPE_CONV_HAKO_sensor_msgs_Illuminance_HPP_
#define _PDU_CTYPE_CONV_HAKO_sensor_msgs_Illuminance_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_Illuminance.h"
/*
 * Dependent ros data
 */
#include "sensor_msgs/msg/illuminance.hpp"

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

static inline int _pdu2ros_Illuminance(const char* heap_ptr, Hako_Illuminance &src, sensor_msgs::msg::Illuminance &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // primitive convert
    hako_convert_pdu2ros(src.illuminance, dst.illuminance);
    // primitive convert
    hako_convert_pdu2ros(src.variance, dst.variance);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_Illuminance(Hako_Illuminance &src, sensor_msgs::msg::Illuminance &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_Illuminance((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_Illuminance(sensor_msgs::msg::Illuminance &src, Hako_Illuminance &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_Header(src.header, dst.header, dynamic_memory);
        // primitive convert
        hako_convert_ros2pdu(src.illuminance, dst.illuminance);
        // primitive convert
        hako_convert_ros2pdu(src.variance, dst.variance);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_Illuminance(sensor_msgs::msg::Illuminance &src, Hako_Illuminance** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Illuminance out;
    if (!_ros2pdu_Illuminance(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Illuminance), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Illuminance));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Illuminance*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Illuminance* hako_create_empty_pdu_Illuminance(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Illuminance), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Illuminance*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sensor_msgs_Illuminance_HPP_ */
