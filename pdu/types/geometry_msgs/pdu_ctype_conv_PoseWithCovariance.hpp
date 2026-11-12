#ifndef _PDU_CTYPE_CONV_HAKO_geometry_msgs_PoseWithCovariance_HPP_
#define _PDU_CTYPE_CONV_HAKO_geometry_msgs_PoseWithCovariance_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_PoseWithCovariance.h"
/*
 * Dependent ros data
 */
#include "geometry_msgs/msg/pose_with_covariance.hpp"

/*
 * Dependent Convertors
 */
#include "geometry_msgs/pdu_ctype_conv_Point.hpp"
#include "geometry_msgs/pdu_ctype_conv_Pose.hpp"
#include "geometry_msgs/pdu_ctype_conv_Quaternion.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_PoseWithCovariance_covariance(const char* heap_ptr, Hako_PoseWithCovariance &src, geometry_msgs::msg::PoseWithCovariance &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 36; ++i) {
        hako_convert_pdu2ros(src.covariance[i], dst.covariance[i]);
    }
    return 0;
}

static inline int _pdu2ros_PoseWithCovariance(const char* heap_ptr, Hako_PoseWithCovariance &src, geometry_msgs::msg::PoseWithCovariance &dst)
{
    // Struct convert
    _pdu2ros_Pose(heap_ptr, src.pose, dst.pose);
    // primitive array convertor
    _pdu2ros_primitive_array_PoseWithCovariance_covariance(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_PoseWithCovariance(Hako_PoseWithCovariance &src, geometry_msgs::msg::PoseWithCovariance &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_PoseWithCovariance((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_PoseWithCovariance_covariance(geometry_msgs::msg::PoseWithCovariance &src, Hako_PoseWithCovariance &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 36
    (void)dynamic_memory;
    (void)hako_convert_ros2pdu_array(
        src.covariance, src.covariance.size(),
        dst.covariance, M_ARRAY_SIZE(Hako_PoseWithCovariance, Hako_float64, covariance));
    return true;
}

static inline bool _ros2pdu_PoseWithCovariance(geometry_msgs::msg::PoseWithCovariance &src, Hako_PoseWithCovariance &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!_ros2pdu_Pose(src.pose, dst.pose, dynamic_memory)) {
            return false;
        }
        //primitive array copy
        if (!_ros2pdu_primitive_array_PoseWithCovariance_covariance(src, dst, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_PoseWithCovariance(geometry_msgs::msg::PoseWithCovariance &src, Hako_PoseWithCovariance** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_PoseWithCovariance out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_PoseWithCovariance(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_PoseWithCovariance), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_PoseWithCovariance));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_PoseWithCovariance*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_PoseWithCovariance() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_PoseWithCovariance(geometry_msgs::msg::PoseWithCovariance &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_PoseWithCovariance out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_PoseWithCovariance(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "PoseWithCovariance" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("PoseWithCovariance", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_PoseWithCovariance* hako_create_empty_pdu_PoseWithCovariance(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_PoseWithCovariance), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_PoseWithCovariance*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_geometry_msgs_PoseWithCovariance_HPP_ */
