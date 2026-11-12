#ifndef _PDU_CTYPE_CONV_HAKO_drone_srv_msgs_LiDARScanRequestPacket_HPP_
#define _PDU_CTYPE_CONV_HAKO_drone_srv_msgs_LiDARScanRequestPacket_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "drone_srv_msgs/pdu_ctype_LiDARScanRequestPacket.h"
/*
 * Dependent ros data
 */
#include "drone_srv_msgs/msg/li_d_a_r_scan_request_packet.hpp"

/*
 * Dependent Convertors
 */
#include "drone_srv_msgs/pdu_ctype_conv_LiDARScanRequest.hpp"
#include "hako_srv_msgs/pdu_ctype_conv_ServiceRequestHeader.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_LiDARScanRequestPacket(const char* heap_ptr, Hako_LiDARScanRequestPacket &src, drone_srv_msgs::msg::LiDARScanRequestPacket &dst)
{
    // Struct convert
    _pdu2ros_ServiceRequestHeader(heap_ptr, src.header, dst.header);
    // Struct convert
    _pdu2ros_LiDARScanRequest(heap_ptr, src.body, dst.body);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_LiDARScanRequestPacket(Hako_LiDARScanRequestPacket &src, drone_srv_msgs::msg::LiDARScanRequestPacket &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_LiDARScanRequestPacket((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_LiDARScanRequestPacket(drone_srv_msgs::msg::LiDARScanRequestPacket &src, Hako_LiDARScanRequestPacket &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!_ros2pdu_ServiceRequestHeader(src.header, dst.header, dynamic_memory)) {
            return false;
        }
        // struct convert
        if (!_ros2pdu_LiDARScanRequest(src.body, dst.body, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_LiDARScanRequestPacket(drone_srv_msgs::msg::LiDARScanRequestPacket &src, Hako_LiDARScanRequestPacket** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_LiDARScanRequestPacket out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_LiDARScanRequestPacket(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_LiDARScanRequestPacket), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_LiDARScanRequestPacket));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_LiDARScanRequestPacket*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_LiDARScanRequestPacket() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_LiDARScanRequestPacket(drone_srv_msgs::msg::LiDARScanRequestPacket &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_LiDARScanRequestPacket out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_LiDARScanRequestPacket(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "LiDARScanRequestPacket" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("LiDARScanRequestPacket", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_LiDARScanRequestPacket* hako_create_empty_pdu_LiDARScanRequestPacket(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_LiDARScanRequestPacket), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_LiDARScanRequestPacket*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_drone_srv_msgs_LiDARScanRequestPacket_HPP_ */
