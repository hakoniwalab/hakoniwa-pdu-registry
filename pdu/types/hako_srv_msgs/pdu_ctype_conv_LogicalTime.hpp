#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_LogicalTime_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_LogicalTime_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_LogicalTime.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/logical_time.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_LogicalTime(const char* heap_ptr, Hako_LogicalTime &src, hako_srv_msgs::msg::LogicalTime &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.generation, dst.generation);
    // primitive convert
    hako_convert_pdu2ros(src.offset_tick, dst.offset_tick);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_LogicalTime(Hako_LogicalTime &src, hako_srv_msgs::msg::LogicalTime &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_LogicalTime((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_LogicalTime(hako_srv_msgs::msg::LogicalTime &src, Hako_LogicalTime &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.generation, dst.generation);
        // primitive convert
        hako_convert_ros2pdu(src.offset_tick, dst.offset_tick);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_LogicalTime(hako_srv_msgs::msg::LogicalTime &src, Hako_LogicalTime** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_LogicalTime out;
    if (!_ros2pdu_LogicalTime(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_LogicalTime), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_LogicalTime));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_LogicalTime*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_LogicalTime* hako_create_empty_pdu_LogicalTime(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_LogicalTime), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_LogicalTime*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_LogicalTime_HPP_ */
