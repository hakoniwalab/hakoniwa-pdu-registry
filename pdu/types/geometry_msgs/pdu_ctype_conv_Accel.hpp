#ifndef _PDU_CTYPE_CONV_HAKO_geometry_msgs_Accel_HPP_
#define _PDU_CTYPE_CONV_HAKO_geometry_msgs_Accel_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_Accel.h"
/*
 * Dependent ros data
 */
#include "geometry_msgs/msg/accel.hpp"

/*
 * Dependent Convertors
 */
#include "geometry_msgs/pdu_ctype_conv_Vector3.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_Accel(const char* heap_ptr, Hako_Accel &src, geometry_msgs::msg::Accel &dst)
{
    // Struct convert
    _pdu2ros_Vector3(heap_ptr, src.linear, dst.linear);
    // Struct convert
    _pdu2ros_Vector3(heap_ptr, src.angular, dst.angular);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_Accel(Hako_Accel &src, geometry_msgs::msg::Accel &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_Accel((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_Accel(geometry_msgs::msg::Accel &src, Hako_Accel &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!_ros2pdu_Vector3(src.linear, dst.linear, dynamic_memory)) {
            return false;
        }
        // struct convert
        if (!_ros2pdu_Vector3(src.angular, dst.angular, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_Accel(geometry_msgs::msg::Accel &src, Hako_Accel** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Accel out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Accel(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Accel), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Accel));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Accel*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_Accel() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_Accel(geometry_msgs::msg::Accel &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_Accel out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Accel(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "Accel" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("Accel", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_Accel* hako_create_empty_pdu_Accel(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Accel), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Accel*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_geometry_msgs_Accel_HPP_ */
