#ifndef _PDU_CTYPE_CONV_HAKO_hako_msgs_ContactEvent_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_msgs_ContactEvent_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_ContactEvent.h"
/*
 * Dependent ros data
 */
#include "hako_msgs/msg/contact_event.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "geometry_msgs/pdu_ctype_conv_Point.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_ContactEvent(const char* heap_ptr, Hako_ContactEvent &src, hako_msgs::msg::ContactEvent &dst)
{
    // Struct convert
    _pdu2ros_Time(heap_ptr, src.stamp, dst.stamp);
    // string convertor
    dst.self_name = (const char*)src.self_name;
    // string convertor
    dst.other_name = (const char*)src.other_name;
    // string convertor
    dst.other_kind = (const char*)src.other_kind;
    // Struct convert
    _pdu2ros_Point(heap_ptr, src.position, dst.position);
    // primitive convert
    hako_convert_pdu2ros(src.relative_speed, dst.relative_speed);
    // primitive convert
    hako_convert_pdu2ros(src.started, dst.started);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_ContactEvent(Hako_ContactEvent &src, hako_msgs::msg::ContactEvent &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_ContactEvent((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_ContactEvent(hako_msgs::msg::ContactEvent &src, Hako_ContactEvent &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_Time(src.stamp, dst.stamp, dynamic_memory);
        // string convertor
        (void)hako_convert_ros2pdu_array(
            src.self_name, src.self_name.length(),
            dst.self_name, M_ARRAY_SIZE(Hako_ContactEvent, char, self_name));
        dst.self_name[src.self_name.length()] = '\0';
        // string convertor
        (void)hako_convert_ros2pdu_array(
            src.other_name, src.other_name.length(),
            dst.other_name, M_ARRAY_SIZE(Hako_ContactEvent, char, other_name));
        dst.other_name[src.other_name.length()] = '\0';
        // string convertor
        (void)hako_convert_ros2pdu_array(
            src.other_kind, src.other_kind.length(),
            dst.other_kind, M_ARRAY_SIZE(Hako_ContactEvent, char, other_kind));
        dst.other_kind[src.other_kind.length()] = '\0';
        // struct convert
        _ros2pdu_Point(src.position, dst.position, dynamic_memory);
        // primitive convert
        hako_convert_ros2pdu(src.relative_speed, dst.relative_speed);
        // primitive convert
        hako_convert_ros2pdu(src.started, dst.started);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_ContactEvent(hako_msgs::msg::ContactEvent &src, Hako_ContactEvent** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_ContactEvent out;
    if (!_ros2pdu_ContactEvent(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_ContactEvent), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_ContactEvent));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_ContactEvent*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_ContactEvent* hako_create_empty_pdu_ContactEvent(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_ContactEvent), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_ContactEvent*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_msgs_ContactEvent_HPP_ */
