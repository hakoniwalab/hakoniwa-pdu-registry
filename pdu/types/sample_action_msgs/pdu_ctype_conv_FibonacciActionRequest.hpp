#ifndef _PDU_CTYPE_CONV_HAKO_sample_action_msgs_FibonacciActionRequest_HPP_
#define _PDU_CTYPE_CONV_HAKO_sample_action_msgs_FibonacciActionRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sample_action_msgs/pdu_ctype_FibonacciActionRequest.h"
/*
 * Dependent ros data
 */
#include "sample_action_msgs/msg/fibonacci_action_request.hpp"

/*
 * Dependent Convertors
 */
#include "hako_action_msgs/pdu_ctype_conv_ActionRequestHeader.hpp"
#include "sample_action_msgs/pdu_ctype_conv_FibonacciGoal.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_FibonacciActionRequest(const char* heap_ptr, Hako_FibonacciActionRequest &src, sample_action_msgs::msg::FibonacciActionRequest &dst)
{
    // Struct convert
    _pdu2ros_ActionRequestHeader(heap_ptr, src.header, dst.header);
    // Struct convert
    _pdu2ros_FibonacciGoal(heap_ptr, src.body, dst.body);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_FibonacciActionRequest(Hako_FibonacciActionRequest &src, sample_action_msgs::msg::FibonacciActionRequest &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_FibonacciActionRequest((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_FibonacciActionRequest(sample_action_msgs::msg::FibonacciActionRequest &src, Hako_FibonacciActionRequest &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_ActionRequestHeader(src.header, dst.header, dynamic_memory);
        // struct convert
        _ros2pdu_FibonacciGoal(src.body, dst.body, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_FibonacciActionRequest(sample_action_msgs::msg::FibonacciActionRequest &src, Hako_FibonacciActionRequest** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_FibonacciActionRequest out;
    if (!_ros2pdu_FibonacciActionRequest(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_FibonacciActionRequest), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_FibonacciActionRequest));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_FibonacciActionRequest*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_FibonacciActionRequest* hako_create_empty_pdu_FibonacciActionRequest(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_FibonacciActionRequest), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_FibonacciActionRequest*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sample_action_msgs_FibonacciActionRequest_HPP_ */
