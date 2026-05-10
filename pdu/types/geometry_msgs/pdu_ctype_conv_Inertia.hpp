#ifndef _PDU_CTYPE_CONV_HAKO_geometry_msgs_Inertia_HPP_
#define _PDU_CTYPE_CONV_HAKO_geometry_msgs_Inertia_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_Inertia.h"
/*
 * Dependent ros data
 */
#include "geometry_msgs/msg/inertia.hpp"

/*
 * Dependent Convertors
 */
#include "geometry_msgs/pdu_ctype_conv_Vector3.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_Inertia(const char* heap_ptr, Hako_Inertia &src, geometry_msgs::msg::Inertia &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.m, dst.m);
    // Struct convert
    _pdu2ros_Vector3(heap_ptr, src.com, dst.com);
    // primitive convert
    hako_convert_pdu2ros(src.ixx, dst.ixx);
    // primitive convert
    hako_convert_pdu2ros(src.ixy, dst.ixy);
    // primitive convert
    hako_convert_pdu2ros(src.ixz, dst.ixz);
    // primitive convert
    hako_convert_pdu2ros(src.iyy, dst.iyy);
    // primitive convert
    hako_convert_pdu2ros(src.iyz, dst.iyz);
    // primitive convert
    hako_convert_pdu2ros(src.izz, dst.izz);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_Inertia(Hako_Inertia &src, geometry_msgs::msg::Inertia &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_Inertia((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_Inertia(geometry_msgs::msg::Inertia &src, Hako_Inertia &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.m, dst.m);
        // struct convert
        _ros2pdu_Vector3(src.com, dst.com, dynamic_memory);
        // primitive convert
        hako_convert_ros2pdu(src.ixx, dst.ixx);
        // primitive convert
        hako_convert_ros2pdu(src.ixy, dst.ixy);
        // primitive convert
        hako_convert_ros2pdu(src.ixz, dst.ixz);
        // primitive convert
        hako_convert_ros2pdu(src.iyy, dst.iyy);
        // primitive convert
        hako_convert_ros2pdu(src.iyz, dst.iyz);
        // primitive convert
        hako_convert_ros2pdu(src.izz, dst.izz);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_Inertia(geometry_msgs::msg::Inertia &src, Hako_Inertia** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Inertia out;
    if (!_ros2pdu_Inertia(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Inertia), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Inertia));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Inertia*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Inertia* hako_create_empty_pdu_Inertia(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Inertia), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Inertia*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_geometry_msgs_Inertia_HPP_ */
