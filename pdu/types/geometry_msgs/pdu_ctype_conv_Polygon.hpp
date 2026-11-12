#ifndef _PDU_CTYPE_CONV_HAKO_geometry_msgs_Polygon_HPP_
#define _PDU_CTYPE_CONV_HAKO_geometry_msgs_Polygon_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_Polygon.h"
/*
 * Dependent ros data
 */
#include "geometry_msgs/msg/polygon.hpp"

/*
 * Dependent Convertors
 */
#include "geometry_msgs/pdu_ctype_conv_Point32.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_Polygon_points(const char* heap_ptr, Hako_Polygon &src, geometry_msgs::msg::Polygon &dst)
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
    else {
        dst.points.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}

static inline int _pdu2ros_Polygon(const char* heap_ptr, Hako_Polygon &src, geometry_msgs::msg::Polygon &dst)
{
    // struct array convertor
    _pdu2ros_struct_array_Polygon_points(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_Polygon(Hako_Polygon &src, geometry_msgs::msg::Polygon &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_Polygon((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_Polygon_points(geometry_msgs::msg::Polygon &src, Hako_Polygon &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._points_len = src.points.size();
    if (dst._points_len > 0) {
        Hako_Point32* temp_struct_ptr = (Hako_Point32*)dynamic_memory.allocate(dst._points_len, sizeof(Hako_Point32));
        dst._points_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._points_len; ++i) {
            if (!_ros2pdu_Point32(src.points[i], *temp_struct_ptr, dynamic_memory)) {
                return false;
            }
            temp_struct_ptr++;
        }
    }
    else {
        dst._points_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_Polygon(geometry_msgs::msg::Polygon &src, Hako_Polygon &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //struct array convert
        if (!_ros2pdu_struct_array_Polygon_points(src, dst, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_Polygon(geometry_msgs::msg::Polygon &src, Hako_Polygon** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Polygon out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Polygon(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Polygon), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Polygon));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Polygon*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_Polygon() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_Polygon(geometry_msgs::msg::Polygon &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_Polygon out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Polygon(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "Polygon" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("Polygon", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_Polygon* hako_create_empty_pdu_Polygon(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Polygon), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Polygon*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_geometry_msgs_Polygon_HPP_ */
