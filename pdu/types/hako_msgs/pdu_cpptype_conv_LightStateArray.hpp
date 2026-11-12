#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_msgs_LightStateArray_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_msgs_LightStateArray_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_LightStateArray.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_msgs/pdu_cpptype_LightStateArray.hpp"

/*
 * Dependent Convertors
 */
#include "hako_msgs/pdu_cpptype_conv_LightState.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_struct_array_LightStateArray_lights(const char* heap_ptr, Hako_LightStateArray &src, HakoCpp_LightStateArray &dst)
{
    // Convert using len and off
    int offset = src._lights_off;
    int length = src._lights_len;
    if (length > 0) {
        dst.lights.resize(length);
        Hako_LightState *temp_struct_ptr = (Hako_LightState *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_LightState(heap_ptr, *temp_struct_ptr, dst.lights[i]);
            temp_struct_ptr++;
        }
    }
    else {
        dst.lights.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}

static inline int cpp_pdu2cpp_LightStateArray(const char* heap_ptr, Hako_LightStateArray &src, HakoCpp_LightStateArray &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.stamp_usec, dst.stamp_usec);
    // string convertor
    dst.carrier = hako_convert_string_from_pdu(src.carrier, M_SIZE(Hako_LightStateArray, carrier));
    // struct array convertor
    cpp_pdu2cpp_struct_array_LightStateArray_lights(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_LightStateArray(Hako_LightStateArray &src, HakoCpp_LightStateArray &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_LightStateArray((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_struct_array_LightStateArray_lights(HakoCpp_LightStateArray &src, Hako_LightStateArray &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._lights_len = hako_pdu_array_length(src.lights.size());
    if (dst._lights_len > 0) {
        Hako_LightState* temp_struct_ptr = (Hako_LightState*)dynamic_memory.allocate(dst._lights_len, sizeof(Hako_LightState));
        dst._lights_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._lights_len; ++i) {
            if (!cpp_cpp2pdu_LightState(src.lights[i], *temp_struct_ptr, dynamic_memory)) {
                return false;
            }
            temp_struct_ptr++;
        }
    }
    else {
        dst._lights_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_LightStateArray(HakoCpp_LightStateArray &src, Hako_LightStateArray &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.stamp_usec, dst.stamp_usec);
        // string convertor
        hako_convert_string_to_pdu(src.carrier, dst.carrier, M_SIZE(Hako_LightStateArray, carrier));
        //struct array convert
        if (!cpp_cpp2pdu_struct_array_LightStateArray_lights(src, dst, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_LightStateArray(HakoCpp_LightStateArray &src, Hako_LightStateArray** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_LightStateArray out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_LightStateArray(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_LightStateArray), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_LightStateArray));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_LightStateArray*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_LightStateArray* hako_create_empty_pdu_LightStateArray(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_LightStateArray), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_LightStateArray*)base_ptr;
}
namespace hako::pdu::msgs::hako_msgs
{
class LightStateArray
{
public:
    LightStateArray() = default;
    ~LightStateArray() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_LightStateArray& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "LightStateArray" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_LightStateArray(*(Hako_LightStateArray*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "LightStateArray" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_LightStateArray() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_LightStateArray& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_LightStateArray out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_LightStateArray(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "LightStateArray" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("LightStateArray", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_msgs_LightStateArray_HPP_ */
