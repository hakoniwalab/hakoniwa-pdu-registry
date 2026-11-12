#ifndef _PDU_CPPTYPE_CONV_HAKO_std_msgs_Int32MultiArray_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_std_msgs_Int32MultiArray_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "std_msgs/pdu_ctype_Int32MultiArray.h"
/*
 * Dependent cpp pdu data
 */
#include "std_msgs/pdu_cpptype_Int32MultiArray.hpp"

/*
 * Dependent Convertors
 */
#include "std_msgs/pdu_cpptype_conv_MultiArrayDimension.hpp"
#include "std_msgs/pdu_cpptype_conv_MultiArrayLayout.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_Int32MultiArray_data(const char* heap_ptr, Hako_Int32MultiArray &src, HakoCpp_Int32MultiArray &dst)
{
    // Convert using len and off
    int offset = src._data_off;
    int length = src._data_len;
    if (length > 0) {
        dst.data.resize(length);
        memcpy(dst.data.data(), heap_ptr + offset, length * sizeof(Hako_int32));
    }
    else {
        dst.data.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}

static inline int cpp_pdu2cpp_Int32MultiArray(const char* heap_ptr, Hako_Int32MultiArray &src, HakoCpp_Int32MultiArray &dst)
{
    // Struct convert
    cpp_pdu2cpp_MultiArrayLayout(heap_ptr, src.layout, dst.layout);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_Int32MultiArray_data(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_Int32MultiArray(Hako_Int32MultiArray &src, HakoCpp_Int32MultiArray &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_Int32MultiArray((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_Int32MultiArray_data(HakoCpp_Int32MultiArray &src, Hako_Int32MultiArray &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._data_len = hako_pdu_array_length(src.data.size());
    if (dst._data_len > 0) {
        dst._data_off = dynamic_memory.reference(src.data.data(), dst._data_len, sizeof(Hako_int32));
    }
    else {
        dst._data_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_Int32MultiArray(HakoCpp_Int32MultiArray &src, Hako_Int32MultiArray &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!cpp_cpp2pdu_MultiArrayLayout(src.layout, dst.layout, dynamic_memory)) {
            return false;
        }
        //primitive array copy
        if (!cpp_cpp2pdu_primitive_array_Int32MultiArray_data(src, dst, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_Int32MultiArray(HakoCpp_Int32MultiArray &src, Hako_Int32MultiArray** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Int32MultiArray out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_Int32MultiArray(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Int32MultiArray), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Int32MultiArray));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Int32MultiArray*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Int32MultiArray* hako_create_empty_pdu_Int32MultiArray(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Int32MultiArray), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Int32MultiArray*)base_ptr;
}
namespace hako::pdu::msgs::std_msgs
{
class Int32MultiArray
{
public:
    Int32MultiArray() = default;
    ~Int32MultiArray() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_Int32MultiArray& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "Int32MultiArray" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_Int32MultiArray(*(Hako_Int32MultiArray*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "Int32MultiArray" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_Int32MultiArray() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_Int32MultiArray& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_Int32MultiArray out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_Int32MultiArray(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "Int32MultiArray" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("Int32MultiArray", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_std_msgs_Int32MultiArray_HPP_ */
