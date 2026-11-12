#ifndef _PDU_CPPTYPE_CONV_HAKO_can_msgs_HakoCanBody_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_can_msgs_HakoCanBody_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "can_msgs/pdu_ctype_HakoCanBody.h"
/*
 * Dependent cpp pdu data
 */
#include "can_msgs/pdu_cpptype_HakoCanBody.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_HakoCanBody_data(const char* heap_ptr, Hako_HakoCanBody &src, HakoCpp_HakoCanBody &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 8; ++i) {
        hako_convert_pdu2cpp(src.data[i], dst.data[i]);
    }
    return 0;
}

static inline int cpp_pdu2cpp_HakoCanBody(const char* heap_ptr, Hako_HakoCanBody &src, HakoCpp_HakoCanBody &dst)
{
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_HakoCanBody_data(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_HakoCanBody(Hako_HakoCanBody &src, HakoCpp_HakoCanBody &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_HakoCanBody((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_HakoCanBody_data(HakoCpp_HakoCanBody &src, Hako_HakoCanBody &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 8
    (void)dynamic_memory;
    (void)hako_convert_cpp2pdu_array(
        src.data, src.data.size(),
        dst.data, M_ARRAY_SIZE(Hako_HakoCanBody, Hako_uint8, data));
    return true;
}

static inline bool cpp_cpp2pdu_HakoCanBody(HakoCpp_HakoCanBody &src, Hako_HakoCanBody &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //primitive array copy
        if (!cpp_cpp2pdu_primitive_array_HakoCanBody_data(src, dst, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_HakoCanBody(HakoCpp_HakoCanBody &src, Hako_HakoCanBody** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_HakoCanBody out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_HakoCanBody(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_HakoCanBody), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_HakoCanBody));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_HakoCanBody*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_HakoCanBody* hako_create_empty_pdu_HakoCanBody(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_HakoCanBody), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_HakoCanBody*)base_ptr;
}
namespace hako::pdu::msgs::can_msgs
{
class HakoCanBody
{
public:
    HakoCanBody() = default;
    ~HakoCanBody() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_HakoCanBody& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "HakoCanBody" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_HakoCanBody(*(Hako_HakoCanBody*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "HakoCanBody" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_HakoCanBody() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_HakoCanBody& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_HakoCanBody out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_HakoCanBody(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "HakoCanBody" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("HakoCanBody", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_can_msgs_HakoCanBody_HPP_ */
