#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_GetWorldTimeResponse_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_GetWorldTimeResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_GetWorldTimeResponse.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/get_world_time_response.hpp"

/*
 * Dependent Convertors
 */
#include "hako_srv_msgs/pdu_ctype_conv_LogicalTime.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_GetWorldTimeResponse(const char* heap_ptr, Hako_GetWorldTimeResponse &src, hako_srv_msgs::msg::GetWorldTimeResponse &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.result_code, dst.result_code);
    // Struct convert
    _pdu2ros_LogicalTime(heap_ptr, src.world_time, dst.world_time);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_GetWorldTimeResponse(Hako_GetWorldTimeResponse &src, hako_srv_msgs::msg::GetWorldTimeResponse &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_GetWorldTimeResponse((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_GetWorldTimeResponse(hako_srv_msgs::msg::GetWorldTimeResponse &src, Hako_GetWorldTimeResponse &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.result_code, dst.result_code);
        // struct convert
        if (!_ros2pdu_LogicalTime(src.world_time, dst.world_time, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_GetWorldTimeResponse(hako_srv_msgs::msg::GetWorldTimeResponse &src, Hako_GetWorldTimeResponse** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_GetWorldTimeResponse out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_GetWorldTimeResponse(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_GetWorldTimeResponse), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_GetWorldTimeResponse));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_GetWorldTimeResponse*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_GetWorldTimeResponse() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_GetWorldTimeResponse(hako_srv_msgs::msg::GetWorldTimeResponse &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_GetWorldTimeResponse out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_GetWorldTimeResponse(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "GetWorldTimeResponse" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("GetWorldTimeResponse", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_GetWorldTimeResponse* hako_create_empty_pdu_GetWorldTimeResponse(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_GetWorldTimeResponse), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_GetWorldTimeResponse*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_GetWorldTimeResponse_HPP_ */
