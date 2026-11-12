#ifndef _PDU_CPPTYPE_CONV_HAKO_drone_srv_msgs_CameraCaptureImageResponse_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_drone_srv_msgs_CameraCaptureImageResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "drone_srv_msgs/pdu_ctype_CameraCaptureImageResponse.h"
/*
 * Dependent cpp pdu data
 */
#include "drone_srv_msgs/pdu_cpptype_CameraCaptureImageResponse.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_CameraCaptureImageResponse_data(const char* heap_ptr, Hako_CameraCaptureImageResponse &src, HakoCpp_CameraCaptureImageResponse &dst)
{
    // Convert using len and off
    int offset = src._data_off;
    int length = src._data_len;
    if (length > 0) {
        dst.data.resize(length);
        memcpy(dst.data.data(), heap_ptr + offset, length * sizeof(Hako_uint8));
    }
    else {
        dst.data.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}

static inline int cpp_pdu2cpp_CameraCaptureImageResponse(const char* heap_ptr, Hako_CameraCaptureImageResponse &src, HakoCpp_CameraCaptureImageResponse &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.ok, dst.ok);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_CameraCaptureImageResponse_data(heap_ptr, src, dst);
    // string convertor
    dst.message = hako_convert_string_from_pdu(src.message, M_SIZE(Hako_CameraCaptureImageResponse, message));
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_CameraCaptureImageResponse(Hako_CameraCaptureImageResponse &src, HakoCpp_CameraCaptureImageResponse &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_CameraCaptureImageResponse((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_CameraCaptureImageResponse_data(HakoCpp_CameraCaptureImageResponse &src, Hako_CameraCaptureImageResponse &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._data_len = hako_pdu_array_length(src.data.size());
    if (dst._data_len > 0) {
        dst._data_off = dynamic_memory.reference(src.data.data(), dst._data_len, sizeof(Hako_uint8));
    }
    else {
        dst._data_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_CameraCaptureImageResponse(HakoCpp_CameraCaptureImageResponse &src, Hako_CameraCaptureImageResponse &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.ok, dst.ok);
        //primitive array copy
        if (!cpp_cpp2pdu_primitive_array_CameraCaptureImageResponse_data(src, dst, dynamic_memory)) {
            return false;
        }
        // string convertor
        hako_convert_string_to_pdu(src.message, dst.message, M_SIZE(Hako_CameraCaptureImageResponse, message));
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_CameraCaptureImageResponse(HakoCpp_CameraCaptureImageResponse &src, Hako_CameraCaptureImageResponse** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_CameraCaptureImageResponse out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_CameraCaptureImageResponse(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_CameraCaptureImageResponse), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_CameraCaptureImageResponse));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_CameraCaptureImageResponse*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_CameraCaptureImageResponse* hako_create_empty_pdu_CameraCaptureImageResponse(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_CameraCaptureImageResponse), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_CameraCaptureImageResponse*)base_ptr;
}
namespace hako::pdu::msgs::drone_srv_msgs
{
class CameraCaptureImageResponse
{
public:
    CameraCaptureImageResponse() = default;
    ~CameraCaptureImageResponse() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_CameraCaptureImageResponse& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "CameraCaptureImageResponse" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_CameraCaptureImageResponse(*(Hako_CameraCaptureImageResponse*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "CameraCaptureImageResponse" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_CameraCaptureImageResponse() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_CameraCaptureImageResponse& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_CameraCaptureImageResponse out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_CameraCaptureImageResponse(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "CameraCaptureImageResponse" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("CameraCaptureImageResponse", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_drone_srv_msgs_CameraCaptureImageResponse_HPP_ */
