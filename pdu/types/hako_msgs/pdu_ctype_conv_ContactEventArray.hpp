#ifndef _PDU_CTYPE_CONV_HAKO_hako_msgs_ContactEventArray_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_msgs_ContactEventArray_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_ContactEventArray.h"
/*
 * Dependent ros data
 */
#include "hako_msgs/msg/contact_event_array.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "geometry_msgs/pdu_ctype_conv_Point.hpp"
#include "hako_msgs/pdu_ctype_conv_ContactEvent.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_ContactEventArray_events(const char* heap_ptr, Hako_ContactEventArray &src, hako_msgs::msg::ContactEventArray &dst)
{
    // Convert using len and off
    int offset = src._events_off;
    int length = src._events_len;
    if (length > 0) {
        dst.events.resize(length);
        Hako_ContactEvent *temp_struct_ptr = (Hako_ContactEvent *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_ContactEvent(heap_ptr, *temp_struct_ptr, dst.events[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int _pdu2ros_ContactEventArray(const char* heap_ptr, Hako_ContactEventArray &src, hako_msgs::msg::ContactEventArray &dst)
{
    // struct array convertor
    _pdu2ros_struct_array_ContactEventArray_events(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_ContactEventArray(Hako_ContactEventArray &src, hako_msgs::msg::ContactEventArray &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_ContactEventArray((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_ContactEventArray_events(hako_msgs::msg::ContactEventArray &src, Hako_ContactEventArray &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._events_len = src.events.size();
    if (dst._events_len > 0) {
        Hako_ContactEvent* temp_struct_ptr = (Hako_ContactEvent*)dynamic_memory.allocate(dst._events_len, sizeof(Hako_ContactEvent));
        dst._events_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._events_len; ++i) {
            _ros2pdu_ContactEvent(src.events[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._events_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_ContactEventArray(hako_msgs::msg::ContactEventArray &src, Hako_ContactEventArray &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //struct array convert
        _ros2pdu_struct_array_ContactEventArray_events(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_ContactEventArray(hako_msgs::msg::ContactEventArray &src, Hako_ContactEventArray** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_ContactEventArray out;
    if (!_ros2pdu_ContactEventArray(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_ContactEventArray), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_ContactEventArray));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_ContactEventArray*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_ContactEventArray* hako_create_empty_pdu_ContactEventArray(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_ContactEventArray), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_ContactEventArray*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_msgs_ContactEventArray_HPP_ */
