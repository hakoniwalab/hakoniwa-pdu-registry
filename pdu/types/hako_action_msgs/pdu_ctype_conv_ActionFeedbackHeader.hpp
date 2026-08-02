#ifndef _PDU_CTYPE_CONV_HAKO_hako_action_msgs_ActionFeedbackHeader_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_action_msgs_ActionFeedbackHeader_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_action_msgs/pdu_ctype_ActionFeedbackHeader.h"
/*
 * Dependent ros data
 */
#include "hako_action_msgs/msg/action_feedback_header.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_ActionFeedbackHeader_reserved(const char* heap_ptr, Hako_ActionFeedbackHeader &src, hako_action_msgs::msg::ActionFeedbackHeader &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 3; ++i) {
        hako_convert_pdu2ros(src.reserved[i], dst.reserved[i]);
    }
    return 0;
}
static inline int _pdu2ros_primitive_array_ActionFeedbackHeader_goal_id(const char* heap_ptr, Hako_ActionFeedbackHeader &src, hako_action_msgs::msg::ActionFeedbackHeader &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 16; ++i) {
        hako_convert_pdu2ros(src.goal_id[i], dst.goal_id[i]);
    }
    return 0;
}

static inline int _pdu2ros_ActionFeedbackHeader(const char* heap_ptr, Hako_ActionFeedbackHeader &src, hako_action_msgs::msg::ActionFeedbackHeader &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.version, dst.version);
    // primitive array convertor
    _pdu2ros_primitive_array_ActionFeedbackHeader_reserved(heap_ptr, src, dst);
    // primitive array convertor
    _pdu2ros_primitive_array_ActionFeedbackHeader_goal_id(heap_ptr, src, dst);
    // primitive convert
    hako_convert_pdu2ros(src.sequence_no, dst.sequence_no);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_ActionFeedbackHeader(Hako_ActionFeedbackHeader &src, hako_action_msgs::msg::ActionFeedbackHeader &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_ActionFeedbackHeader((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_ActionFeedbackHeader_reserved(hako_action_msgs::msg::ActionFeedbackHeader &src, Hako_ActionFeedbackHeader &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 3
    (void)dynamic_memory;
    (void)hako_convert_ros2pdu_array(
        src.reserved, src.reserved.size(),
        dst.reserved, M_ARRAY_SIZE(Hako_ActionFeedbackHeader, Hako_uint8, reserved));
    return true;
}
static inline bool _ros2pdu_primitive_array_ActionFeedbackHeader_goal_id(hako_action_msgs::msg::ActionFeedbackHeader &src, Hako_ActionFeedbackHeader &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 16
    (void)dynamic_memory;
    (void)hako_convert_ros2pdu_array(
        src.goal_id, src.goal_id.size(),
        dst.goal_id, M_ARRAY_SIZE(Hako_ActionFeedbackHeader, Hako_uint8, goal_id));
    return true;
}

static inline bool _ros2pdu_ActionFeedbackHeader(hako_action_msgs::msg::ActionFeedbackHeader &src, Hako_ActionFeedbackHeader &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.version, dst.version);
        //primitive array copy
        _ros2pdu_primitive_array_ActionFeedbackHeader_reserved(src, dst, dynamic_memory);
        //primitive array copy
        _ros2pdu_primitive_array_ActionFeedbackHeader_goal_id(src, dst, dynamic_memory);
        // primitive convert
        hako_convert_ros2pdu(src.sequence_no, dst.sequence_no);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_ActionFeedbackHeader(hako_action_msgs::msg::ActionFeedbackHeader &src, Hako_ActionFeedbackHeader** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_ActionFeedbackHeader out;
    if (!_ros2pdu_ActionFeedbackHeader(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_ActionFeedbackHeader), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_ActionFeedbackHeader));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_ActionFeedbackHeader*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_ActionFeedbackHeader* hako_create_empty_pdu_ActionFeedbackHeader(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_ActionFeedbackHeader), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_ActionFeedbackHeader*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_action_msgs_ActionFeedbackHeader_HPP_ */
