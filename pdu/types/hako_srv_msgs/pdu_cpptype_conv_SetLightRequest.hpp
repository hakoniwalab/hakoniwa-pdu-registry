#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_SetLightRequest_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_SetLightRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_SetLightRequest.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_srv_msgs/pdu_cpptype_SetLightRequest.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_SetLightRequest(const char* heap_ptr, Hako_SetLightRequest &src, HakoCpp_SetLightRequest &dst)
{
    // string convertor
    dst.source = hako_convert_string_from_pdu(src.source, M_SIZE(Hako_SetLightRequest, source));
    // primitive convert
    hako_convert_pdu2cpp(src.mode, dst.mode);
    // primitive convert
    hako_convert_pdu2cpp(src.luminous_intensity_scale, dst.luminous_intensity_scale);
    // primitive convert
    hako_convert_pdu2cpp(src.flashing_on_s, dst.flashing_on_s);
    // primitive convert
    hako_convert_pdu2cpp(src.flashing_off_s, dst.flashing_off_s);
    // primitive convert
    hako_convert_pdu2cpp(src.transition_s, dst.transition_s);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_SetLightRequest(Hako_SetLightRequest &src, HakoCpp_SetLightRequest &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_SetLightRequest((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_SetLightRequest(HakoCpp_SetLightRequest &src, Hako_SetLightRequest &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // string convertor
        hako_convert_string_to_pdu(src.source, dst.source, M_SIZE(Hako_SetLightRequest, source));
        // primitive convert
        hako_convert_cpp2pdu(src.mode, dst.mode);
        // primitive convert
        hako_convert_cpp2pdu(src.luminous_intensity_scale, dst.luminous_intensity_scale);
        // primitive convert
        hako_convert_cpp2pdu(src.flashing_on_s, dst.flashing_on_s);
        // primitive convert
        hako_convert_cpp2pdu(src.flashing_off_s, dst.flashing_off_s);
        // primitive convert
        hako_convert_cpp2pdu(src.transition_s, dst.transition_s);
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_SetLightRequest(HakoCpp_SetLightRequest &src, Hako_SetLightRequest** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_SetLightRequest out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_SetLightRequest(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_SetLightRequest), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_SetLightRequest));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_SetLightRequest*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_SetLightRequest* hako_create_empty_pdu_SetLightRequest(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_SetLightRequest), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_SetLightRequest*)base_ptr;
}
namespace hako::pdu::msgs::hako_srv_msgs
{
class SetLightRequest
{
public:
    SetLightRequest() = default;
    ~SetLightRequest() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_SetLightRequest& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "SetLightRequest" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_SetLightRequest(*(Hako_SetLightRequest*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "SetLightRequest" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_SetLightRequest() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_SetLightRequest& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_SetLightRequest out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_SetLightRequest(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "SetLightRequest" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("SetLightRequest", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_SetLightRequest_HPP_ */
