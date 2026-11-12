#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_ServiceRequestHeader_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_ServiceRequestHeader_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_ServiceRequestHeader.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/service_request_header.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_ServiceRequestHeader(const char* heap_ptr, Hako_ServiceRequestHeader &src, hako_srv_msgs::msg::ServiceRequestHeader &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.request_id, dst.request_id);
    // string convertor
    dst.service_name = hako_convert_string_from_pdu(src.service_name, M_SIZE(Hako_ServiceRequestHeader, service_name));
    // string convertor
    dst.client_name = hako_convert_string_from_pdu(src.client_name, M_SIZE(Hako_ServiceRequestHeader, client_name));
    // primitive convert
    hako_convert_pdu2ros(src.opcode, dst.opcode);
    // primitive convert
    hako_convert_pdu2ros(src.status_poll_interval_msec, dst.status_poll_interval_msec);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_ServiceRequestHeader(Hako_ServiceRequestHeader &src, hako_srv_msgs::msg::ServiceRequestHeader &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_ServiceRequestHeader((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_ServiceRequestHeader(hako_srv_msgs::msg::ServiceRequestHeader &src, Hako_ServiceRequestHeader &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.request_id, dst.request_id);
        // string convertor
        hako_convert_string_to_pdu(src.service_name, dst.service_name, M_SIZE(Hako_ServiceRequestHeader, service_name));
        // string convertor
        hako_convert_string_to_pdu(src.client_name, dst.client_name, M_SIZE(Hako_ServiceRequestHeader, client_name));
        // primitive convert
        hako_convert_ros2pdu(src.opcode, dst.opcode);
        // primitive convert
        hako_convert_ros2pdu(src.status_poll_interval_msec, dst.status_poll_interval_msec);
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_ServiceRequestHeader(hako_srv_msgs::msg::ServiceRequestHeader &src, Hako_ServiceRequestHeader** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_ServiceRequestHeader out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_ServiceRequestHeader(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_ServiceRequestHeader), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_ServiceRequestHeader));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_ServiceRequestHeader*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_ServiceRequestHeader() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_ServiceRequestHeader(hako_srv_msgs::msg::ServiceRequestHeader &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_ServiceRequestHeader out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_ServiceRequestHeader(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "ServiceRequestHeader" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("ServiceRequestHeader", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_ServiceRequestHeader* hako_create_empty_pdu_ServiceRequestHeader(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_ServiceRequestHeader), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_ServiceRequestHeader*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_ServiceRequestHeader_HPP_ */
