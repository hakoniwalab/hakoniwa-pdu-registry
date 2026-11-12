#ifndef _PDU_CTYPE_CONV_HAKO_sensor_msgs_Image_HPP_
#define _PDU_CTYPE_CONV_HAKO_sensor_msgs_Image_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_Image.h"
/*
 * Dependent ros data
 */
#include "sensor_msgs/msg/image.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_Image_data(const char* heap_ptr, Hako_Image &src, sensor_msgs::msg::Image &dst)
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

static inline int _pdu2ros_Image(const char* heap_ptr, Hako_Image &src, sensor_msgs::msg::Image &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // primitive convert
    hako_convert_pdu2ros(src.height, dst.height);
    // primitive convert
    hako_convert_pdu2ros(src.width, dst.width);
    // string convertor
    dst.encoding = hako_convert_string_from_pdu(src.encoding, M_SIZE(Hako_Image, encoding));
    // primitive convert
    hako_convert_pdu2ros(src.is_bigendian, dst.is_bigendian);
    // primitive convert
    hako_convert_pdu2ros(src.step, dst.step);
    // primitive array convertor
    _pdu2ros_primitive_array_Image_data(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_Image(Hako_Image &src, sensor_msgs::msg::Image &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_Image((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_Image_data(sensor_msgs::msg::Image &src, Hako_Image &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._data_len = src.data.size();
    if (dst._data_len > 0) {
        dst._data_off = dynamic_memory.reference(src.data.data(), dst._data_len, sizeof(Hako_uint8));
    }
    else {
        dst._data_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_Image(sensor_msgs::msg::Image &src, Hako_Image &dst, PduDynamicMemory &dynamic_memory)
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
        // string convertor
        hako_convert_string_to_pdu(src.encoding, dst.encoding, M_SIZE(Hako_Image, encoding));
        // primitive convert
        hako_convert_ros2pdu(src.is_bigendian, dst.is_bigendian);
        // primitive convert
        hako_convert_ros2pdu(src.step, dst.step);
        //primitive array copy
        if (!_ros2pdu_primitive_array_Image_data(src, dst, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_Image(sensor_msgs::msg::Image &src, Hako_Image** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Image out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Image(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Image), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Image));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Image*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_Image() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_Image(sensor_msgs::msg::Image &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_Image out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_Image(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "Image" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("Image", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_Image* hako_create_empty_pdu_Image(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Image), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Image*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_sensor_msgs_Image_HPP_ */
