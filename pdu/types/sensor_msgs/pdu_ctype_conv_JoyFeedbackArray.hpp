#ifndef _PDU_CTYPE_CONV_HAKO_sensor_msgs_JoyFeedbackArray_HPP_
#define _PDU_CTYPE_CONV_HAKO_sensor_msgs_JoyFeedbackArray_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_JoyFeedbackArray.h"
/*
 * Dependent ros data
 */
#include "sensor_msgs/msg/joy_feedback_array.hpp"

/*
 * Dependent Convertors
 */
#include "sensor_msgs/pdu_ctype_conv_JoyFeedback.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_JoyFeedbackArray_array(const char* heap_ptr, Hako_JoyFeedbackArray &src, sensor_msgs::msg::JoyFeedbackArray &dst)
{
    // Convert using len and off
    int offset = src._array_off;
    int length = src._array_len;
    if (length > 0) {
        dst.array.resize(length);
        Hako_JoyFeedback *temp_struct_ptr = (Hako_JoyFeedback *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_JoyFeedback(heap_ptr, *temp_struct_ptr, dst.array[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int _pdu2ros_JoyFeedbackArray(const char* heap_ptr, Hako_JoyFeedbackArray &src, sensor_msgs::msg::JoyFeedbackArray &dst)
{
    // struct array convertor
    _pdu2ros_struct_array_JoyFeedbackArray_array(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_JoyFeedbackArray(Hako_JoyFeedbackArray &src, sensor_msgs::msg::JoyFeedbackArray &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_JoyFeedbackArray((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_JoyFeedbackArray_array(sensor_msgs::msg::JoyFeedbackArray &src, Hako_JoyFeedbackArray &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._array_len = src.array.size();
    if (dst._array_len > 0) {
        Hako_JoyFeedback* temp_struct_ptr = (Hako_JoyFeedback*)dynamic_memory.allocate(dst._array_len, sizeof(Hako_JoyFeedback));
        dst._array_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._array_len; ++i) {
            _ros2pdu_JoyFeedback(src.array[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._array_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_JoyFeedbackArray(sensor_msgs::msg::JoyFeedbackArray &src, Hako_JoyFeedbackArray &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //struct array convert
        _ros2pdu_struct_array_JoyFeedbackArray_array(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_JoyFeedbackArray(sensor_msgs::msg::JoyFeedbackArray &src, Hako_JoyFeedbackArray** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_JoyFeedbackArray out;
    if (!_ros2pdu_JoyFeedbackArray(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_JoyFeedbackArray), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_JoyFeedbackArray));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_JoyFeedbackArray*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_JoyFeedbackArray* hako_create_empty_pdu_JoyFeedbackArray(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_JoyFeedbackArray), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_JoyFeedbackArray*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sensor_msgs_JoyFeedbackArray_HPP_ */
