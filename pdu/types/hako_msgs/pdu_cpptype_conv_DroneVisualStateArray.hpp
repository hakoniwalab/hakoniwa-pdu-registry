#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_msgs_DroneVisualStateArray_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_msgs_DroneVisualStateArray_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_DroneVisualStateArray.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_msgs/pdu_cpptype_DroneVisualStateArray.hpp"

/*
 * Dependent Convertors
 */
#include "hako_msgs/pdu_cpptype_conv_DroneVisualState.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_struct_array_DroneVisualStateArray_drones(const char* heap_ptr, Hako_DroneVisualStateArray &src, HakoCpp_DroneVisualStateArray &dst)
{
    // Convert using len and off
    int offset = src._drones_off;
    int length = src._drones_len;
    if (length > 0) {
        dst.drones.resize(length);
        Hako_DroneVisualState *temp_struct_ptr = (Hako_DroneVisualState *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_DroneVisualState(heap_ptr, *temp_struct_ptr, dst.drones[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int cpp_pdu2cpp_DroneVisualStateArray(const char* heap_ptr, Hako_DroneVisualStateArray &src, HakoCpp_DroneVisualStateArray &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.sequence_id, dst.sequence_id);
    // primitive convert
    hako_convert_pdu2cpp(src.chunk_index, dst.chunk_index);
    // primitive convert
    hako_convert_pdu2cpp(src.chunk_count, dst.chunk_count);
    // primitive convert
    hako_convert_pdu2cpp(src.start_index, dst.start_index);
    // primitive convert
    hako_convert_pdu2cpp(src.valid_count, dst.valid_count);
    // struct array convertor
    cpp_pdu2cpp_struct_array_DroneVisualStateArray_drones(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_DroneVisualStateArray(Hako_DroneVisualStateArray &src, HakoCpp_DroneVisualStateArray &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_DroneVisualStateArray((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_struct_array_DroneVisualStateArray_drones(HakoCpp_DroneVisualStateArray &src, Hako_DroneVisualStateArray &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._drones_len = src.drones.size();
    if (dst._drones_len > 0) {
        Hako_DroneVisualState* temp_struct_ptr = (Hako_DroneVisualState*)dynamic_memory.allocate(dst._drones_len, sizeof(Hako_DroneVisualState));
        dst._drones_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._drones_len; ++i) {
            cpp_cpp2pdu_DroneVisualState(src.drones[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._drones_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_DroneVisualStateArray(HakoCpp_DroneVisualStateArray &src, Hako_DroneVisualStateArray &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.sequence_id, dst.sequence_id);
        // primitive convert
        hako_convert_cpp2pdu(src.chunk_index, dst.chunk_index);
        // primitive convert
        hako_convert_cpp2pdu(src.chunk_count, dst.chunk_count);
        // primitive convert
        hako_convert_cpp2pdu(src.start_index, dst.start_index);
        // primitive convert
        hako_convert_cpp2pdu(src.valid_count, dst.valid_count);
        //struct array convert
        cpp_cpp2pdu_struct_array_DroneVisualStateArray_drones(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_DroneVisualStateArray(HakoCpp_DroneVisualStateArray &src, Hako_DroneVisualStateArray** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_DroneVisualStateArray out;
    if (!cpp_cpp2pdu_DroneVisualStateArray(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_DroneVisualStateArray), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_DroneVisualStateArray));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_DroneVisualStateArray*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_DroneVisualStateArray* hako_create_empty_pdu_DroneVisualStateArray(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_DroneVisualStateArray), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_DroneVisualStateArray*)base_ptr;
}
namespace hako::pdu::msgs::hako_msgs
{
class DroneVisualStateArray
{
public:
    DroneVisualStateArray() = default;
    ~DroneVisualStateArray() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_DroneVisualStateArray& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "DroneVisualStateArray" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_DroneVisualStateArray(*(Hako_DroneVisualStateArray*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "DroneVisualStateArray" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_DroneVisualStateArray& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_DroneVisualStateArray(cppData, (Hako_DroneVisualStateArray**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "DroneVisualStateArray" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "DroneVisualStateArray" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "DroneVisualStateArray" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_msgs_DroneVisualStateArray_HPP_ */
