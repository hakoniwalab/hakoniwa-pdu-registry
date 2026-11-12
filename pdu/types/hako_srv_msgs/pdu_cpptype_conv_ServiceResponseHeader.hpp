#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_ServiceResponseHeader_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_ServiceResponseHeader_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_ServiceResponseHeader.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_srv_msgs/pdu_cpptype_ServiceResponseHeader.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_ServiceResponseHeader(const char* heap_ptr, Hako_ServiceResponseHeader &src, HakoCpp_ServiceResponseHeader &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.request_id, dst.request_id);
    // string convertor
    dst.service_name = (const char*)src.service_name;
    // string convertor
    dst.client_name = (const char*)src.client_name;
    // primitive convert
    hako_convert_pdu2cpp(src.status, dst.status);
    // primitive convert
    hako_convert_pdu2cpp(src.processing_percentage, dst.processing_percentage);
    // primitive convert
    hako_convert_pdu2cpp(src.result_code, dst.result_code);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_ServiceResponseHeader(Hako_ServiceResponseHeader &src, HakoCpp_ServiceResponseHeader &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_ServiceResponseHeader((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_ServiceResponseHeader(HakoCpp_ServiceResponseHeader &src, Hako_ServiceResponseHeader &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.request_id, dst.request_id);
        // string convertor
        (void)hako_convert_cpp2pdu_array(
            src.service_name, src.service_name.length(),
            dst.service_name, M_ARRAY_SIZE(Hako_ServiceResponseHeader, char, service_name));
        dst.service_name[src.service_name.length()] = '\0';
        // string convertor
        (void)hako_convert_cpp2pdu_array(
            src.client_name, src.client_name.length(),
            dst.client_name, M_ARRAY_SIZE(Hako_ServiceResponseHeader, char, client_name));
        dst.client_name[src.client_name.length()] = '\0';
        // primitive convert
        hako_convert_cpp2pdu(src.status, dst.status);
        // primitive convert
        hako_convert_cpp2pdu(src.processing_percentage, dst.processing_percentage);
        // primitive convert
        hako_convert_cpp2pdu(src.result_code, dst.result_code);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_ServiceResponseHeader(HakoCpp_ServiceResponseHeader &src, Hako_ServiceResponseHeader** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_ServiceResponseHeader out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_ServiceResponseHeader(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_ServiceResponseHeader), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_ServiceResponseHeader));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_ServiceResponseHeader*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_ServiceResponseHeader* hako_create_empty_pdu_ServiceResponseHeader(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_ServiceResponseHeader), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_ServiceResponseHeader*)base_ptr;
}
namespace hako::pdu::msgs::hako_srv_msgs
{
class ServiceResponseHeader
{
public:
    ServiceResponseHeader() = default;
    ~ServiceResponseHeader() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_ServiceResponseHeader& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "ServiceResponseHeader" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_ServiceResponseHeader(*(Hako_ServiceResponseHeader*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "ServiceResponseHeader" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_ServiceResponseHeader() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_ServiceResponseHeader& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_ServiceResponseHeader out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_ServiceResponseHeader(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "ServiceResponseHeader" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        // Sizes in size_t, checked against the int-sized PDU fields and the buffer.
        const size_t meta_size = HAKO_PDU_META_DATA_SIZE();
        const size_t base_size = HAKO_ALIGN_SIZE(sizeof(Hako_ServiceResponseHeader), HAKO_ALIGNMENT_SIZE);
        const size_t heap_used = static_cast<size_t>(dynamic_memory.get_total_size());
        const size_t heap_size = HAKO_ALIGN_SIZE(heap_used, static_cast<size_t>(HAKO_ALIGNMENT_SIZE));
        const size_t pdu_size = meta_size + base_size + heap_size;
        if (heap_size < heap_used || pdu_size > static_cast<size_t>(std::numeric_limits<int>::max())) {
            std::cerr << "[ConvertorError][" << "ServiceResponseHeader" << "] PDU too large. heap=" << heap_used << std::endl;
            return -1;
        }
        if (pdu_buffer == nullptr || buffer_len < 0 || pdu_size > static_cast<size_t>(buffer_len)) {
            std::cerr << "[ConvertorError][" << "ServiceResponseHeader" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        if (dynamic_memory.references_overlap(pdu_buffer, pdu_size)) {
            std::cerr << "[ConvertorError][" << "ServiceResponseHeader" << "] pdu_buffer overlaps the message's arrays" << std::endl;
            return -1;
        }
        HakoPduMetaDataType meta;
        memset(&meta, 0, sizeof(meta));
        meta.magicno = HAKO_PDU_META_DATA_MAGICNO;
        meta.version = HAKO_PDU_META_DATA_VERSION;
        meta.base_off = static_cast<uint32_t>(meta_size);
        meta.heap_off = static_cast<uint32_t>(meta_size + base_size);
        meta.total_size = static_cast<uint32_t>(pdu_size);
        memset(pdu_buffer, 0, meta_size);
        memcpy(pdu_buffer, &meta, sizeof(meta));
        char* base_ptr = pdu_buffer + meta_size;
        memcpy(base_ptr, (const void*)&out, sizeof(Hako_ServiceResponseHeader));
        memset(base_ptr + sizeof(Hako_ServiceResponseHeader), 0, base_size - sizeof(Hako_ServiceResponseHeader));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return static_cast<int>(pdu_size);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_ServiceResponseHeader_HPP_ */
