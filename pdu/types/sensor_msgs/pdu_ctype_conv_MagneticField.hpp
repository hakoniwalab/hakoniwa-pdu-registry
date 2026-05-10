#ifndef _PDU_CTYPE_CONV_HAKO_sensor_msgs_MagneticField_HPP_
#define _PDU_CTYPE_CONV_HAKO_sensor_msgs_MagneticField_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_MagneticField.h"
/*
 * Dependent ros data
 */
#include "sensor_msgs/msg/magnetic_field.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "geometry_msgs/pdu_ctype_conv_Vector3.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_MagneticField_magnetic_field_covariance(const char* heap_ptr, Hako_MagneticField &src, sensor_msgs::msg::MagneticField &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 9; ++i) {
        hako_convert_pdu2ros(src.magnetic_field_covariance[i], dst.magnetic_field_covariance[i]);
    }
    return 0;
}

static inline int _pdu2ros_MagneticField(const char* heap_ptr, Hako_MagneticField &src, sensor_msgs::msg::MagneticField &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // Struct convert
    _pdu2ros_Vector3(heap_ptr, src.magnetic_field, dst.magnetic_field);
    // primitive array convertor
    _pdu2ros_primitive_array_MagneticField_magnetic_field_covariance(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_MagneticField(Hako_MagneticField &src, sensor_msgs::msg::MagneticField &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_MagneticField((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_MagneticField_magnetic_field_covariance(sensor_msgs::msg::MagneticField &src, Hako_MagneticField &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 9
    (void)dynamic_memory;
    (void)hako_convert_ros2pdu_array(
        src.magnetic_field_covariance, src.magnetic_field_covariance.size(),
        dst.magnetic_field_covariance, M_ARRAY_SIZE(Hako_MagneticField, Hako_float64, magnetic_field_covariance));
    return true;
}

static inline bool _ros2pdu_MagneticField(sensor_msgs::msg::MagneticField &src, Hako_MagneticField &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        _ros2pdu_Header(src.header, dst.header, dynamic_memory);
        // struct convert
        _ros2pdu_Vector3(src.magnetic_field, dst.magnetic_field, dynamic_memory);
        //primitive array copy
        _ros2pdu_primitive_array_MagneticField_magnetic_field_covariance(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_MagneticField(sensor_msgs::msg::MagneticField &src, Hako_MagneticField** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_MagneticField out;
    if (!_ros2pdu_MagneticField(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_MagneticField), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_MagneticField));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_MagneticField*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_MagneticField* hako_create_empty_pdu_MagneticField(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_MagneticField), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_MagneticField*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sensor_msgs_MagneticField_HPP_ */
