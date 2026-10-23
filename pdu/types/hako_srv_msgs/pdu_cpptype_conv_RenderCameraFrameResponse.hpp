#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_RenderCameraFrameResponse_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_RenderCameraFrameResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_RenderCameraFrameResponse.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_srv_msgs/pdu_cpptype_RenderCameraFrameResponse.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "sensor_msgs/pdu_cpptype_conv_Image.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_RenderCameraFrameResponse(const char* heap_ptr, Hako_RenderCameraFrameResponse &src, HakoCpp_RenderCameraFrameResponse &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.result_code, dst.result_code);
    // primitive convert
    hako_convert_pdu2cpp(src.sim_time_usec, dst.sim_time_usec);
    // Struct convert
    cpp_pdu2cpp_Image(heap_ptr, src.rgb, dst.rgb);
    // Struct convert
    cpp_pdu2cpp_Image(heap_ptr, src.depth, dst.depth);
    // Struct convert
    cpp_pdu2cpp_Image(heap_ptr, src.segmentation, dst.segmentation);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_RenderCameraFrameResponse(Hako_RenderCameraFrameResponse &src, HakoCpp_RenderCameraFrameResponse &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_RenderCameraFrameResponse((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_RenderCameraFrameResponse(HakoCpp_RenderCameraFrameResponse &src, Hako_RenderCameraFrameResponse &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.result_code, dst.result_code);
        // primitive convert
        hako_convert_cpp2pdu(src.sim_time_usec, dst.sim_time_usec);
        // struct convert
        cpp_cpp2pdu_Image(src.rgb, dst.rgb, dynamic_memory);
        // struct convert
        cpp_cpp2pdu_Image(src.depth, dst.depth, dynamic_memory);
        // struct convert
        cpp_cpp2pdu_Image(src.segmentation, dst.segmentation, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_RenderCameraFrameResponse(HakoCpp_RenderCameraFrameResponse &src, Hako_RenderCameraFrameResponse** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_RenderCameraFrameResponse out;
    if (!cpp_cpp2pdu_RenderCameraFrameResponse(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_RenderCameraFrameResponse), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_RenderCameraFrameResponse));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_RenderCameraFrameResponse*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_RenderCameraFrameResponse* hako_create_empty_pdu_RenderCameraFrameResponse(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_RenderCameraFrameResponse), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_RenderCameraFrameResponse*)base_ptr;
}
namespace hako::pdu::msgs::hako_srv_msgs
{
class RenderCameraFrameResponse
{
public:
    RenderCameraFrameResponse() = default;
    ~RenderCameraFrameResponse() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_RenderCameraFrameResponse& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "RenderCameraFrameResponse" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_RenderCameraFrameResponse(*(Hako_RenderCameraFrameResponse*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "RenderCameraFrameResponse" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_RenderCameraFrameResponse& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_RenderCameraFrameResponse(cppData, (Hako_RenderCameraFrameResponse**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "RenderCameraFrameResponse" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "RenderCameraFrameResponse" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "RenderCameraFrameResponse" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_RenderCameraFrameResponse_HPP_ */
