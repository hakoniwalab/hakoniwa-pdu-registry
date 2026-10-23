#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_RenderCameraFrameResponse_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_RenderCameraFrameResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_RenderCameraFrameResponse.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/render_camera_frame_response.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "sensor_msgs/pdu_ctype_conv_Image.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_RenderCameraFrameResponse(const char* heap_ptr, Hako_RenderCameraFrameResponse &src, hako_srv_msgs::msg::RenderCameraFrameResponse &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.result_code, dst.result_code);
    // primitive convert
    hako_convert_pdu2ros(src.sim_time_usec, dst.sim_time_usec);
    // Struct convert
    _pdu2ros_Image(heap_ptr, src.rgb, dst.rgb);
    // Struct convert
    _pdu2ros_Image(heap_ptr, src.depth, dst.depth);
    // Struct convert
    _pdu2ros_Image(heap_ptr, src.segmentation, dst.segmentation);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_RenderCameraFrameResponse(Hako_RenderCameraFrameResponse &src, hako_srv_msgs::msg::RenderCameraFrameResponse &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_RenderCameraFrameResponse((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_RenderCameraFrameResponse(hako_srv_msgs::msg::RenderCameraFrameResponse &src, Hako_RenderCameraFrameResponse &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.result_code, dst.result_code);
        // primitive convert
        hako_convert_ros2pdu(src.sim_time_usec, dst.sim_time_usec);
        // struct convert
        _ros2pdu_Image(src.rgb, dst.rgb, dynamic_memory);
        // struct convert
        _ros2pdu_Image(src.depth, dst.depth, dynamic_memory);
        // struct convert
        _ros2pdu_Image(src.segmentation, dst.segmentation, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_RenderCameraFrameResponse(hako_srv_msgs::msg::RenderCameraFrameResponse &src, Hako_RenderCameraFrameResponse** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_RenderCameraFrameResponse out;
    if (!_ros2pdu_RenderCameraFrameResponse(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_RenderCameraFrameResponse), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_RenderCameraFrameResponse));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_RenderCameraFrameResponse*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_RenderCameraFrameResponse* hako_create_empty_pdu_RenderCameraFrameResponse(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_RenderCameraFrameResponse), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_RenderCameraFrameResponse*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_RenderCameraFrameResponse_HPP_ */
