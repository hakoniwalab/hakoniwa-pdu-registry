#ifndef _PDU_CTYPE_CONV_HAKO_geometry_msgs_PoseArray_HPP_
#define _PDU_CTYPE_CONV_HAKO_geometry_msgs_PoseArray_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_PoseArray.h"
/*
 * Dependent ros data
 */
#include "geometry_msgs/msg/pose_array.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "geometry_msgs/pdu_ctype_conv_Point.hpp"
#include "geometry_msgs/pdu_ctype_conv_Pose.hpp"
#include "geometry_msgs/pdu_ctype_conv_Quaternion.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_PoseArray_poses(const char* heap_ptr, Hako_PoseArray &src, geometry_msgs::msg::PoseArray &dst)
{
    // Convert using len and off
    int offset = src._poses_off;
    int length = src._poses_len;
    if (length > 0) {
        dst.poses.resize(length);
        Hako_Pose *temp_struct_ptr = (Hako_Pose *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_Pose(heap_ptr, *temp_struct_ptr, dst.poses[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int _pdu2ros_PoseArray(const char* heap_ptr, Hako_PoseArray &src, geometry_msgs::msg::PoseArray &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // struct array convertor
    _pdu2ros_struct_array_PoseArray_poses(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_PoseArray(Hako_PoseArray &src, geometry_msgs::msg::PoseArray &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_PoseArray((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_PoseArray_poses(geometry_msgs::msg::PoseArray &src, Hako_PoseArray &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._poses_len = src.poses.size();
    if (dst._poses_len > 0) {
        Hako_Pose* temp_struct_ptr = (Hako_Pose*)dynamic_memory.allocate(dst._poses_len, sizeof(Hako_Pose));
        dst._poses_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._poses_len; ++i) {
            _ros2pdu_Pose(src.poses[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._poses_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_PoseArray(geometry_msgs::msg::PoseArray &src, Hako_PoseArray &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_Header(src.header, dst.header, dynamic_memory);
        //struct array convert
        _ros2pdu_struct_array_PoseArray_poses(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_PoseArray(geometry_msgs::msg::PoseArray &src, Hako_PoseArray** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_PoseArray out;
    if (!_ros2pdu_PoseArray(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_PoseArray), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_PoseArray));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_PoseArray*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_PoseArray* hako_create_empty_pdu_PoseArray(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_PoseArray), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_PoseArray*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_geometry_msgs_PoseArray_HPP_ */
