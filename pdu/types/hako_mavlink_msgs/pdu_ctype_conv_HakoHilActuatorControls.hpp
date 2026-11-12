#ifndef _PDU_CTYPE_CONV_HAKO_hako_mavlink_msgs_HakoHilActuatorControls_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_mavlink_msgs_HakoHilActuatorControls_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_mavlink_msgs/pdu_ctype_HakoHilActuatorControls.h"
/*
 * Dependent ros data
 */
#include "hako_mavlink_msgs/msg/hako_hil_actuator_controls.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_HakoHilActuatorControls_controls(const char* heap_ptr, Hako_HakoHilActuatorControls &src, hako_mavlink_msgs::msg::HakoHilActuatorControls &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 16; ++i) {
        hako_convert_pdu2ros(src.controls[i], dst.controls[i]);
    }
    return 0;
}

static inline int _pdu2ros_HakoHilActuatorControls(const char* heap_ptr, Hako_HakoHilActuatorControls &src, hako_mavlink_msgs::msg::HakoHilActuatorControls &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.time_usec, dst.time_usec);
    // primitive array convertor
    _pdu2ros_primitive_array_HakoHilActuatorControls_controls(heap_ptr, src, dst);
    // primitive convert
    hako_convert_pdu2ros(src.mode, dst.mode);
    // primitive convert
    hako_convert_pdu2ros(src.flags, dst.flags);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_HakoHilActuatorControls(Hako_HakoHilActuatorControls &src, hako_mavlink_msgs::msg::HakoHilActuatorControls &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_HakoHilActuatorControls((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_HakoHilActuatorControls_controls(hako_mavlink_msgs::msg::HakoHilActuatorControls &src, Hako_HakoHilActuatorControls &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 16
    (void)dynamic_memory;
    (void)hako_convert_ros2pdu_array(
        src.controls, src.controls.size(),
        dst.controls, M_ARRAY_SIZE(Hako_HakoHilActuatorControls, Hako_float32, controls));
    return true;
}

static inline bool _ros2pdu_HakoHilActuatorControls(hako_mavlink_msgs::msg::HakoHilActuatorControls &src, Hako_HakoHilActuatorControls &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.time_usec, dst.time_usec);
        //primitive array copy
        if (!_ros2pdu_primitive_array_HakoHilActuatorControls_controls(src, dst, dynamic_memory)) {
            return false;
        }
        // primitive convert
        hako_convert_ros2pdu(src.mode, dst.mode);
        // primitive convert
        hako_convert_ros2pdu(src.flags, dst.flags);
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_HakoHilActuatorControls(hako_mavlink_msgs::msg::HakoHilActuatorControls &src, Hako_HakoHilActuatorControls** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_HakoHilActuatorControls out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_HakoHilActuatorControls(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_HakoHilActuatorControls), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_HakoHilActuatorControls));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_HakoHilActuatorControls*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_HakoHilActuatorControls() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_HakoHilActuatorControls(hako_mavlink_msgs::msg::HakoHilActuatorControls &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_HakoHilActuatorControls out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_HakoHilActuatorControls(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "HakoHilActuatorControls" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("HakoHilActuatorControls", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_HakoHilActuatorControls* hako_create_empty_pdu_HakoHilActuatorControls(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_HakoHilActuatorControls), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_HakoHilActuatorControls*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_mavlink_msgs_HakoHilActuatorControls_HPP_ */
