#ifndef _PDU_CTYPE_CONV_HAKO_hako_msgs_LightState_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_msgs_LightState_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_LightState.h"
/*
 * Dependent ros data
 */
#include "hako_msgs/msg/light_state.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_LightState(const char* heap_ptr, Hako_LightState &src, hako_msgs::msg::LightState &dst)
{
    // string convertor
    dst.source = hako_convert_string_from_pdu(src.source, M_SIZE(Hako_LightState, source));
    // primitive convert
    hako_convert_pdu2ros(src.mode, dst.mode);
    // primitive convert
    hako_convert_pdu2ros(src.luminous_intensity_scale, dst.luminous_intensity_scale);
    // primitive convert
    hako_convert_pdu2ros(src.is_lit, dst.is_lit);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_LightState(Hako_LightState &src, hako_msgs::msg::LightState &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_LightState((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_LightState(hako_msgs::msg::LightState &src, Hako_LightState &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // string convertor
        hako_convert_string_to_pdu(src.source, dst.source, M_SIZE(Hako_LightState, source));
        // primitive convert
        hako_convert_ros2pdu(src.mode, dst.mode);
        // primitive convert
        hako_convert_ros2pdu(src.luminous_intensity_scale, dst.luminous_intensity_scale);
        // primitive convert
        hako_convert_ros2pdu(src.is_lit, dst.is_lit);
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_LightState(hako_msgs::msg::LightState &src, Hako_LightState** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_LightState out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_LightState(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_LightState), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_LightState));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_LightState*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_LightState() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_LightState(hako_msgs::msg::LightState &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_LightState out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_LightState(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "LightState" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("LightState", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_LightState* hako_create_empty_pdu_LightState(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_LightState), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_LightState*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_msgs_LightState_HPP_ */
