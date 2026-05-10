#ifndef _PDU_CTYPE_CONV_HAKO_nav_msgs_MapMetaData_HPP_
#define _PDU_CTYPE_CONV_HAKO_nav_msgs_MapMetaData_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "nav_msgs/pdu_ctype_MapMetaData.h"
/*
 * Dependent ros data
 */
#include "nav_msgs/msg/map_meta_data.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "geometry_msgs/pdu_ctype_conv_Point.hpp"
#include "geometry_msgs/pdu_ctype_conv_Pose.hpp"
#include "geometry_msgs/pdu_ctype_conv_Quaternion.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_MapMetaData(const char* heap_ptr, Hako_MapMetaData &src, nav_msgs::msg::MapMetaData &dst)
{
    // Struct convert
    _pdu2ros_Time(heap_ptr, src.map_load_time, dst.map_load_time);
    // primitive convert
    hako_convert_pdu2ros(src.resolution, dst.resolution);
    // primitive convert
    hako_convert_pdu2ros(src.width, dst.width);
    // primitive convert
    hako_convert_pdu2ros(src.height, dst.height);
    // Struct convert
    _pdu2ros_Pose(heap_ptr, src.origin, dst.origin);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_MapMetaData(Hako_MapMetaData &src, nav_msgs::msg::MapMetaData &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_MapMetaData((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_MapMetaData(nav_msgs::msg::MapMetaData &src, Hako_MapMetaData &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_Time(src.map_load_time, dst.map_load_time, dynamic_memory);
        // primitive convert
        hako_convert_ros2pdu(src.resolution, dst.resolution);
        // primitive convert
        hako_convert_ros2pdu(src.width, dst.width);
        // primitive convert
        hako_convert_ros2pdu(src.height, dst.height);
        // struct convert
        _ros2pdu_Pose(src.origin, dst.origin, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_MapMetaData(nav_msgs::msg::MapMetaData &src, Hako_MapMetaData** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_MapMetaData out;
    if (!_ros2pdu_MapMetaData(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_MapMetaData), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_MapMetaData));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_MapMetaData*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_MapMetaData* hako_create_empty_pdu_MapMetaData(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_MapMetaData), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_MapMetaData*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_nav_msgs_MapMetaData_HPP_ */
