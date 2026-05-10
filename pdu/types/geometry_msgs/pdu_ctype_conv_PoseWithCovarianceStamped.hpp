#ifndef _PDU_CTYPE_CONV_HAKO_geometry_msgs_PoseWithCovarianceStamped_HPP_
#define _PDU_CTYPE_CONV_HAKO_geometry_msgs_PoseWithCovarianceStamped_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_PoseWithCovarianceStamped.h"
/*
 * Dependent ros data
 */
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "geometry_msgs/pdu_ctype_conv_Point.hpp"
#include "geometry_msgs/pdu_ctype_conv_Pose.hpp"
#include "geometry_msgs/pdu_ctype_conv_PoseWithCovariance.hpp"
#include "geometry_msgs/pdu_ctype_conv_Quaternion.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_PoseWithCovarianceStamped(const char* heap_ptr, Hako_PoseWithCovarianceStamped &src, geometry_msgs::msg::PoseWithCovarianceStamped &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // Struct convert
    _pdu2ros_PoseWithCovariance(heap_ptr, src.pose, dst.pose);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_PoseWithCovarianceStamped(Hako_PoseWithCovarianceStamped &src, geometry_msgs::msg::PoseWithCovarianceStamped &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_PoseWithCovarianceStamped((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_PoseWithCovarianceStamped(geometry_msgs::msg::PoseWithCovarianceStamped &src, Hako_PoseWithCovarianceStamped &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_Header(src.header, dst.header, dynamic_memory);
        // struct convert
        _ros2pdu_PoseWithCovariance(src.pose, dst.pose, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_PoseWithCovarianceStamped(geometry_msgs::msg::PoseWithCovarianceStamped &src, Hako_PoseWithCovarianceStamped** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_PoseWithCovarianceStamped out;
    if (!_ros2pdu_PoseWithCovarianceStamped(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_PoseWithCovarianceStamped), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_PoseWithCovarianceStamped));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_PoseWithCovarianceStamped*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_PoseWithCovarianceStamped* hako_create_empty_pdu_PoseWithCovarianceStamped(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_PoseWithCovarianceStamped), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_PoseWithCovarianceStamped*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_geometry_msgs_PoseWithCovarianceStamped_HPP_ */
