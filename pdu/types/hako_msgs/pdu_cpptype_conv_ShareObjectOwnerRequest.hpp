#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_msgs_ShareObjectOwnerRequest_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_msgs_ShareObjectOwnerRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_ShareObjectOwnerRequest.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_msgs/pdu_cpptype_ShareObjectOwnerRequest.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_ShareObjectOwnerRequest(const char* heap_ptr, Hako_ShareObjectOwnerRequest &src, HakoCpp_ShareObjectOwnerRequest &dst)
{
    // string convertor
    dst.object_name = (const char*)src.object_name;
    // primitive convert
    hako_convert_pdu2cpp(src.request_type, dst.request_type);
    // primitive convert
    hako_convert_pdu2cpp(src.new_owner_id, dst.new_owner_id);
    // primitive convert
    hako_convert_pdu2cpp(src.request_time, dst.request_time);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_ShareObjectOwnerRequest(Hako_ShareObjectOwnerRequest &src, HakoCpp_ShareObjectOwnerRequest &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_ShareObjectOwnerRequest((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_ShareObjectOwnerRequest(HakoCpp_ShareObjectOwnerRequest &src, Hako_ShareObjectOwnerRequest &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // string convertor
        (void)hako_convert_cpp2pdu_array(
            src.object_name, src.object_name.length(),
            dst.object_name, M_ARRAY_SIZE(Hako_ShareObjectOwnerRequest, char, object_name));
        dst.object_name[src.object_name.length()] = '\0';
        // primitive convert
        hako_convert_cpp2pdu(src.request_type, dst.request_type);
        // primitive convert
        hako_convert_cpp2pdu(src.new_owner_id, dst.new_owner_id);
        // primitive convert
        hako_convert_cpp2pdu(src.request_time, dst.request_time);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_ShareObjectOwnerRequest(HakoCpp_ShareObjectOwnerRequest &src, Hako_ShareObjectOwnerRequest** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_ShareObjectOwnerRequest out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_ShareObjectOwnerRequest(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_ShareObjectOwnerRequest), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_ShareObjectOwnerRequest));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_ShareObjectOwnerRequest*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_ShareObjectOwnerRequest* hako_create_empty_pdu_ShareObjectOwnerRequest(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_ShareObjectOwnerRequest), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_ShareObjectOwnerRequest*)base_ptr;
}
namespace hako::pdu::msgs::hako_msgs
{
class ShareObjectOwnerRequest
{
public:
    ShareObjectOwnerRequest() = default;
    ~ShareObjectOwnerRequest() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_ShareObjectOwnerRequest& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "ShareObjectOwnerRequest" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_ShareObjectOwnerRequest(*(Hako_ShareObjectOwnerRequest*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "ShareObjectOwnerRequest" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_ShareObjectOwnerRequest() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    int cpp2pdu(HakoCpp_ShareObjectOwnerRequest& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_ShareObjectOwnerRequest out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_ShareObjectOwnerRequest(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "ShareObjectOwnerRequest" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        const int meta_size = (int)HAKO_PDU_META_DATA_SIZE();
        const int base_size = (int)HAKO_ALIGN_SIZE(sizeof(Hako_ShareObjectOwnerRequest), HAKO_ALIGNMENT_SIZE);
        const int heap_used = dynamic_memory.get_total_size();
        const int heap_size = (int)HAKO_ALIGN_SIZE(heap_used, HAKO_ALIGNMENT_SIZE);
        const int pdu_size = meta_size + base_size + heap_size;
        if (pdu_buffer == nullptr || pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "ShareObjectOwnerRequest" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
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
        memcpy(base_ptr, (void*)&out, sizeof(Hako_ShareObjectOwnerRequest));
        memset(base_ptr + sizeof(Hako_ShareObjectOwnerRequest), 0, base_size - sizeof(Hako_ShareObjectOwnerRequest));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_msgs_ShareObjectOwnerRequest_HPP_ */
