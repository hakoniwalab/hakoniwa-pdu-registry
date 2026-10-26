#ifndef _PDU_CTYPE_CONV_HAKO_hako_msgs_LightStateArray_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_msgs_LightStateArray_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_LightStateArray.h"
/*
 * Dependent ros data
 */
#include "hako_msgs/msg/light_state_array.hpp"

/*
 * Dependent Convertors
 */
#include "hako_msgs/pdu_ctype_conv_LightState.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_LightStateArray_lights(const char* heap_ptr, Hako_LightStateArray &src, hako_msgs::msg::LightStateArray &dst)
{
    // Convert using len and off
    int offset = src._lights_off;
    int length = src._lights_len;
    if (length > 0) {
        dst.lights.resize(length);
        Hako_LightState *temp_struct_ptr = (Hako_LightState *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_LightState(heap_ptr, *temp_struct_ptr, dst.lights[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int _pdu2ros_LightStateArray(const char* heap_ptr, Hako_LightStateArray &src, hako_msgs::msg::LightStateArray &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.stamp_usec, dst.stamp_usec);
    // string convertor
    dst.carrier = (const char*)src.carrier;
    // struct array convertor
    _pdu2ros_struct_array_LightStateArray_lights(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_LightStateArray(Hako_LightStateArray &src, hako_msgs::msg::LightStateArray &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_LightStateArray((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_LightStateArray_lights(hako_msgs::msg::LightStateArray &src, Hako_LightStateArray &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._lights_len = src.lights.size();
    if (dst._lights_len > 0) {
        Hako_LightState* temp_struct_ptr = (Hako_LightState*)dynamic_memory.allocate(dst._lights_len, sizeof(Hako_LightState));
        dst._lights_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._lights_len; ++i) {
            _ros2pdu_LightState(src.lights[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._lights_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_LightStateArray(hako_msgs::msg::LightStateArray &src, Hako_LightStateArray &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.stamp_usec, dst.stamp_usec);
        // string convertor
        (void)hako_convert_ros2pdu_array(
            src.carrier, src.carrier.length(),
            dst.carrier, M_ARRAY_SIZE(Hako_LightStateArray, char, carrier));
        dst.carrier[src.carrier.length()] = '\0';
        //struct array convert
        _ros2pdu_struct_array_LightStateArray_lights(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_LightStateArray(hako_msgs::msg::LightStateArray &src, Hako_LightStateArray** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_LightStateArray out;
    if (!_ros2pdu_LightStateArray(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_LightStateArray), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_LightStateArray));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_LightStateArray*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_LightStateArray* hako_create_empty_pdu_LightStateArray(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_LightStateArray), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_LightStateArray*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_msgs_LightStateArray_HPP_ */
