#ifndef _PDU_CTYPE_CONV_HAKO_ev3_msgs_Ev3PduSensorHeader_HPP_
#define _PDU_CTYPE_CONV_HAKO_ev3_msgs_Ev3PduSensorHeader_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "ev3_msgs/pdu_ctype_Ev3PduSensorHeader.h"
/*
 * Dependent ros data
 */
#include "ev3_msgs/msg/ev3_pdu_sensor_header.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_Ev3PduSensorHeader(const char* heap_ptr, Hako_Ev3PduSensorHeader &src, ev3_msgs::msg::Ev3PduSensorHeader &dst)
{
    // string convertor
    dst.name = hako_convert_string_from_pdu(src.name, M_SIZE(Hako_Ev3PduSensorHeader, name));
    // primitive convert
    hako_convert_pdu2ros(src.version, dst.version);
    // primitive convert
    hako_convert_pdu2ros(src.hakoniwa_time, dst.hakoniwa_time);
    // primitive convert
    hako_convert_pdu2ros(src.ext_off, dst.ext_off);
    // primitive convert
    hako_convert_pdu2ros(src.ext_size, dst.ext_size);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_Ev3PduSensorHeader(Hako_Ev3PduSensorHeader &src, ev3_msgs::msg::Ev3PduSensorHeader &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_Ev3PduSensorHeader((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_Ev3PduSensorHeader(ev3_msgs::msg::Ev3PduSensorHeader &src, Hako_Ev3PduSensorHeader &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // string convertor
        hako_convert_string_to_pdu(src.name, dst.name, M_SIZE(Hako_Ev3PduSensorHeader, name));
        // primitive convert
        hako_convert_ros2pdu(src.version, dst.version);
        // primitive convert
        hako_convert_ros2pdu(src.hakoniwa_time, dst.hakoniwa_time);
        // primitive convert
        hako_convert_ros2pdu(src.ext_off, dst.ext_off);
        // primitive convert
        hako_convert_ros2pdu(src.ext_size, dst.ext_size);
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_Ev3PduSensorHeader(ev3_msgs::msg::Ev3PduSensorHeader &src, Hako_Ev3PduSensorHeader** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Ev3PduSensorHeader out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Ev3PduSensorHeader(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Ev3PduSensorHeader), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Ev3PduSensorHeader));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Ev3PduSensorHeader*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_Ev3PduSensorHeader() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_Ev3PduSensorHeader(ev3_msgs::msg::Ev3PduSensorHeader &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_Ev3PduSensorHeader out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Ev3PduSensorHeader(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "Ev3PduSensorHeader" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("Ev3PduSensorHeader", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_Ev3PduSensorHeader* hako_create_empty_pdu_Ev3PduSensorHeader(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Ev3PduSensorHeader), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Ev3PduSensorHeader*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_ev3_msgs_Ev3PduSensorHeader_HPP_ */
