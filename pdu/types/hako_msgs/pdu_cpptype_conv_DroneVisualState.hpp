#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_msgs_DroneVisualState_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_msgs_DroneVisualState_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_DroneVisualState.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_msgs/pdu_cpptype_DroneVisualState.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_DroneVisualState_pwm_duty(const char* heap_ptr, Hako_DroneVisualState &src, HakoCpp_DroneVisualState &dst)
{
    // Convert using len and off
    int offset = src._pwm_duty_off;
    int length = src._pwm_duty_len;
    if (length > 0) {
        dst.pwm_duty.resize(length);
        memcpy(dst.pwm_duty.data(), heap_ptr + offset, length * sizeof(Hako_float32));
    }
    return 0;
}

static inline int cpp_pdu2cpp_DroneVisualState(const char* heap_ptr, Hako_DroneVisualState &src, HakoCpp_DroneVisualState &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.x, dst.x);
    // primitive convert
    hako_convert_pdu2cpp(src.y, dst.y);
    // primitive convert
    hako_convert_pdu2cpp(src.z, dst.z);
    // primitive convert
    hako_convert_pdu2cpp(src.roll, dst.roll);
    // primitive convert
    hako_convert_pdu2cpp(src.pitch, dst.pitch);
    // primitive convert
    hako_convert_pdu2cpp(src.yaw, dst.yaw);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_DroneVisualState_pwm_duty(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_DroneVisualState(Hako_DroneVisualState &src, HakoCpp_DroneVisualState &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_DroneVisualState((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_DroneVisualState_pwm_duty(HakoCpp_DroneVisualState &src, Hako_DroneVisualState &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray
    dst._pwm_duty_len = src.pwm_duty.size();
    if (dst._pwm_duty_len > 0) {
        void* temp_ptr = dynamic_memory.allocate(dst._pwm_duty_len, sizeof(Hako_float32));
        memcpy(temp_ptr, src.pwm_duty.data(), dst._pwm_duty_len * sizeof(Hako_float32));
        dst._pwm_duty_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._pwm_duty_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_DroneVisualState(HakoCpp_DroneVisualState &src, Hako_DroneVisualState &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.x, dst.x);
        // primitive convert
        hako_convert_cpp2pdu(src.y, dst.y);
        // primitive convert
        hako_convert_cpp2pdu(src.z, dst.z);
        // primitive convert
        hako_convert_cpp2pdu(src.roll, dst.roll);
        // primitive convert
        hako_convert_cpp2pdu(src.pitch, dst.pitch);
        // primitive convert
        hako_convert_cpp2pdu(src.yaw, dst.yaw);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_DroneVisualState_pwm_duty(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_DroneVisualState(HakoCpp_DroneVisualState &src, Hako_DroneVisualState** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_DroneVisualState out;
    if (!cpp_cpp2pdu_DroneVisualState(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_DroneVisualState), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_DroneVisualState));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_DroneVisualState*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_DroneVisualState* hako_create_empty_pdu_DroneVisualState(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_DroneVisualState), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_DroneVisualState*)base_ptr;
}
namespace hako::pdu::msgs::hako_msgs
{
class DroneVisualState
{
public:
    DroneVisualState() = default;
    ~DroneVisualState() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_DroneVisualState& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "DroneVisualState" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_DroneVisualState(*(Hako_DroneVisualState*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "DroneVisualState" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_DroneVisualState& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_DroneVisualState(cppData, (Hako_DroneVisualState**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "DroneVisualState" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "DroneVisualState" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "DroneVisualState" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_msgs_DroneVisualState_HPP_ */
