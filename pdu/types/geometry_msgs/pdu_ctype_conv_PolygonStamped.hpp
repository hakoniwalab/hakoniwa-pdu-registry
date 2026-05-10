#ifndef _PDU_CTYPE_CONV_HAKO_geometry_msgs_PolygonStamped_HPP_
#define _PDU_CTYPE_CONV_HAKO_geometry_msgs_PolygonStamped_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_PolygonStamped.h"
/*
 * Dependent ros data
 */
#include "geometry_msgs/msg/polygon_stamped.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "geometry_msgs/pdu_ctype_conv_Point32.hpp"
#include "geometry_msgs/pdu_ctype_conv_Polygon.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_PolygonStamped(const char* heap_ptr, Hako_PolygonStamped &src, geometry_msgs::msg::PolygonStamped &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // Struct convert
    _pdu2ros_Polygon(heap_ptr, src.polygon, dst.polygon);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_PolygonStamped(Hako_PolygonStamped &src, geometry_msgs::msg::PolygonStamped &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_PolygonStamped((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_PolygonStamped(geometry_msgs::msg::PolygonStamped &src, Hako_PolygonStamped &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_Header(src.header, dst.header, dynamic_memory);
        // struct convert
        _ros2pdu_Polygon(src.polygon, dst.polygon, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_PolygonStamped(geometry_msgs::msg::PolygonStamped &src, Hako_PolygonStamped** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_PolygonStamped out;
    if (!_ros2pdu_PolygonStamped(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_PolygonStamped), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_PolygonStamped));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_PolygonStamped*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_PolygonStamped* hako_create_empty_pdu_PolygonStamped(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_PolygonStamped), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_PolygonStamped*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_geometry_msgs_PolygonStamped_HPP_ */
