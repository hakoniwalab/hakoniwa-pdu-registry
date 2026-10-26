#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_PersonStepRequest_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_PersonStepRequest_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_PersonStepRequest.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_srv_msgs/pdu_cpptype_PersonStepRequest.hpp"

/*
 * Dependent Convertors
 */
#include "geometry_msgs/pdu_cpptype_conv_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Vector3.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_PersonStepRequest(const char* heap_ptr, Hako_PersonStepRequest &src, HakoCpp_PersonStepRequest &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.step, dst.step);
    // Struct convert
    cpp_pdu2cpp_Twist(heap_ptr, src.cmd_vel, dst.cmd_vel);
    // string convertor
    dst.animation = (const char*)src.animation;
    // string convertor
    dst.ride = (const char*)src.ride;
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_PersonStepRequest(Hako_PersonStepRequest &src, HakoCpp_PersonStepRequest &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_PersonStepRequest((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_PersonStepRequest(HakoCpp_PersonStepRequest &src, Hako_PersonStepRequest &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.step, dst.step);
        // struct convert
        cpp_cpp2pdu_Twist(src.cmd_vel, dst.cmd_vel, dynamic_memory);
        // string convertor
        (void)hako_convert_cpp2pdu_array(
            src.animation, src.animation.length(),
            dst.animation, M_ARRAY_SIZE(Hako_PersonStepRequest, char, animation));
        dst.animation[src.animation.length()] = '\0';
        // string convertor
        (void)hako_convert_cpp2pdu_array(
            src.ride, src.ride.length(),
            dst.ride, M_ARRAY_SIZE(Hako_PersonStepRequest, char, ride));
        dst.ride[src.ride.length()] = '\0';
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_PersonStepRequest(HakoCpp_PersonStepRequest &src, Hako_PersonStepRequest** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_PersonStepRequest out;
    if (!cpp_cpp2pdu_PersonStepRequest(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_PersonStepRequest), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_PersonStepRequest));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_PersonStepRequest*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_PersonStepRequest* hako_create_empty_pdu_PersonStepRequest(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_PersonStepRequest), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_PersonStepRequest*)base_ptr;
}
namespace hako::pdu::msgs::hako_srv_msgs
{
class PersonStepRequest
{
public:
    PersonStepRequest() = default;
    ~PersonStepRequest() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_PersonStepRequest& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "PersonStepRequest" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_PersonStepRequest(*(Hako_PersonStepRequest*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "PersonStepRequest" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_PersonStepRequest& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_PersonStepRequest(cppData, (Hako_PersonStepRequest**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "PersonStepRequest" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "PersonStepRequest" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "PersonStepRequest" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_PersonStepRequest_HPP_ */
