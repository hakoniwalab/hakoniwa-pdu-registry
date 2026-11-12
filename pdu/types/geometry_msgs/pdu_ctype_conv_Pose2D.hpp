#ifndef _PDU_CTYPE_CONV_HAKO_geometry_msgs_Pose2D_HPP_
#define _PDU_CTYPE_CONV_HAKO_geometry_msgs_Pose2D_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_Pose2D.h"
/*
 * Dependent ros data
 */
#include "geometry_msgs/msg/pose2_d.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_Pose2D(const char* heap_ptr, Hako_Pose2D &src, geometry_msgs::msg::Pose2D &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.x, dst.x);
    // primitive convert
    hako_convert_pdu2ros(src.y, dst.y);
    // primitive convert
    hako_convert_pdu2ros(src.theta, dst.theta);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_Pose2D(Hako_Pose2D &src, geometry_msgs::msg::Pose2D &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_Pose2D((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_Pose2D(geometry_msgs::msg::Pose2D &src, Hako_Pose2D &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.x, dst.x);
        // primitive convert
        hako_convert_ros2pdu(src.y, dst.y);
        // primitive convert
        hako_convert_ros2pdu(src.theta, dst.theta);
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_Pose2D(geometry_msgs::msg::Pose2D &src, Hako_Pose2D** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Pose2D out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Pose2D(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Pose2D), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Pose2D));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Pose2D*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_Pose2D() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_Pose2D(geometry_msgs::msg::Pose2D &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_Pose2D out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Pose2D(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "Pose2D" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("Pose2D", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_Pose2D* hako_create_empty_pdu_Pose2D(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Pose2D), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Pose2D*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_geometry_msgs_Pose2D_HPP_ */
