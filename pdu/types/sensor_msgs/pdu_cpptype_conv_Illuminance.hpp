#ifndef _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_Illuminance_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_Illuminance_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_Illuminance.h"
/*
 * Dependent cpp pdu data
 */
#include "sensor_msgs/pdu_cpptype_Illuminance.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_Illuminance(const char* heap_ptr, Hako_Illuminance &src, HakoCpp_Illuminance &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // primitive convert
    hako_convert_pdu2cpp(src.illuminance, dst.illuminance);
    // primitive convert
    hako_convert_pdu2cpp(src.variance, dst.variance);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_Illuminance(Hako_Illuminance &src, HakoCpp_Illuminance &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_Illuminance((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_Illuminance(HakoCpp_Illuminance &src, Hako_Illuminance &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory);
        // primitive convert
        hako_convert_cpp2pdu(src.illuminance, dst.illuminance);
        // primitive convert
        hako_convert_cpp2pdu(src.variance, dst.variance);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_Illuminance(HakoCpp_Illuminance &src, Hako_Illuminance** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Illuminance out;
    if (!cpp_cpp2pdu_Illuminance(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Illuminance), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Illuminance));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Illuminance*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Illuminance* hako_create_empty_pdu_Illuminance(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Illuminance), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Illuminance*)base_ptr;
}
namespace hako::pdu::msgs::sensor_msgs
{
class Illuminance
{
public:
    Illuminance() = default;
    ~Illuminance() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_Illuminance& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "Illuminance" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_Illuminance(*(Hako_Illuminance*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "Illuminance" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_Illuminance& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_Illuminance(cppData, (Hako_Illuminance**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "Illuminance" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "Illuminance" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "Illuminance" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_Illuminance_HPP_ */
