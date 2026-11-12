#ifndef _PDU_CTYPE_CONV_HAKO_std_msgs_MultiArrayDimension_HPP_
#define _PDU_CTYPE_CONV_HAKO_std_msgs_MultiArrayDimension_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "std_msgs/pdu_ctype_MultiArrayDimension.h"
/*
 * Dependent ros data
 */
#include "std_msgs/msg/multi_array_dimension.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_MultiArrayDimension(const char* heap_ptr, Hako_MultiArrayDimension &src, std_msgs::msg::MultiArrayDimension &dst)
{
    // string convertor
    dst.label = hako_convert_string_from_pdu(src.label, M_SIZE(Hako_MultiArrayDimension, label));
    // primitive convert
    hako_convert_pdu2ros(src.size, dst.size);
    // primitive convert
    hako_convert_pdu2ros(src.stride, dst.stride);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_MultiArrayDimension(Hako_MultiArrayDimension &src, std_msgs::msg::MultiArrayDimension &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_MultiArrayDimension((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_MultiArrayDimension(std_msgs::msg::MultiArrayDimension &src, Hako_MultiArrayDimension &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // string convertor
        hako_convert_string_to_pdu(src.label, dst.label, M_SIZE(Hako_MultiArrayDimension, label));
        // primitive convert
        hako_convert_ros2pdu(src.size, dst.size);
        // primitive convert
        hako_convert_ros2pdu(src.stride, dst.stride);
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_MultiArrayDimension(std_msgs::msg::MultiArrayDimension &src, Hako_MultiArrayDimension** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_MultiArrayDimension out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_MultiArrayDimension(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_MultiArrayDimension), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_MultiArrayDimension));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_MultiArrayDimension*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_MultiArrayDimension() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_MultiArrayDimension(std_msgs::msg::MultiArrayDimension &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_MultiArrayDimension out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_MultiArrayDimension(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "MultiArrayDimension" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("MultiArrayDimension", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_MultiArrayDimension* hako_create_empty_pdu_MultiArrayDimension(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_MultiArrayDimension), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_MultiArrayDimension*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_std_msgs_MultiArrayDimension_HPP_ */
