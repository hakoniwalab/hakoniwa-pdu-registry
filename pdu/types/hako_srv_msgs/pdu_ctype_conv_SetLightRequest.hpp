#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_SetLightRequest_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_SetLightRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_SetLightRequest.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/set_light_request.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_SetLightRequest(const char* heap_ptr, Hako_SetLightRequest &src, hako_srv_msgs::msg::SetLightRequest &dst)
{
    // string convertor
    dst.source = (const char*)src.source;
    // primitive convert
    hako_convert_pdu2ros(src.mode, dst.mode);
    // primitive convert
    hako_convert_pdu2ros(src.luminous_intensity_scale, dst.luminous_intensity_scale);
    // primitive convert
    hako_convert_pdu2ros(src.flashing_on_s, dst.flashing_on_s);
    // primitive convert
    hako_convert_pdu2ros(src.flashing_off_s, dst.flashing_off_s);
    // primitive convert
    hako_convert_pdu2ros(src.transition_s, dst.transition_s);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_SetLightRequest(Hako_SetLightRequest &src, hako_srv_msgs::msg::SetLightRequest &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_SetLightRequest((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_SetLightRequest(hako_srv_msgs::msg::SetLightRequest &src, Hako_SetLightRequest &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // string convertor
        (void)hako_convert_ros2pdu_array(
            src.source, src.source.length(),
            dst.source, M_ARRAY_SIZE(Hako_SetLightRequest, char, source));
        dst.source[src.source.length()] = '\0';
        // primitive convert
        hako_convert_ros2pdu(src.mode, dst.mode);
        // primitive convert
        hako_convert_ros2pdu(src.luminous_intensity_scale, dst.luminous_intensity_scale);
        // primitive convert
        hako_convert_ros2pdu(src.flashing_on_s, dst.flashing_on_s);
        // primitive convert
        hako_convert_ros2pdu(src.flashing_off_s, dst.flashing_off_s);
        // primitive convert
        hako_convert_ros2pdu(src.transition_s, dst.transition_s);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_SetLightRequest(hako_srv_msgs::msg::SetLightRequest &src, Hako_SetLightRequest** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_SetLightRequest out;
    if (!_ros2pdu_SetLightRequest(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_SetLightRequest), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_SetLightRequest));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_SetLightRequest*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_SetLightRequest* hako_create_empty_pdu_SetLightRequest(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_SetLightRequest), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_SetLightRequest*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_SetLightRequest_HPP_ */
