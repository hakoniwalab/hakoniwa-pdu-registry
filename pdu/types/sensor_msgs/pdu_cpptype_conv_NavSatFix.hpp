#ifndef _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_NavSatFix_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_NavSatFix_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_NavSatFix.h"
/*
 * Dependent cpp pdu data
 */
#include "sensor_msgs/pdu_cpptype_NavSatFix.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "sensor_msgs/pdu_cpptype_conv_NavSatStatus.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_NavSatFix_position_covariance(const char* heap_ptr, Hako_NavSatFix &src, HakoCpp_NavSatFix &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 9; ++i) {
        hako_convert_pdu2cpp(src.position_covariance[i], dst.position_covariance[i]);
    }
    return 0;
}

static inline int cpp_pdu2cpp_NavSatFix(const char* heap_ptr, Hako_NavSatFix &src, HakoCpp_NavSatFix &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // Struct convert
    cpp_pdu2cpp_NavSatStatus(heap_ptr, src.status, dst.status);
    // primitive convert
    hako_convert_pdu2cpp(src.latitude, dst.latitude);
    // primitive convert
    hako_convert_pdu2cpp(src.longitude, dst.longitude);
    // primitive convert
    hako_convert_pdu2cpp(src.altitude, dst.altitude);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_NavSatFix_position_covariance(heap_ptr, src, dst);
    // primitive convert
    hako_convert_pdu2cpp(src.position_covariance_type, dst.position_covariance_type);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_NavSatFix(Hako_NavSatFix &src, HakoCpp_NavSatFix &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_NavSatFix((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_NavSatFix_position_covariance(HakoCpp_NavSatFix &src, Hako_NavSatFix &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 9
    (void)dynamic_memory;
    (void)hako_convert_cpp2pdu_array(
        src.position_covariance, src.position_covariance.size(),
        dst.position_covariance, M_ARRAY_SIZE(Hako_NavSatFix, Hako_float64, position_covariance));
    return true;
}

static inline bool cpp_cpp2pdu_NavSatFix(HakoCpp_NavSatFix &src, Hako_NavSatFix &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory);
        // struct convert
        cpp_cpp2pdu_NavSatStatus(src.status, dst.status, dynamic_memory);
        // primitive convert
        hako_convert_cpp2pdu(src.latitude, dst.latitude);
        // primitive convert
        hako_convert_cpp2pdu(src.longitude, dst.longitude);
        // primitive convert
        hako_convert_cpp2pdu(src.altitude, dst.altitude);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_NavSatFix_position_covariance(src, dst, dynamic_memory);
        // primitive convert
        hako_convert_cpp2pdu(src.position_covariance_type, dst.position_covariance_type);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_NavSatFix(HakoCpp_NavSatFix &src, Hako_NavSatFix** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_NavSatFix out;
    if (!cpp_cpp2pdu_NavSatFix(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_NavSatFix), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_NavSatFix));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_NavSatFix*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_NavSatFix* hako_create_empty_pdu_NavSatFix(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_NavSatFix), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_NavSatFix*)base_ptr;
}
namespace hako::pdu::msgs::sensor_msgs
{
class NavSatFix
{
public:
    NavSatFix() = default;
    ~NavSatFix() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_NavSatFix& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "NavSatFix" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_NavSatFix(*(Hako_NavSatFix*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "NavSatFix" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_NavSatFix& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_NavSatFix(cppData, (Hako_NavSatFix**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "NavSatFix" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "NavSatFix" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "NavSatFix" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_NavSatFix_HPP_ */
