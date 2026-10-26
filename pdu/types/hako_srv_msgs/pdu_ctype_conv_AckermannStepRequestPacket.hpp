#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_AckermannStepRequestPacket_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_AckermannStepRequestPacket_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_AckermannStepRequestPacket.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/ackermann_step_request_packet.hpp"

/*
 * Dependent Convertors
 */
#include "ackermann_msgs/pdu_ctype_conv_AckermannDrive.hpp"
#include "hako_srv_msgs/pdu_ctype_conv_AckermannStepRequest.hpp"
#include "hako_srv_msgs/pdu_ctype_conv_ServiceRequestHeader.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_AckermannStepRequestPacket(const char* heap_ptr, Hako_AckermannStepRequestPacket &src, hako_srv_msgs::msg::AckermannStepRequestPacket &dst)
{
    // Struct convert
    _pdu2ros_ServiceRequestHeader(heap_ptr, src.header, dst.header);
    // Struct convert
    _pdu2ros_AckermannStepRequest(heap_ptr, src.body, dst.body);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_AckermannStepRequestPacket(Hako_AckermannStepRequestPacket &src, hako_srv_msgs::msg::AckermannStepRequestPacket &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_AckermannStepRequestPacket((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_AckermannStepRequestPacket(hako_srv_msgs::msg::AckermannStepRequestPacket &src, Hako_AckermannStepRequestPacket &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_ServiceRequestHeader(src.header, dst.header, dynamic_memory);
        // struct convert
        _ros2pdu_AckermannStepRequest(src.body, dst.body, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_AckermannStepRequestPacket(hako_srv_msgs::msg::AckermannStepRequestPacket &src, Hako_AckermannStepRequestPacket** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_AckermannStepRequestPacket out;
    if (!_ros2pdu_AckermannStepRequestPacket(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_AckermannStepRequestPacket), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_AckermannStepRequestPacket));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_AckermannStepRequestPacket*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_AckermannStepRequestPacket* hako_create_empty_pdu_AckermannStepRequestPacket(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_AckermannStepRequestPacket), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_AckermannStepRequestPacket*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_AckermannStepRequestPacket_HPP_ */
