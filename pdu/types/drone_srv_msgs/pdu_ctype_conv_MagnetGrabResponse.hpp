#ifndef _PDU_CTYPE_CONV_HAKO_drone_srv_msgs_MagnetGrabResponse_HPP_
#define _PDU_CTYPE_CONV_HAKO_drone_srv_msgs_MagnetGrabResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "drone_srv_msgs/pdu_ctype_MagnetGrabResponse.h"
/*
 * Dependent ros data
 */
#include "drone_srv_msgs/msg/magnet_grab_response.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_MagnetGrabResponse(const char* heap_ptr, Hako_MagnetGrabResponse &src, drone_srv_msgs::msg::MagnetGrabResponse &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.ok, dst.ok);
    // primitive convert
    hako_convert_pdu2ros(src.magnet_on, dst.magnet_on);
    // primitive convert
    hako_convert_pdu2ros(src.contact_on, dst.contact_on);
    // string convertor
    dst.message = hako_convert_string_from_pdu(src.message, M_SIZE(Hako_MagnetGrabResponse, message));
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_MagnetGrabResponse(Hako_MagnetGrabResponse &src, drone_srv_msgs::msg::MagnetGrabResponse &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_MagnetGrabResponse((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_MagnetGrabResponse(drone_srv_msgs::msg::MagnetGrabResponse &src, Hako_MagnetGrabResponse &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.ok, dst.ok);
        // primitive convert
        hako_convert_ros2pdu(src.magnet_on, dst.magnet_on);
        // primitive convert
        hako_convert_ros2pdu(src.contact_on, dst.contact_on);
        // string convertor
        hako_convert_string_to_pdu(src.message, dst.message, M_SIZE(Hako_MagnetGrabResponse, message));
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_MagnetGrabResponse(drone_srv_msgs::msg::MagnetGrabResponse &src, Hako_MagnetGrabResponse** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_MagnetGrabResponse out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_MagnetGrabResponse(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_MagnetGrabResponse), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_MagnetGrabResponse));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_MagnetGrabResponse*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_MagnetGrabResponse() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_MagnetGrabResponse(drone_srv_msgs::msg::MagnetGrabResponse &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_MagnetGrabResponse out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_MagnetGrabResponse(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "MagnetGrabResponse" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("MagnetGrabResponse", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_MagnetGrabResponse* hako_create_empty_pdu_MagnetGrabResponse(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_MagnetGrabResponse), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_MagnetGrabResponse*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_drone_srv_msgs_MagnetGrabResponse_HPP_ */
