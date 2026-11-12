#ifndef _PDU_CTYPE_CONV_HAKO_tf2_msgs_TF2Error_HPP_
#define _PDU_CTYPE_CONV_HAKO_tf2_msgs_TF2Error_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "tf2_msgs/pdu_ctype_TF2Error.h"
/*
 * Dependent ros data
 */
#include "tf2_msgs/msg/t_f2_error.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_TF2Error(const char* heap_ptr, Hako_TF2Error &src, tf2_msgs::msg::TF2Error &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.error, dst.error);
    // string convertor
    dst.error_string = hako_convert_string_from_pdu(src.error_string, M_SIZE(Hako_TF2Error, error_string));
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_TF2Error(Hako_TF2Error &src, tf2_msgs::msg::TF2Error &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_TF2Error((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_TF2Error(tf2_msgs::msg::TF2Error &src, Hako_TF2Error &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.error, dst.error);
        // string convertor
        hako_convert_string_to_pdu(src.error_string, dst.error_string, M_SIZE(Hako_TF2Error, error_string));
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_TF2Error(tf2_msgs::msg::TF2Error &src, Hako_TF2Error** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_TF2Error out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_TF2Error(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_TF2Error), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_TF2Error));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_TF2Error*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_TF2Error() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_TF2Error(tf2_msgs::msg::TF2Error &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_TF2Error out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_TF2Error(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "TF2Error" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("TF2Error", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_TF2Error* hako_create_empty_pdu_TF2Error(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_TF2Error), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_TF2Error*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_tf2_msgs_TF2Error_HPP_ */
