#ifndef _PDU_CTYPE_CONV_HAKO_hako_msgs_Disturbance_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_msgs_Disturbance_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_Disturbance.h"
/*
 * Dependent ros data
 */
#include "hako_msgs/msg/disturbance.hpp"

/*
 * Dependent Convertors
 */
#include "geometry_msgs/pdu_ctype_conv_Point.hpp"
#include "geometry_msgs/pdu_ctype_conv_Vector3.hpp"
#include "hako_msgs/pdu_ctype_conv_DisturbanceAtm.hpp"
#include "hako_msgs/pdu_ctype_conv_DisturbanceBoundary.hpp"
#include "hako_msgs/pdu_ctype_conv_DisturbanceTemperature.hpp"
#include "hako_msgs/pdu_ctype_conv_DisturbanceUserCustom.hpp"
#include "hako_msgs/pdu_ctype_conv_DisturbanceWind.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_Disturbance_d_user_custom(const char* heap_ptr, Hako_Disturbance &src, hako_msgs::msg::Disturbance &dst)
{
    // Convert using len and off
    int offset = src._d_user_custom_off;
    int length = src._d_user_custom_len;
    if (length > 0) {
        dst.d_user_custom.resize(length);
        Hako_DisturbanceUserCustom *temp_struct_ptr = (Hako_DisturbanceUserCustom *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_DisturbanceUserCustom(heap_ptr, *temp_struct_ptr, dst.d_user_custom[i]);
            temp_struct_ptr++;
        }
    }
    else {
        dst.d_user_custom.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}

static inline int _pdu2ros_Disturbance(const char* heap_ptr, Hako_Disturbance &src, hako_msgs::msg::Disturbance &dst)
{
    // Struct convert
    _pdu2ros_DisturbanceTemperature(heap_ptr, src.d_temp, dst.d_temp);
    // Struct convert
    _pdu2ros_DisturbanceWind(heap_ptr, src.d_wind, dst.d_wind);
    // Struct convert
    _pdu2ros_DisturbanceAtm(heap_ptr, src.d_atm, dst.d_atm);
    // Struct convert
    _pdu2ros_DisturbanceBoundary(heap_ptr, src.d_boundary, dst.d_boundary);
    // struct array convertor
    _pdu2ros_struct_array_Disturbance_d_user_custom(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_Disturbance(Hako_Disturbance &src, hako_msgs::msg::Disturbance &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_Disturbance((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_Disturbance_d_user_custom(hako_msgs::msg::Disturbance &src, Hako_Disturbance &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._d_user_custom_len = src.d_user_custom.size();
    if (dst._d_user_custom_len > 0) {
        Hako_DisturbanceUserCustom* temp_struct_ptr = (Hako_DisturbanceUserCustom*)dynamic_memory.allocate(dst._d_user_custom_len, sizeof(Hako_DisturbanceUserCustom));
        dst._d_user_custom_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._d_user_custom_len; ++i) {
            if (!_ros2pdu_DisturbanceUserCustom(src.d_user_custom[i], *temp_struct_ptr, dynamic_memory)) {
                return false;
            }
            temp_struct_ptr++;
        }
    }
    else {
        dst._d_user_custom_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_Disturbance(hako_msgs::msg::Disturbance &src, Hako_Disturbance &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!_ros2pdu_DisturbanceTemperature(src.d_temp, dst.d_temp, dynamic_memory)) {
            return false;
        }
        // struct convert
        if (!_ros2pdu_DisturbanceWind(src.d_wind, dst.d_wind, dynamic_memory)) {
            return false;
        }
        // struct convert
        if (!_ros2pdu_DisturbanceAtm(src.d_atm, dst.d_atm, dynamic_memory)) {
            return false;
        }
        // struct convert
        if (!_ros2pdu_DisturbanceBoundary(src.d_boundary, dst.d_boundary, dynamic_memory)) {
            return false;
        }
        //struct array convert
        if (!_ros2pdu_struct_array_Disturbance_d_user_custom(src, dst, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_Disturbance(hako_msgs::msg::Disturbance &src, Hako_Disturbance** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Disturbance out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Disturbance(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Disturbance), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Disturbance));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Disturbance*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_Disturbance() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_Disturbance(hako_msgs::msg::Disturbance &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_Disturbance out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Disturbance(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "Disturbance" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("Disturbance", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_Disturbance* hako_create_empty_pdu_Disturbance(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Disturbance), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Disturbance*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_msgs_Disturbance_HPP_ */
