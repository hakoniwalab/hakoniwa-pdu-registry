#ifndef _PDU_CPPTYPE_CONV_HAKO_ackermann_msgs_AckermannDrive_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_ackermann_msgs_AckermannDrive_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "ackermann_msgs/pdu_ctype_AckermannDrive.h"
/*
 * Dependent cpp pdu data
 */
#include "ackermann_msgs/pdu_cpptype_AckermannDrive.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_AckermannDrive(const char* heap_ptr, Hako_AckermannDrive &src, HakoCpp_AckermannDrive &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.steering_angle, dst.steering_angle);
    // primitive convert
    hako_convert_pdu2cpp(src.steering_angle_velocity, dst.steering_angle_velocity);
    // primitive convert
    hako_convert_pdu2cpp(src.speed, dst.speed);
    // primitive convert
    hako_convert_pdu2cpp(src.acceleration, dst.acceleration);
    // primitive convert
    hako_convert_pdu2cpp(src.jerk, dst.jerk);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_AckermannDrive(Hako_AckermannDrive &src, HakoCpp_AckermannDrive &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_AckermannDrive((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_AckermannDrive(HakoCpp_AckermannDrive &src, Hako_AckermannDrive &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.steering_angle, dst.steering_angle);
        // primitive convert
        hako_convert_cpp2pdu(src.steering_angle_velocity, dst.steering_angle_velocity);
        // primitive convert
        hako_convert_cpp2pdu(src.speed, dst.speed);
        // primitive convert
        hako_convert_cpp2pdu(src.acceleration, dst.acceleration);
        // primitive convert
        hako_convert_cpp2pdu(src.jerk, dst.jerk);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_AckermannDrive(HakoCpp_AckermannDrive &src, Hako_AckermannDrive** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_AckermannDrive out;
    if (!cpp_cpp2pdu_AckermannDrive(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_AckermannDrive), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_AckermannDrive));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_AckermannDrive*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_AckermannDrive* hako_create_empty_pdu_AckermannDrive(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_AckermannDrive), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_AckermannDrive*)base_ptr;
}
namespace hako::pdu::msgs::ackermann_msgs
{
class AckermannDrive
{
public:
    AckermannDrive() = default;
    ~AckermannDrive() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_AckermannDrive& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "AckermannDrive" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        }
        int ret = hako_convert_pdu2cpp_AckermannDrive(*(Hako_AckermannDrive*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "AckermannDrive" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_AckermannDrive& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_AckermannDrive(cppData, (Hako_AckermannDrive**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "AckermannDrive" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "AckermannDrive" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "AckermannDrive" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_ackermann_msgs_AckermannDrive_HPP_ */
