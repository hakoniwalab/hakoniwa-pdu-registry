#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_PersonStepResponsePacket_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_PersonStepResponsePacket_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_PersonStepResponsePacket.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/person_step_response_packet.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "geometry_msgs/pdu_ctype_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_ctype_conv_Transform.hpp"
#include "geometry_msgs/pdu_ctype_conv_Twist.hpp"
#include "geometry_msgs/pdu_ctype_conv_Vector3.hpp"
#include "hako_srv_msgs/pdu_ctype_conv_PersonStepResponse.hpp"
#include "hako_srv_msgs/pdu_ctype_conv_ServiceResponseHeader.hpp"
#include "sensor_msgs/pdu_ctype_conv_JointState.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_PersonStepResponsePacket(const char* heap_ptr, Hako_PersonStepResponsePacket &src, hako_srv_msgs::msg::PersonStepResponsePacket &dst)
{
    // Struct convert
    _pdu2ros_ServiceResponseHeader(heap_ptr, src.header, dst.header);
    // Struct convert
    _pdu2ros_PersonStepResponse(heap_ptr, src.body, dst.body);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_PersonStepResponsePacket(Hako_PersonStepResponsePacket &src, hako_srv_msgs::msg::PersonStepResponsePacket &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_PersonStepResponsePacket((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_PersonStepResponsePacket(hako_srv_msgs::msg::PersonStepResponsePacket &src, Hako_PersonStepResponsePacket &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!_ros2pdu_ServiceResponseHeader(src.header, dst.header, dynamic_memory)) {
            return false;
        }
        // struct convert
        if (!_ros2pdu_PersonStepResponse(src.body, dst.body, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_PersonStepResponsePacket(hako_srv_msgs::msg::PersonStepResponsePacket &src, Hako_PersonStepResponsePacket** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_PersonStepResponsePacket out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_PersonStepResponsePacket(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_PersonStepResponsePacket), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_PersonStepResponsePacket));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_PersonStepResponsePacket*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_PersonStepResponsePacket() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_PersonStepResponsePacket(hako_srv_msgs::msg::PersonStepResponsePacket &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_PersonStepResponsePacket out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_PersonStepResponsePacket(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "PersonStepResponsePacket" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("PersonStepResponsePacket", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_PersonStepResponsePacket* hako_create_empty_pdu_PersonStepResponsePacket(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_PersonStepResponsePacket), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_PersonStepResponsePacket*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_PersonStepResponsePacket_HPP_ */
