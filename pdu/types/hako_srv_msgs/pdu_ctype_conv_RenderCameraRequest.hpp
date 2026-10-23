#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_RenderCameraRequest_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_RenderCameraRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_RenderCameraRequest.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/render_camera_request.hpp"

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

static inline int _pdu2ros_RenderCameraRequest(const char* heap_ptr, Hako_RenderCameraRequest &src, hako_srv_msgs::msg::RenderCameraRequest &dst)
{
    // string convertor
    dst.camera_name = (const char*)src.camera_name;
    // primitive convert
    hako_convert_pdu2ros(src.sim_time_usec, dst.sim_time_usec);
    // Struct convert
    _pdu2ros_Pose(heap_ptr, src.camera_pose, dst.camera_pose);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_RenderCameraRequest(Hako_RenderCameraRequest &src, hako_srv_msgs::msg::RenderCameraRequest &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_RenderCameraRequest((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_RenderCameraRequest(hako_srv_msgs::msg::RenderCameraRequest &src, Hako_RenderCameraRequest &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // string convertor
        (void)hako_convert_ros2pdu_array(
            src.camera_name, src.camera_name.length(),
            dst.camera_name, M_ARRAY_SIZE(Hako_RenderCameraRequest, char, camera_name));
        dst.camera_name[src.camera_name.length()] = '\0';
        // primitive convert
        hako_convert_ros2pdu(src.sim_time_usec, dst.sim_time_usec);
        // struct convert
        _ros2pdu_Pose(src.camera_pose, dst.camera_pose, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_RenderCameraRequest(hako_srv_msgs::msg::RenderCameraRequest &src, Hako_RenderCameraRequest** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_RenderCameraRequest out;
    if (!_ros2pdu_RenderCameraRequest(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_RenderCameraRequest), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_RenderCameraRequest));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_RenderCameraRequest*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_RenderCameraRequest* hako_create_empty_pdu_RenderCameraRequest(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_RenderCameraRequest), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_RenderCameraRequest*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_RenderCameraRequest_HPP_ */
