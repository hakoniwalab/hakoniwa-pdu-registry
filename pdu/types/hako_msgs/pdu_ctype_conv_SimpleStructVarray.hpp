#ifndef _PDU_CTYPE_CONV_HAKO_hako_msgs_SimpleStructVarray_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_msgs_SimpleStructVarray_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_SimpleStructVarray.h"
/*
 * Dependent ros data
 */
#include "hako_msgs/msg/simple_struct_varray.hpp"

/*
 * Dependent Convertors
 */
#include "hako_msgs/pdu_ctype_conv_SimpleVarray.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_string_array_SimpleStructVarray_fixed_str(const char* heap_ptr, Hako_SimpleStructVarray &src, hako_msgs::msg::SimpleStructVarray &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    (void)hako_convert_pdu2ros_array_string<M_ARRAY_SIZE(Hako_SimpleStructVarray, Hako_cstring, fixed_str), 2>(
        src.fixed_str, dst.fixed_str);
    return 0;
}
static inline int _pdu2ros_string_array_SimpleStructVarray_varray_str(const char* heap_ptr, Hako_SimpleStructVarray &src, hako_msgs::msg::SimpleStructVarray &dst)
{
    // Convert using len and off
    int offset = src._varray_str_off;
    int length = src._varray_str_len;
    if (length > 0) {
        Hako_cstring *temp_struct_ptr = (Hako_cstring *)(heap_ptr + offset);
        hako_convert_pdu2ros_array_string_varray(temp_struct_ptr, dst.varray_str, length);
    }
    else {
        dst.varray_str.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}
static inline int _pdu2ros_struct_array_SimpleStructVarray_fixed_array(const char* heap_ptr, Hako_SimpleStructVarray &src, hako_msgs::msg::SimpleStructVarray &dst)
{
    // Fixed size array convertor
    for (int i = 0; i < 5; ++i) {
        _pdu2ros_SimpleVarray(heap_ptr, src.fixed_array[i], dst.fixed_array[i]);
    }
    return 0;
}
static inline int _pdu2ros_struct_array_SimpleStructVarray_data(const char* heap_ptr, Hako_SimpleStructVarray &src, hako_msgs::msg::SimpleStructVarray &dst)
{
    // Convert using len and off
    int offset = src._data_off;
    int length = src._data_len;
    if (length > 0) {
        dst.data.resize(length);
        Hako_SimpleVarray *temp_struct_ptr = (Hako_SimpleVarray *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_SimpleVarray(heap_ptr, *temp_struct_ptr, dst.data[i]);
            temp_struct_ptr++;
        }
    }
    else {
        dst.data.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}

static inline int _pdu2ros_SimpleStructVarray(const char* heap_ptr, Hako_SimpleStructVarray &src, hako_msgs::msg::SimpleStructVarray &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.aaa, dst.aaa);
    // string array convertor
    _pdu2ros_string_array_SimpleStructVarray_fixed_str(heap_ptr, src, dst);
    // string array convertor
    _pdu2ros_string_array_SimpleStructVarray_varray_str(heap_ptr, src, dst);
    // struct array convertor
    _pdu2ros_struct_array_SimpleStructVarray_fixed_array(heap_ptr, src, dst);
    // struct array convertor
    _pdu2ros_struct_array_SimpleStructVarray_data(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_SimpleStructVarray(Hako_SimpleStructVarray &src, hako_msgs::msg::SimpleStructVarray &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_SimpleStructVarray((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_string_array_SimpleStructVarray_fixed_str(hako_msgs::msg::SimpleStructVarray &src, Hako_SimpleStructVarray &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed string 2
    (void)dynamic_memory;
    (void)hako_convert_ros2pdu_array_string<2, M_ARRAY_SIZE(Hako_SimpleStructVarray, Hako_cstring, fixed_str)>(
        src.fixed_str, dst.fixed_str);
    return true;
}
static inline bool _ros2pdu_string_array_SimpleStructVarray_varray_str(hako_msgs::msg::SimpleStructVarray &src, Hako_SimpleStructVarray &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray string
    dst._varray_str_len = src.varray_str.size();
    if (dst._varray_str_len > 0) {
        Hako_cstring* temp_ptr = (Hako_cstring*)dynamic_memory.allocate(dst._varray_str_len, sizeof(Hako_cstring));
        (void)hako_convert_ros2pdu_array_string_varray(src.varray_str, temp_ptr);
        dst._varray_str_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._varray_str_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool _ros2pdu_struct_array_SimpleStructVarray_fixed_array(hako_msgs::msg::SimpleStructVarray &src, Hako_SimpleStructVarray &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    //array size is fixed
    for (int i = 0; i < 5; ++i) {
        if (!_ros2pdu_SimpleVarray(src.fixed_array[i], dst.fixed_array[i], dynamic_memory)) {
            return false;
        }
    }
    return true;
}
static inline bool _ros2pdu_struct_array_SimpleStructVarray_data(hako_msgs::msg::SimpleStructVarray &src, Hako_SimpleStructVarray &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._data_len = src.data.size();
    if (dst._data_len > 0) {
        Hako_SimpleVarray* temp_struct_ptr = (Hako_SimpleVarray*)dynamic_memory.allocate(dst._data_len, sizeof(Hako_SimpleVarray));
        dst._data_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._data_len; ++i) {
            if (!_ros2pdu_SimpleVarray(src.data[i], *temp_struct_ptr, dynamic_memory)) {
                return false;
            }
            temp_struct_ptr++;
        }
    }
    else {
        dst._data_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_SimpleStructVarray(hako_msgs::msg::SimpleStructVarray &src, Hako_SimpleStructVarray &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.aaa, dst.aaa);
        // string array convert
        if (!_ros2pdu_string_array_SimpleStructVarray_fixed_str(src, dst, dynamic_memory)) {
            return false;
        }
        // string array convert
        if (!_ros2pdu_string_array_SimpleStructVarray_varray_str(src, dst, dynamic_memory)) {
            return false;
        }
        //struct array convert
        if (!_ros2pdu_struct_array_SimpleStructVarray_fixed_array(src, dst, dynamic_memory)) {
            return false;
        }
        //struct array convert
        if (!_ros2pdu_struct_array_SimpleStructVarray_data(src, dst, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_SimpleStructVarray(hako_msgs::msg::SimpleStructVarray &src, Hako_SimpleStructVarray** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_SimpleStructVarray out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_SimpleStructVarray(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_SimpleStructVarray), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_SimpleStructVarray));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_SimpleStructVarray*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_SimpleStructVarray() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_SimpleStructVarray(hako_msgs::msg::SimpleStructVarray &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_SimpleStructVarray out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_SimpleStructVarray(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "SimpleStructVarray" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("SimpleStructVarray", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_SimpleStructVarray* hako_create_empty_pdu_SimpleStructVarray(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_SimpleStructVarray), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_SimpleStructVarray*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_msgs_SimpleStructVarray_HPP_ */
