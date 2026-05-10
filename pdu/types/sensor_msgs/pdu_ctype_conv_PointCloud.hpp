#ifndef _PDU_CTYPE_CONV_HAKO_sensor_msgs_PointCloud_HPP_
#define _PDU_CTYPE_CONV_HAKO_sensor_msgs_PointCloud_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_PointCloud.h"
/*
 * Dependent ros data
 */
#include "sensor_msgs/msg/point_cloud.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "geometry_msgs/pdu_ctype_conv_Point32.hpp"
#include "sensor_msgs/pdu_ctype_conv_ChannelFloat32.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_PointCloud_points(const char* heap_ptr, Hako_PointCloud &src, sensor_msgs::msg::PointCloud &dst)
{
    // Convert using len and off
    int offset = src._points_off;
    int length = src._points_len;
    if (length > 0) {
        dst.points.resize(length);
        Hako_Point32 *temp_struct_ptr = (Hako_Point32 *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_Point32(heap_ptr, *temp_struct_ptr, dst.points[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}
static inline int _pdu2ros_struct_array_PointCloud_channels(const char* heap_ptr, Hako_PointCloud &src, sensor_msgs::msg::PointCloud &dst)
{
    // Convert using len and off
    int offset = src._channels_off;
    int length = src._channels_len;
    if (length > 0) {
        dst.channels.resize(length);
        Hako_ChannelFloat32 *temp_struct_ptr = (Hako_ChannelFloat32 *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_ChannelFloat32(heap_ptr, *temp_struct_ptr, dst.channels[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int _pdu2ros_PointCloud(const char* heap_ptr, Hako_PointCloud &src, sensor_msgs::msg::PointCloud &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // struct array convertor
    _pdu2ros_struct_array_PointCloud_points(heap_ptr, src, dst);
    // struct array convertor
    _pdu2ros_struct_array_PointCloud_channels(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_PointCloud(Hako_PointCloud &src, sensor_msgs::msg::PointCloud &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_PointCloud((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_PointCloud_points(sensor_msgs::msg::PointCloud &src, Hako_PointCloud &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._points_len = src.points.size();
    if (dst._points_len > 0) {
        Hako_Point32* temp_struct_ptr = (Hako_Point32*)dynamic_memory.allocate(dst._points_len, sizeof(Hako_Point32));
        dst._points_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._points_len; ++i) {
            _ros2pdu_Point32(src.points[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._points_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool _ros2pdu_struct_array_PointCloud_channels(sensor_msgs::msg::PointCloud &src, Hako_PointCloud &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._channels_len = src.channels.size();
    if (dst._channels_len > 0) {
        Hako_ChannelFloat32* temp_struct_ptr = (Hako_ChannelFloat32*)dynamic_memory.allocate(dst._channels_len, sizeof(Hako_ChannelFloat32));
        dst._channels_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._channels_len; ++i) {
            _ros2pdu_ChannelFloat32(src.channels[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._channels_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_PointCloud(sensor_msgs::msg::PointCloud &src, Hako_PointCloud &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_Header(src.header, dst.header, dynamic_memory);
        //struct array convert
        _ros2pdu_struct_array_PointCloud_points(src, dst, dynamic_memory);
        //struct array convert
        _ros2pdu_struct_array_PointCloud_channels(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_PointCloud(sensor_msgs::msg::PointCloud &src, Hako_PointCloud** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_PointCloud out;
    if (!_ros2pdu_PointCloud(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_PointCloud), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_PointCloud));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_PointCloud*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_PointCloud* hako_create_empty_pdu_PointCloud(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_PointCloud), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_PointCloud*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sensor_msgs_PointCloud_HPP_ */
