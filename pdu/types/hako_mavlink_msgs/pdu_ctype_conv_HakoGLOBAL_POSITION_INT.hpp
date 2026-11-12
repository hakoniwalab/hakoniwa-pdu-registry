#ifndef _PDU_CTYPE_CONV_HAKO_hako_mavlink_msgs_HakoGLOBAL_POSITION_INT_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_mavlink_msgs_HakoGLOBAL_POSITION_INT_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_mavlink_msgs/pdu_ctype_HakoGLOBAL_POSITION_INT.h"
/*
 * Dependent ros data
 */
#include "hako_mavlink_msgs/msg/hako_g_l_o_b_a_l__p_o_s_i_t_i_o_n__i_n_t.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_HakoGLOBAL_POSITION_INT(const char* heap_ptr, Hako_HakoGLOBAL_POSITION_INT &src, hako_mavlink_msgs::msg::HakoGLOBAL_POSITION_INT &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.time_boot_ms, dst.time_boot_ms);
    // primitive convert
    hako_convert_pdu2ros(src.lat, dst.lat);
    // primitive convert
    hako_convert_pdu2ros(src.lon, dst.lon);
    // primitive convert
    hako_convert_pdu2ros(src.alt, dst.alt);
    // primitive convert
    hako_convert_pdu2ros(src.relative_alt, dst.relative_alt);
    // primitive convert
    hako_convert_pdu2ros(src.vx, dst.vx);
    // primitive convert
    hako_convert_pdu2ros(src.vy, dst.vy);
    // primitive convert
    hako_convert_pdu2ros(src.vz, dst.vz);
    // primitive convert
    hako_convert_pdu2ros(src.hdg, dst.hdg);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_HakoGLOBAL_POSITION_INT(Hako_HakoGLOBAL_POSITION_INT &src, hako_mavlink_msgs::msg::HakoGLOBAL_POSITION_INT &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_HakoGLOBAL_POSITION_INT((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_HakoGLOBAL_POSITION_INT(hako_mavlink_msgs::msg::HakoGLOBAL_POSITION_INT &src, Hako_HakoGLOBAL_POSITION_INT &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.time_boot_ms, dst.time_boot_ms);
        // primitive convert
        hako_convert_ros2pdu(src.lat, dst.lat);
        // primitive convert
        hako_convert_ros2pdu(src.lon, dst.lon);
        // primitive convert
        hako_convert_ros2pdu(src.alt, dst.alt);
        // primitive convert
        hako_convert_ros2pdu(src.relative_alt, dst.relative_alt);
        // primitive convert
        hako_convert_ros2pdu(src.vx, dst.vx);
        // primitive convert
        hako_convert_ros2pdu(src.vy, dst.vy);
        // primitive convert
        hako_convert_ros2pdu(src.vz, dst.vz);
        // primitive convert
        hako_convert_ros2pdu(src.hdg, dst.hdg);
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_HakoGLOBAL_POSITION_INT(hako_mavlink_msgs::msg::HakoGLOBAL_POSITION_INT &src, Hako_HakoGLOBAL_POSITION_INT** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_HakoGLOBAL_POSITION_INT out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_HakoGLOBAL_POSITION_INT(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_HakoGLOBAL_POSITION_INT), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_HakoGLOBAL_POSITION_INT));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_HakoGLOBAL_POSITION_INT*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_HakoGLOBAL_POSITION_INT() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_HakoGLOBAL_POSITION_INT(hako_mavlink_msgs::msg::HakoGLOBAL_POSITION_INT &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_HakoGLOBAL_POSITION_INT out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_HakoGLOBAL_POSITION_INT(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "HakoGLOBAL_POSITION_INT" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("HakoGLOBAL_POSITION_INT", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_HakoGLOBAL_POSITION_INT* hako_create_empty_pdu_HakoGLOBAL_POSITION_INT(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_HakoGLOBAL_POSITION_INT), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_HakoGLOBAL_POSITION_INT*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_mavlink_msgs_HakoGLOBAL_POSITION_INT_HPP_ */
