#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_DetachResponsePacket_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_DetachResponsePacket_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_DetachResponsePacket.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_srv_msgs/pdu_cpptype_DetachResponsePacket.hpp"

/*
 * Dependent Convertors
 */
#include "hako_srv_msgs/pdu_cpptype_conv_DetachResponse.hpp"
#include "hako_srv_msgs/pdu_cpptype_conv_ServiceResponseHeader.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_DetachResponsePacket(const char* heap_ptr, Hako_DetachResponsePacket &src, HakoCpp_DetachResponsePacket &dst)
{
    // Struct convert
    cpp_pdu2cpp_ServiceResponseHeader(heap_ptr, src.header, dst.header);
    // Struct convert
    cpp_pdu2cpp_DetachResponse(heap_ptr, src.body, dst.body);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_DetachResponsePacket(Hako_DetachResponsePacket &src, HakoCpp_DetachResponsePacket &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_DetachResponsePacket((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_DetachResponsePacket(HakoCpp_DetachResponsePacket &src, Hako_DetachResponsePacket &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_ServiceResponseHeader(src.header, dst.header, dynamic_memory);
        // struct convert
        cpp_cpp2pdu_DetachResponse(src.body, dst.body, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_DetachResponsePacket(HakoCpp_DetachResponsePacket &src, Hako_DetachResponsePacket** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_DetachResponsePacket out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_DetachResponsePacket(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_DetachResponsePacket), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_DetachResponsePacket));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_DetachResponsePacket*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_DetachResponsePacket* hako_create_empty_pdu_DetachResponsePacket(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_DetachResponsePacket), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_DetachResponsePacket*)base_ptr;
}
namespace hako::pdu::msgs::hako_srv_msgs
{
class DetachResponsePacket
{
public:
    DetachResponsePacket() = default;
    ~DetachResponsePacket() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_DetachResponsePacket& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "DetachResponsePacket" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_DetachResponsePacket(*(Hako_DetachResponsePacket*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "DetachResponsePacket" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_DetachResponsePacket() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_DetachResponsePacket& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_DetachResponsePacket out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_DetachResponsePacket(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "DetachResponsePacket" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        // Sizes in size_t, checked against the int-sized PDU fields and the buffer.
        const size_t meta_size = HAKO_PDU_META_DATA_SIZE();
        const size_t base_size = HAKO_ALIGN_SIZE(sizeof(Hako_DetachResponsePacket), HAKO_ALIGNMENT_SIZE);
        const size_t heap_used = static_cast<size_t>(dynamic_memory.get_total_size());
        const size_t heap_size = HAKO_ALIGN_SIZE(heap_used, static_cast<size_t>(HAKO_ALIGNMENT_SIZE));
        const size_t pdu_size = meta_size + base_size + heap_size;
        if (heap_size < heap_used || pdu_size > static_cast<size_t>(std::numeric_limits<int>::max())) {
            std::cerr << "[ConvertorError][" << "DetachResponsePacket" << "] PDU too large. heap=" << heap_used << std::endl;
            return -1;
        }
        if (pdu_buffer == nullptr || buffer_len < 0 || pdu_size > static_cast<size_t>(buffer_len)) {
            std::cerr << "[ConvertorError][" << "DetachResponsePacket" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        if (dynamic_memory.references_overlap(pdu_buffer, pdu_size)) {
            std::cerr << "[ConvertorError][" << "DetachResponsePacket" << "] pdu_buffer overlaps the message's arrays" << std::endl;
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
        memcpy(base_ptr, (const void*)&out, sizeof(Hako_DetachResponsePacket));
        memset(base_ptr + sizeof(Hako_DetachResponsePacket), 0, base_size - sizeof(Hako_DetachResponsePacket));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return static_cast<int>(pdu_size);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_DetachResponsePacket_HPP_ */
