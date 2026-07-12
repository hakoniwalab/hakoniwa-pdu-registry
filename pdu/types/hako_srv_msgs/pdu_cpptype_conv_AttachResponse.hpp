#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_AttachResponse_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_AttachResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_AttachResponse.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_srv_msgs/pdu_cpptype_AttachResponse.hpp"

/*
 * Dependent Convertors
 */
#include "hako_srv_msgs/pdu_cpptype_conv_LogicalTime.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_AttachResponse(const char* heap_ptr, Hako_AttachResponse &src, HakoCpp_AttachResponse &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.result_code, dst.result_code);
    // primitive convert
    hako_convert_pdu2cpp(src.session_id, dst.session_id);
    // Struct convert
    cpp_pdu2cpp_LogicalTime(heap_ptr, src.world_time, dst.world_time);
    // primitive convert
    hako_convert_pdu2cpp(src.delta_asset_tick, dst.delta_asset_tick);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_AttachResponse(Hako_AttachResponse &src, HakoCpp_AttachResponse &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_AttachResponse((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_AttachResponse(HakoCpp_AttachResponse &src, Hako_AttachResponse &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.result_code, dst.result_code);
        // primitive convert
        hako_convert_cpp2pdu(src.session_id, dst.session_id);
        // struct convert
        cpp_cpp2pdu_LogicalTime(src.world_time, dst.world_time, dynamic_memory);
        // primitive convert
        hako_convert_cpp2pdu(src.delta_asset_tick, dst.delta_asset_tick);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_AttachResponse(HakoCpp_AttachResponse &src, Hako_AttachResponse** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_AttachResponse out;
    if (!cpp_cpp2pdu_AttachResponse(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_AttachResponse), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_AttachResponse));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_AttachResponse*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_AttachResponse* hako_create_empty_pdu_AttachResponse(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_AttachResponse), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_AttachResponse*)base_ptr;
}
namespace hako::pdu::msgs::hako_srv_msgs
{
class AttachResponse
{
public:
    AttachResponse() = default;
    ~AttachResponse() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_AttachResponse& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "AttachResponse" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_AttachResponse(*(Hako_AttachResponse*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "AttachResponse" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_AttachResponse& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_AttachResponse(cppData, (Hako_AttachResponse**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "AttachResponse" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "AttachResponse" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "AttachResponse" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_AttachResponse_HPP_ */
