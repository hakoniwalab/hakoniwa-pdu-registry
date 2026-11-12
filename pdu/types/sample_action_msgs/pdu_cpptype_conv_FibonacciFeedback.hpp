#ifndef _PDU_CPPTYPE_CONV_HAKO_sample_action_msgs_FibonacciFeedback_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sample_action_msgs_FibonacciFeedback_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sample_action_msgs/pdu_ctype_FibonacciFeedback.h"
/*
 * Dependent cpp pdu data
 */
#include "sample_action_msgs/pdu_cpptype_FibonacciFeedback.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_FibonacciFeedback_partial_sequence(const char* heap_ptr, Hako_FibonacciFeedback &src, HakoCpp_FibonacciFeedback &dst)
{
    // Convert using len and off
    int offset = src._partial_sequence_off;
    int length = src._partial_sequence_len;
    if (length > 0) {
        dst.partial_sequence.resize(length);
        memcpy(dst.partial_sequence.data(), heap_ptr + offset, length * sizeof(Hako_int32));
    }
    return 0;
}

static inline int cpp_pdu2cpp_FibonacciFeedback(const char* heap_ptr, Hako_FibonacciFeedback &src, HakoCpp_FibonacciFeedback &dst)
{
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_FibonacciFeedback_partial_sequence(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_FibonacciFeedback(Hako_FibonacciFeedback &src, HakoCpp_FibonacciFeedback &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_FibonacciFeedback((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_FibonacciFeedback_partial_sequence(HakoCpp_FibonacciFeedback &src, Hako_FibonacciFeedback &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._partial_sequence_len = src.partial_sequence.size();
    if (dst._partial_sequence_len > 0) {
        dst._partial_sequence_off = dynamic_memory.reference(src.partial_sequence.data(), dst._partial_sequence_len, sizeof(Hako_int32));
    }
    else {
        dst._partial_sequence_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_FibonacciFeedback(HakoCpp_FibonacciFeedback &src, Hako_FibonacciFeedback &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //primitive array copy
        cpp_cpp2pdu_primitive_array_FibonacciFeedback_partial_sequence(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_FibonacciFeedback(HakoCpp_FibonacciFeedback &src, Hako_FibonacciFeedback** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_FibonacciFeedback out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_FibonacciFeedback(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_FibonacciFeedback), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_FibonacciFeedback));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_FibonacciFeedback*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_FibonacciFeedback* hako_create_empty_pdu_FibonacciFeedback(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_FibonacciFeedback), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_FibonacciFeedback*)base_ptr;
}
namespace hako::pdu::msgs::sample_action_msgs
{
class FibonacciFeedback
{
public:
    FibonacciFeedback() = default;
    ~FibonacciFeedback() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_FibonacciFeedback& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "FibonacciFeedback" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_FibonacciFeedback(*(Hako_FibonacciFeedback*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "FibonacciFeedback" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_FibonacciFeedback() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    int cpp2pdu(HakoCpp_FibonacciFeedback& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_FibonacciFeedback out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_FibonacciFeedback(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "FibonacciFeedback" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        const int meta_size = (int)HAKO_PDU_META_DATA_SIZE();
        const int base_size = (int)HAKO_ALIGN_SIZE(sizeof(Hako_FibonacciFeedback), HAKO_ALIGNMENT_SIZE);
        const int heap_used = dynamic_memory.get_total_size();
        const int heap_size = (int)HAKO_ALIGN_SIZE(heap_used, HAKO_ALIGNMENT_SIZE);
        const int pdu_size = meta_size + base_size + heap_size;
        if (pdu_buffer == nullptr || pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "FibonacciFeedback" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        memset(pdu_buffer, 0, meta_size);
        HakoPduMetaDataType* meta = (HakoPduMetaDataType*)pdu_buffer;
        meta->magicno = HAKO_PDU_META_DATA_MAGICNO;
        meta->version = HAKO_PDU_META_DATA_VERSION;
        meta->base_off = meta_size;
        meta->heap_off = meta_size + base_size;
        meta->total_size = pdu_size;
        char* base_ptr = pdu_buffer + meta_size;
        memcpy(base_ptr, (void*)&out, sizeof(Hako_FibonacciFeedback));
        memset(base_ptr + sizeof(Hako_FibonacciFeedback), 0, base_size - sizeof(Hako_FibonacciFeedback));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sample_action_msgs_FibonacciFeedback_HPP_ */
