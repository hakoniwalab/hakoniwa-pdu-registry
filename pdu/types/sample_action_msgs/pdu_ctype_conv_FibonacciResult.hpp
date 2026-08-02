#ifndef _PDU_CTYPE_CONV_HAKO_sample_action_msgs_FibonacciResult_HPP_
#define _PDU_CTYPE_CONV_HAKO_sample_action_msgs_FibonacciResult_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sample_action_msgs/pdu_ctype_FibonacciResult.h"
/*
 * Dependent ros data
 */
#include "sample_action_msgs/msg/fibonacci_result.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_FibonacciResult_sequence(const char* heap_ptr, Hako_FibonacciResult &src, sample_action_msgs::msg::FibonacciResult &dst)
{
    // Convert using len and off
    int offset = src._sequence_off;
    int length = src._sequence_len;
    if (length > 0) {
        dst.sequence.resize(length);
        memcpy(dst.sequence.data(), heap_ptr + offset, length * sizeof(Hako_int32));
    }
    return 0;
}

static inline int _pdu2ros_FibonacciResult(const char* heap_ptr, Hako_FibonacciResult &src, sample_action_msgs::msg::FibonacciResult &dst)
{
    // primitive array convertor
    _pdu2ros_primitive_array_FibonacciResult_sequence(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_FibonacciResult(Hako_FibonacciResult &src, sample_action_msgs::msg::FibonacciResult &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_FibonacciResult((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_FibonacciResult_sequence(sample_action_msgs::msg::FibonacciResult &src, Hako_FibonacciResult &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray
    dst._sequence_len = src.sequence.size();
    if (dst._sequence_len > 0) {
        void* temp_ptr = dynamic_memory.allocate(dst._sequence_len, sizeof(Hako_int32));
        memcpy(temp_ptr, src.sequence.data(), dst._sequence_len * sizeof(Hako_int32));
        dst._sequence_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._sequence_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_FibonacciResult(sample_action_msgs::msg::FibonacciResult &src, Hako_FibonacciResult &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //primitive array copy
        _ros2pdu_primitive_array_FibonacciResult_sequence(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_FibonacciResult(sample_action_msgs::msg::FibonacciResult &src, Hako_FibonacciResult** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_FibonacciResult out;
    if (!_ros2pdu_FibonacciResult(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_FibonacciResult), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_FibonacciResult));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_FibonacciResult*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_FibonacciResult* hako_create_empty_pdu_FibonacciResult(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_FibonacciResult), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_FibonacciResult*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sample_action_msgs_FibonacciResult_HPP_ */
