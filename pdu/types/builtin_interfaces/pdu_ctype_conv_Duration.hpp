#ifndef _PDU_CTYPE_CONV_HAKO_builtin_interfaces_Duration_HPP_
#define _PDU_CTYPE_CONV_HAKO_builtin_interfaces_Duration_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "builtin_interfaces/pdu_ctype_Duration.h"
/*
 * Dependent ros data
 */
#include "builtin_interfaces/msg/duration.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_Duration(const char* heap_ptr, Hako_Duration &src, builtin_interfaces::msg::Duration &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.sec, dst.sec);
    // primitive convert
    hako_convert_pdu2ros(src.nanosec, dst.nanosec);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_Duration(Hako_Duration &src, builtin_interfaces::msg::Duration &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_Duration((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_Duration(builtin_interfaces::msg::Duration &src, Hako_Duration &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.sec, dst.sec);
        // primitive convert
        hako_convert_ros2pdu(src.nanosec, dst.nanosec);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_Duration(builtin_interfaces::msg::Duration &src, Hako_Duration** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Duration out;
    if (!_ros2pdu_Duration(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Duration), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Duration));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Duration*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Duration* hako_create_empty_pdu_Duration(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Duration), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Duration*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_builtin_interfaces_Duration_HPP_ */
