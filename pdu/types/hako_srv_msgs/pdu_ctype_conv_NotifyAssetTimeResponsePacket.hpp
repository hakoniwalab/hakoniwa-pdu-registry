#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_NotifyAssetTimeResponsePacket_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_NotifyAssetTimeResponsePacket_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_NotifyAssetTimeResponsePacket.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/notify_asset_time_response_packet.hpp"

/*
 * Dependent Convertors
 */
#include "hako_srv_msgs/pdu_ctype_conv_NotifyAssetTimeResponse.hpp"
#include "hako_srv_msgs/pdu_ctype_conv_ServiceResponseHeader.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_NotifyAssetTimeResponsePacket(const char* heap_ptr, Hako_NotifyAssetTimeResponsePacket &src, hako_srv_msgs::msg::NotifyAssetTimeResponsePacket &dst)
{
    // Struct convert
    _pdu2ros_ServiceResponseHeader(heap_ptr, src.header, dst.header);
    // Struct convert
    _pdu2ros_NotifyAssetTimeResponse(heap_ptr, src.body, dst.body);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_NotifyAssetTimeResponsePacket(Hako_NotifyAssetTimeResponsePacket &src, hako_srv_msgs::msg::NotifyAssetTimeResponsePacket &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_NotifyAssetTimeResponsePacket((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_NotifyAssetTimeResponsePacket(hako_srv_msgs::msg::NotifyAssetTimeResponsePacket &src, Hako_NotifyAssetTimeResponsePacket &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_ServiceResponseHeader(src.header, dst.header, dynamic_memory);
        // struct convert
        _ros2pdu_NotifyAssetTimeResponse(src.body, dst.body, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_NotifyAssetTimeResponsePacket(hako_srv_msgs::msg::NotifyAssetTimeResponsePacket &src, Hako_NotifyAssetTimeResponsePacket** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_NotifyAssetTimeResponsePacket out;
    if (!_ros2pdu_NotifyAssetTimeResponsePacket(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_NotifyAssetTimeResponsePacket), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_NotifyAssetTimeResponsePacket));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_NotifyAssetTimeResponsePacket*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_NotifyAssetTimeResponsePacket* hako_create_empty_pdu_NotifyAssetTimeResponsePacket(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_NotifyAssetTimeResponsePacket), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_NotifyAssetTimeResponsePacket*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_NotifyAssetTimeResponsePacket_HPP_ */
