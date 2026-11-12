#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_RenderObject_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_RenderObject_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_RenderObject.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/render_object.hpp"

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

static inline int _pdu2ros_RenderObject(const char* heap_ptr, Hako_RenderObject &src, hako_srv_msgs::msg::RenderObject &dst)
{
    // string convertor
    dst.name = hako_convert_string_from_pdu(src.name, M_SIZE(Hako_RenderObject, name));
    // string convertor
    dst.model = hako_convert_string_from_pdu(src.model, M_SIZE(Hako_RenderObject, model));
    // Struct convert
    _pdu2ros_Pose(heap_ptr, src.pose, dst.pose);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_RenderObject(Hako_RenderObject &src, hako_srv_msgs::msg::RenderObject &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_RenderObject((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_RenderObject(hako_srv_msgs::msg::RenderObject &src, Hako_RenderObject &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // string convertor
        hako_convert_string_to_pdu(src.name, dst.name, M_SIZE(Hako_RenderObject, name));
        // string convertor
        hako_convert_string_to_pdu(src.model, dst.model, M_SIZE(Hako_RenderObject, model));
        // struct convert
        if (!_ros2pdu_Pose(src.pose, dst.pose, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_RenderObject(hako_srv_msgs::msg::RenderObject &src, Hako_RenderObject** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_RenderObject out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_RenderObject(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_RenderObject), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_RenderObject));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_RenderObject*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_RenderObject() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_RenderObject(hako_srv_msgs::msg::RenderObject &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_RenderObject out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_RenderObject(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "RenderObject" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("RenderObject", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_RenderObject* hako_create_empty_pdu_RenderObject(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_RenderObject), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_RenderObject*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_RenderObject_HPP_ */
