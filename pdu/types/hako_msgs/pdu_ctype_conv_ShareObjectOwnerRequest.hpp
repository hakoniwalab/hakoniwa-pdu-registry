#ifndef _PDU_CTYPE_CONV_HAKO_hako_msgs_ShareObjectOwnerRequest_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_msgs_ShareObjectOwnerRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_ShareObjectOwnerRequest.h"
/*
 * Dependent ros data
 */
#include "hako_msgs/msg/share_object_owner_request.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_ShareObjectOwnerRequest(const char* heap_ptr, Hako_ShareObjectOwnerRequest &src, hako_msgs::msg::ShareObjectOwnerRequest &dst)
{
    // string convertor
    dst.object_name = hako_convert_string_from_pdu(src.object_name, M_SIZE(Hako_ShareObjectOwnerRequest, object_name));
    // primitive convert
    hako_convert_pdu2ros(src.request_type, dst.request_type);
    // primitive convert
    hako_convert_pdu2ros(src.new_owner_id, dst.new_owner_id);
    // primitive convert
    hako_convert_pdu2ros(src.request_time, dst.request_time);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_ShareObjectOwnerRequest(Hako_ShareObjectOwnerRequest &src, hako_msgs::msg::ShareObjectOwnerRequest &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_ShareObjectOwnerRequest((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_ShareObjectOwnerRequest(hako_msgs::msg::ShareObjectOwnerRequest &src, Hako_ShareObjectOwnerRequest &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // string convertor
        hako_convert_string_to_pdu(src.object_name, dst.object_name, M_SIZE(Hako_ShareObjectOwnerRequest, object_name));
        // primitive convert
        hako_convert_ros2pdu(src.request_type, dst.request_type);
        // primitive convert
        hako_convert_ros2pdu(src.new_owner_id, dst.new_owner_id);
        // primitive convert
        hako_convert_ros2pdu(src.request_time, dst.request_time);
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_ShareObjectOwnerRequest(hako_msgs::msg::ShareObjectOwnerRequest &src, Hako_ShareObjectOwnerRequest** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_ShareObjectOwnerRequest out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_ShareObjectOwnerRequest(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_ShareObjectOwnerRequest), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_ShareObjectOwnerRequest));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_ShareObjectOwnerRequest*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_ShareObjectOwnerRequest() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_ShareObjectOwnerRequest(hako_msgs::msg::ShareObjectOwnerRequest &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_ShareObjectOwnerRequest out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_ShareObjectOwnerRequest(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "ShareObjectOwnerRequest" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("ShareObjectOwnerRequest", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_ShareObjectOwnerRequest* hako_create_empty_pdu_ShareObjectOwnerRequest(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_ShareObjectOwnerRequest), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_ShareObjectOwnerRequest*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_msgs_ShareObjectOwnerRequest_HPP_ */
