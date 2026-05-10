#ifndef _PDU_CPPTYPE_CONV_HAKO_tf2_msgs_TF2Error_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_tf2_msgs_TF2Error_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "tf2_msgs/pdu_ctype_TF2Error.h"
/*
 * Dependent cpp pdu data
 */
#include "tf2_msgs/pdu_cpptype_TF2Error.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_TF2Error(const char* heap_ptr, Hako_TF2Error &src, HakoCpp_TF2Error &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.error, dst.error);
    // string convertor
    dst.error_string = (const char*)src.error_string;
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_TF2Error(Hako_TF2Error &src, HakoCpp_TF2Error &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_TF2Error((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_TF2Error(HakoCpp_TF2Error &src, Hako_TF2Error &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.error, dst.error);
        // string convertor
        (void)hako_convert_cpp2pdu_array(
            src.error_string, src.error_string.length(),
            dst.error_string, M_ARRAY_SIZE(Hako_TF2Error, char, error_string));
        dst.error_string[src.error_string.length()] = '\0';
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_TF2Error(HakoCpp_TF2Error &src, Hako_TF2Error** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_TF2Error out;
    if (!cpp_cpp2pdu_TF2Error(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_TF2Error), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_TF2Error));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_TF2Error*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_TF2Error* hako_create_empty_pdu_TF2Error(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_TF2Error), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_TF2Error*)base_ptr;
}
namespace hako::pdu::msgs::tf2_msgs
{
class TF2Error
{
public:
    TF2Error() = default;
    ~TF2Error() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_TF2Error& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "TF2Error" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_TF2Error(*(Hako_TF2Error*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "TF2Error" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_TF2Error& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_TF2Error(cppData, (Hako_TF2Error**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "TF2Error" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "TF2Error" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "TF2Error" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_tf2_msgs_TF2Error_HPP_ */
