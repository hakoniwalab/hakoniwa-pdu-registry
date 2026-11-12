#ifndef _PDU_CTYPE_CONV_HAKO_sensor_msgs_PointCloud2_HPP_
#define _PDU_CTYPE_CONV_HAKO_sensor_msgs_PointCloud2_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_PointCloud2.h"
/*
 * Dependent ros data
 */
#include "sensor_msgs/msg/point_cloud2.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "sensor_msgs/pdu_ctype_conv_PointField.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_PointCloud2_fields(const char* heap_ptr, Hako_PointCloud2 &src, sensor_msgs::msg::PointCloud2 &dst)
{
    // Convert using len and off
    int offset = src._fields_off;
    int length = src._fields_len;
    if (length > 0) {
        dst.fields.resize(length);
        Hako_PointField *temp_struct_ptr = (Hako_PointField *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_PointField(heap_ptr, *temp_struct_ptr, dst.fields[i]);
            temp_struct_ptr++;
        }
    }
    else {
        dst.fields.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}
static inline int _pdu2ros_primitive_array_PointCloud2_data(const char* heap_ptr, Hako_PointCloud2 &src, sensor_msgs::msg::PointCloud2 &dst)
{
    // Convert using len and off
    int offset = src._data_off;
    int length = src._data_len;
    if (length > 0) {
        dst.data.resize(length);
        memcpy(dst.data.data(), heap_ptr + offset, length * sizeof(Hako_uint8));
    }
    else {
        dst.data.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}

static inline int _pdu2ros_PointCloud2(const char* heap_ptr, Hako_PointCloud2 &src, sensor_msgs::msg::PointCloud2 &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // primitive convert
    hako_convert_pdu2ros(src.height, dst.height);
    // primitive convert
    hako_convert_pdu2ros(src.width, dst.width);
    // struct array convertor
    _pdu2ros_struct_array_PointCloud2_fields(heap_ptr, src, dst);
    // primitive convert
    hako_convert_pdu2ros(src.is_bigendian, dst.is_bigendian);
    // primitive convert
    hako_convert_pdu2ros(src.point_step, dst.point_step);
    // primitive convert
    hako_convert_pdu2ros(src.row_step, dst.row_step);
    // primitive array convertor
    _pdu2ros_primitive_array_PointCloud2_data(heap_ptr, src, dst);
    // primitive convert
    hako_convert_pdu2ros(src.is_dense, dst.is_dense);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_PointCloud2(Hako_PointCloud2 &src, sensor_msgs::msg::PointCloud2 &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_PointCloud2((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_PointCloud2_fields(sensor_msgs::msg::PointCloud2 &src, Hako_PointCloud2 &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._fields_len = hako_pdu_array_length(src.fields.size());
    if (dst._fields_len > 0) {
        Hako_PointField* temp_struct_ptr = (Hako_PointField*)dynamic_memory.allocate(dst._fields_len, sizeof(Hako_PointField));
        dst._fields_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._fields_len; ++i) {
            if (!_ros2pdu_PointField(src.fields[i], *temp_struct_ptr, dynamic_memory)) {
                return false;
            }
            temp_struct_ptr++;
        }
    }
    else {
        dst._fields_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool _ros2pdu_primitive_array_PointCloud2_data(sensor_msgs::msg::PointCloud2 &src, Hako_PointCloud2 &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._data_len = hako_pdu_array_length(src.data.size());
    if (dst._data_len > 0) {
        dst._data_off = dynamic_memory.reference(src.data.data(), dst._data_len, sizeof(Hako_uint8));
    }
    else {
        dst._data_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_PointCloud2(sensor_msgs::msg::PointCloud2 &src, Hako_PointCloud2 &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!_ros2pdu_Header(src.header, dst.header, dynamic_memory)) {
            return false;
        }
        // primitive convert
        hako_convert_ros2pdu(src.height, dst.height);
        // primitive convert
        hako_convert_ros2pdu(src.width, dst.width);
        //struct array convert
        if (!_ros2pdu_struct_array_PointCloud2_fields(src, dst, dynamic_memory)) {
            return false;
        }
        // primitive convert
        hako_convert_ros2pdu(src.is_bigendian, dst.is_bigendian);
        // primitive convert
        hako_convert_ros2pdu(src.point_step, dst.point_step);
        // primitive convert
        hako_convert_ros2pdu(src.row_step, dst.row_step);
        //primitive array copy
        if (!_ros2pdu_primitive_array_PointCloud2_data(src, dst, dynamic_memory)) {
            return false;
        }
        // primitive convert
        hako_convert_ros2pdu(src.is_dense, dst.is_dense);
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_PointCloud2(sensor_msgs::msg::PointCloud2 &src, Hako_PointCloud2** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_PointCloud2 out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_PointCloud2(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_PointCloud2), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_PointCloud2));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_PointCloud2*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_PointCloud2() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_PointCloud2(sensor_msgs::msg::PointCloud2 &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_PointCloud2 out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_PointCloud2(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "PointCloud2" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("PointCloud2", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_PointCloud2* hako_create_empty_pdu_PointCloud2(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_PointCloud2), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_PointCloud2*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sensor_msgs_PointCloud2_HPP_ */
