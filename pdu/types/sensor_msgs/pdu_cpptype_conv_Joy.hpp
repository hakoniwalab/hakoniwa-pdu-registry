#ifndef _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_Joy_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_Joy_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_Joy.h"
/*
 * Dependent cpp pdu data
 */
#include "sensor_msgs/pdu_cpptype_Joy.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_Joy_axes(const char* heap_ptr, Hako_Joy &src, HakoCpp_Joy &dst)
{
    // Convert using len and off
    int offset = src._axes_off;
    int length = src._axes_len;
    if (length > 0) {
        dst.axes.resize(length);
        memcpy(dst.axes.data(), heap_ptr + offset, length * sizeof(Hako_float32));
    }
    else {
        dst.axes.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}
static inline int cpp_pdu2cpp_primitive_array_Joy_buttons(const char* heap_ptr, Hako_Joy &src, HakoCpp_Joy &dst)
{
    // Convert using len and off
    int offset = src._buttons_off;
    int length = src._buttons_len;
    if (length > 0) {
        dst.buttons.resize(length);
        memcpy(dst.buttons.data(), heap_ptr + offset, length * sizeof(Hako_int32));
    }
    else {
        dst.buttons.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}

static inline int cpp_pdu2cpp_Joy(const char* heap_ptr, Hako_Joy &src, HakoCpp_Joy &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_Joy_axes(heap_ptr, src, dst);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_Joy_buttons(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_Joy(Hako_Joy &src, HakoCpp_Joy &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_Joy((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_Joy_axes(HakoCpp_Joy &src, Hako_Joy &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._axes_len = hako_pdu_array_length(src.axes.size());
    if (dst._axes_len > 0) {
        dst._axes_off = dynamic_memory.reference(src.axes.data(), dst._axes_len, sizeof(Hako_float32));
    }
    else {
        dst._axes_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool cpp_cpp2pdu_primitive_array_Joy_buttons(HakoCpp_Joy &src, Hako_Joy &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._buttons_len = hako_pdu_array_length(src.buttons.size());
    if (dst._buttons_len > 0) {
        dst._buttons_off = dynamic_memory.reference(src.buttons.data(), dst._buttons_len, sizeof(Hako_int32));
    }
    else {
        dst._buttons_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_Joy(HakoCpp_Joy &src, Hako_Joy &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory)) {
            return false;
        }
        //primitive array copy
        if (!cpp_cpp2pdu_primitive_array_Joy_axes(src, dst, dynamic_memory)) {
            return false;
        }
        //primitive array copy
        if (!cpp_cpp2pdu_primitive_array_Joy_buttons(src, dst, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_Joy(HakoCpp_Joy &src, Hako_Joy** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Joy out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_Joy(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Joy), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Joy));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Joy*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Joy* hako_create_empty_pdu_Joy(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Joy), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Joy*)base_ptr;
}
namespace hako::pdu::msgs::sensor_msgs
{
class Joy
{
public:
    Joy() = default;
    ~Joy() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_Joy& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "Joy" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_Joy(*(Hako_Joy*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "Joy" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_Joy() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_Joy& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_Joy out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_Joy(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "Joy" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("Joy", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_Joy_HPP_ */
