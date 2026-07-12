#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_AttachResponse_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_AttachResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_AttachResponse.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/attach_response.hpp"

/*
 * Dependent Convertors
 */
#include "hako_srv_msgs/pdu_ctype_conv_LogicalTime.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_AttachResponse(const char* heap_ptr, Hako_AttachResponse &src, hako_srv_msgs::msg::AttachResponse &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.result_code, dst.result_code);
    // primitive convert
    hako_convert_pdu2ros(src.session_id, dst.session_id);
    // Struct convert
    _pdu2ros_LogicalTime(heap_ptr, src.world_time, dst.world_time);
    // primitive convert
    hako_convert_pdu2ros(src.delta_asset_tick, dst.delta_asset_tick);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_AttachResponse(Hako_AttachResponse &src, hako_srv_msgs::msg::AttachResponse &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_AttachResponse((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_AttachResponse(hako_srv_msgs::msg::AttachResponse &src, Hako_AttachResponse &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.result_code, dst.result_code);
        // primitive convert
        hako_convert_ros2pdu(src.session_id, dst.session_id);
        // struct convert
        _ros2pdu_LogicalTime(src.world_time, dst.world_time, dynamic_memory);
        // primitive convert
        hako_convert_ros2pdu(src.delta_asset_tick, dst.delta_asset_tick);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_AttachResponse(hako_srv_msgs::msg::AttachResponse &src, Hako_AttachResponse** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_AttachResponse out;
    if (!_ros2pdu_AttachResponse(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_AttachResponse), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_AttachResponse));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_AttachResponse*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_AttachResponse* hako_create_empty_pdu_AttachResponse(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_AttachResponse), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_AttachResponse*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_AttachResponse_HPP_ */
