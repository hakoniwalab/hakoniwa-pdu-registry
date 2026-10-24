#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_RenderCameraFrameRequest_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_RenderCameraFrameRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_RenderCameraFrameRequest.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/render_camera_frame_request.hpp"

/*
 * Dependent Convertors
 */
#include "geometry_msgs/pdu_ctype_conv_Point.hpp"
#include "geometry_msgs/pdu_ctype_conv_Pose.hpp"
#include "geometry_msgs/pdu_ctype_conv_Quaternion.hpp"
#include "hako_srv_msgs/pdu_ctype_conv_RenderObject.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_RenderCameraFrameRequest_objects(const char* heap_ptr, Hako_RenderCameraFrameRequest &src, hako_srv_msgs::msg::RenderCameraFrameRequest &dst)
{
    // Convert using len and off
    int offset = src._objects_off;
    int length = src._objects_len;
    if (length > 0) {
        dst.objects.resize(length);
        Hako_RenderObject *temp_struct_ptr = (Hako_RenderObject *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_RenderObject(heap_ptr, *temp_struct_ptr, dst.objects[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int _pdu2ros_RenderCameraFrameRequest(const char* heap_ptr, Hako_RenderCameraFrameRequest &src, hako_srv_msgs::msg::RenderCameraFrameRequest &dst)
{
    // string convertor
    dst.camera_name = (const char*)src.camera_name;
    // primitive convert
    hako_convert_pdu2ros(src.sim_time_usec, dst.sim_time_usec);
    // Struct convert
    _pdu2ros_Pose(heap_ptr, src.camera_pose, dst.camera_pose);
    // primitive convert
    hako_convert_pdu2ros(src.outputs, dst.outputs);
    // struct array convertor
    _pdu2ros_struct_array_RenderCameraFrameRequest_objects(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_RenderCameraFrameRequest(Hako_RenderCameraFrameRequest &src, hako_srv_msgs::msg::RenderCameraFrameRequest &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_RenderCameraFrameRequest((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_RenderCameraFrameRequest_objects(hako_srv_msgs::msg::RenderCameraFrameRequest &src, Hako_RenderCameraFrameRequest &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._objects_len = src.objects.size();
    if (dst._objects_len > 0) {
        Hako_RenderObject* temp_struct_ptr = (Hako_RenderObject*)dynamic_memory.allocate(dst._objects_len, sizeof(Hako_RenderObject));
        dst._objects_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._objects_len; ++i) {
            _ros2pdu_RenderObject(src.objects[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._objects_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_RenderCameraFrameRequest(hako_srv_msgs::msg::RenderCameraFrameRequest &src, Hako_RenderCameraFrameRequest &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // string convertor
        (void)hako_convert_ros2pdu_array(
            src.camera_name, src.camera_name.length(),
            dst.camera_name, M_ARRAY_SIZE(Hako_RenderCameraFrameRequest, char, camera_name));
        dst.camera_name[src.camera_name.length()] = '\0';
        // primitive convert
        hako_convert_ros2pdu(src.sim_time_usec, dst.sim_time_usec);
        // struct convert
        _ros2pdu_Pose(src.camera_pose, dst.camera_pose, dynamic_memory);
        // primitive convert
        hako_convert_ros2pdu(src.outputs, dst.outputs);
        //struct array convert
        _ros2pdu_struct_array_RenderCameraFrameRequest_objects(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_RenderCameraFrameRequest(hako_srv_msgs::msg::RenderCameraFrameRequest &src, Hako_RenderCameraFrameRequest** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_RenderCameraFrameRequest out;
    if (!_ros2pdu_RenderCameraFrameRequest(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_RenderCameraFrameRequest), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_RenderCameraFrameRequest));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_RenderCameraFrameRequest*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_RenderCameraFrameRequest* hako_create_empty_pdu_RenderCameraFrameRequest(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_RenderCameraFrameRequest), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_RenderCameraFrameRequest*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_RenderCameraFrameRequest_HPP_ */
