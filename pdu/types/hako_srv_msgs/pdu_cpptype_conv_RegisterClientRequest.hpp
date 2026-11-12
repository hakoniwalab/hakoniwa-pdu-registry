#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_RegisterClientRequest_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_RegisterClientRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_RegisterClientRequest.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_srv_msgs/pdu_cpptype_RegisterClientRequest.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_RegisterClientRequest(const char* heap_ptr, Hako_RegisterClientRequest &src, HakoCpp_RegisterClientRequest &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.dummy, dst.dummy);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_RegisterClientRequest(Hako_RegisterClientRequest &src, HakoCpp_RegisterClientRequest &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_RegisterClientRequest((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_RegisterClientRequest(HakoCpp_RegisterClientRequest &src, Hako_RegisterClientRequest &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.dummy, dst.dummy);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_RegisterClientRequest(HakoCpp_RegisterClientRequest &src, Hako_RegisterClientRequest** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_RegisterClientRequest out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_RegisterClientRequest(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_RegisterClientRequest), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_RegisterClientRequest));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_RegisterClientRequest*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_RegisterClientRequest* hako_create_empty_pdu_RegisterClientRequest(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_RegisterClientRequest), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_RegisterClientRequest*)base_ptr;
}
namespace hako::pdu::msgs::hako_srv_msgs
{
class RegisterClientRequest
{
public:
    RegisterClientRequest() = default;
    ~RegisterClientRequest() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_RegisterClientRequest& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "RegisterClientRequest" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_RegisterClientRequest(*(Hako_RegisterClientRequest*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "RegisterClientRequest" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_RegisterClientRequest() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    int cpp2pdu(HakoCpp_RegisterClientRequest& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_RegisterClientRequest out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_RegisterClientRequest(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "RegisterClientRequest" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        const int meta_size = (int)HAKO_PDU_META_DATA_SIZE();
        const int base_size = (int)HAKO_ALIGN_SIZE(sizeof(Hako_RegisterClientRequest), HAKO_ALIGNMENT_SIZE);
        const int heap_used = dynamic_memory.get_total_size();
        const int heap_size = (int)HAKO_ALIGN_SIZE(heap_used, HAKO_ALIGNMENT_SIZE);
        const int pdu_size = meta_size + base_size + heap_size;
        if (pdu_buffer == nullptr || pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "RegisterClientRequest" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
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
        memcpy(base_ptr, (void*)&out, sizeof(Hako_RegisterClientRequest));
        memset(base_ptr + sizeof(Hako_RegisterClientRequest), 0, base_size - sizeof(Hako_RegisterClientRequest));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_RegisterClientRequest_HPP_ */
