#ifndef _PDU_CPPTYPE_CONV_HAKO_drone_srv_msgs_DroneGoToResponse_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_drone_srv_msgs_DroneGoToResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "drone_srv_msgs/pdu_ctype_DroneGoToResponse.h"
/*
 * Dependent cpp pdu data
 */
#include "drone_srv_msgs/pdu_cpptype_DroneGoToResponse.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_DroneGoToResponse(const char* heap_ptr, Hako_DroneGoToResponse &src, HakoCpp_DroneGoToResponse &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.ok, dst.ok);
    // string convertor
    dst.message = hako_convert_string_from_pdu(src.message, M_SIZE(Hako_DroneGoToResponse, message));
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_DroneGoToResponse(Hako_DroneGoToResponse &src, HakoCpp_DroneGoToResponse &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_DroneGoToResponse((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_DroneGoToResponse(HakoCpp_DroneGoToResponse &src, Hako_DroneGoToResponse &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.ok, dst.ok);
        // string convertor
        hako_convert_string_to_pdu(src.message, dst.message, M_SIZE(Hako_DroneGoToResponse, message));
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_DroneGoToResponse(HakoCpp_DroneGoToResponse &src, Hako_DroneGoToResponse** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_DroneGoToResponse out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_DroneGoToResponse(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_DroneGoToResponse), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_DroneGoToResponse));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_DroneGoToResponse*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_DroneGoToResponse* hako_create_empty_pdu_DroneGoToResponse(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_DroneGoToResponse), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_DroneGoToResponse*)base_ptr;
}
namespace hako::pdu::msgs::drone_srv_msgs
{
class DroneGoToResponse
{
public:
    DroneGoToResponse() = default;
    ~DroneGoToResponse() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_DroneGoToResponse& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "DroneGoToResponse" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_DroneGoToResponse(*(Hako_DroneGoToResponse*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "DroneGoToResponse" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_DroneGoToResponse() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_DroneGoToResponse& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_DroneGoToResponse out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_DroneGoToResponse(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "DroneGoToResponse" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("DroneGoToResponse", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_drone_srv_msgs_DroneGoToResponse_HPP_ */
