#ifndef _PDU_CTYPE_CONV_HAKO_hako_msgs_Collision_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_msgs_Collision_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_Collision.h"
/*
 * Dependent ros data
 */
#include "hako_msgs/msg/collision.hpp"

/*
 * Dependent Convertors
 */
#include "geometry_msgs/pdu_ctype_conv_Point.hpp"
#include "geometry_msgs/pdu_ctype_conv_Vector3.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_Collision_contact_position(const char* heap_ptr, Hako_Collision &src, hako_msgs::msg::Collision &dst)
{
    // Fixed size array convertor
    for (int i = 0; i < 10; ++i) {
        _pdu2ros_Point(heap_ptr, src.contact_position[i], dst.contact_position[i]);
    }
    return 0;
}

static inline int _pdu2ros_Collision(const char* heap_ptr, Hako_Collision &src, hako_msgs::msg::Collision &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.collision, dst.collision);
    // primitive convert
    hako_convert_pdu2ros(src.contact_num, dst.contact_num);
    // Struct convert
    _pdu2ros_Vector3(heap_ptr, src.relative_velocity, dst.relative_velocity);
    // struct array convertor
    _pdu2ros_struct_array_Collision_contact_position(heap_ptr, src, dst);
    // primitive convert
    hako_convert_pdu2ros(src.restitution_coefficient, dst.restitution_coefficient);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_Collision(Hako_Collision &src, hako_msgs::msg::Collision &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_Collision((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_Collision_contact_position(hako_msgs::msg::Collision &src, Hako_Collision &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    //array size is fixed
    for (int i = 0; i < 10; ++i) {
        if (!_ros2pdu_Point(src.contact_position[i], dst.contact_position[i], dynamic_memory)) {
            return false;
        }
    }
    return true;
}

static inline bool _ros2pdu_Collision(hako_msgs::msg::Collision &src, Hako_Collision &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.collision, dst.collision);
        // primitive convert
        hako_convert_ros2pdu(src.contact_num, dst.contact_num);
        // struct convert
        if (!_ros2pdu_Vector3(src.relative_velocity, dst.relative_velocity, dynamic_memory)) {
            return false;
        }
        //struct array convert
        if (!_ros2pdu_struct_array_Collision_contact_position(src, dst, dynamic_memory)) {
            return false;
        }
        // primitive convert
        hako_convert_ros2pdu(src.restitution_coefficient, dst.restitution_coefficient);
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_Collision(hako_msgs::msg::Collision &src, Hako_Collision** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Collision out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Collision(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Collision), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Collision));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Collision*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_Collision() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_Collision(hako_msgs::msg::Collision &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_Collision out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Collision(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "Collision" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("Collision", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_Collision* hako_create_empty_pdu_Collision(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Collision), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Collision*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_msgs_Collision_HPP_ */
