#ifndef _PDU_CPPTYPE_CONV_HAKO_sample_action_msgs_FibonacciResult_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sample_action_msgs_FibonacciResult_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sample_action_msgs/pdu_ctype_FibonacciResult.h"
/*
 * Dependent cpp pdu data
 */
#include "sample_action_msgs/pdu_cpptype_FibonacciResult.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_FibonacciResult_sequence(const char* heap_ptr, Hako_FibonacciResult &src, HakoCpp_FibonacciResult &dst)
{
    // Convert using len and off
    int offset = src._sequence_off;
    int length = src._sequence_len;
    if (length > 0) {
        dst.sequence.resize(length);
        memcpy(dst.sequence.data(), heap_ptr + offset, length * sizeof(Hako_int32));
    }
    return 0;
}

static inline int cpp_pdu2cpp_FibonacciResult(const char* heap_ptr, Hako_FibonacciResult &src, HakoCpp_FibonacciResult &dst)
{
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_FibonacciResult_sequence(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_FibonacciResult(Hako_FibonacciResult &src, HakoCpp_FibonacciResult &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_FibonacciResult((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_FibonacciResult_sequence(HakoCpp_FibonacciResult &src, Hako_FibonacciResult &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray
    dst._sequence_len = src.sequence.size();
    if (dst._sequence_len > 0) {
        void* temp_ptr = dynamic_memory.allocate(dst._sequence_len, sizeof(Hako_int32));
        memcpy(temp_ptr, src.sequence.data(), dst._sequence_len * sizeof(Hako_int32));
        dst._sequence_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._sequence_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_FibonacciResult(HakoCpp_FibonacciResult &src, Hako_FibonacciResult &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //primitive array copy
        cpp_cpp2pdu_primitive_array_FibonacciResult_sequence(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_FibonacciResult(HakoCpp_FibonacciResult &src, Hako_FibonacciResult** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_FibonacciResult out;
    if (!cpp_cpp2pdu_FibonacciResult(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_FibonacciResult), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_FibonacciResult));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_FibonacciResult*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_FibonacciResult* hako_create_empty_pdu_FibonacciResult(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_FibonacciResult), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_FibonacciResult*)base_ptr;
}
namespace hako::pdu::msgs::sample_action_msgs
{
class FibonacciResult
{
public:
    FibonacciResult() = default;
    ~FibonacciResult() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_FibonacciResult& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "FibonacciResult" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_FibonacciResult(*(Hako_FibonacciResult*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "FibonacciResult" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_FibonacciResult& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_FibonacciResult(cppData, (Hako_FibonacciResult**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "FibonacciResult" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "FibonacciResult" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "FibonacciResult" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sample_action_msgs_FibonacciResult_HPP_ */
