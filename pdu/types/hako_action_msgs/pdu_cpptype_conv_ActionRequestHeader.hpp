#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_action_msgs_ActionRequestHeader_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_action_msgs_ActionRequestHeader_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_action_msgs/pdu_ctype_ActionRequestHeader.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_action_msgs/pdu_cpptype_ActionRequestHeader.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_ActionRequestHeader_reserved(const char* heap_ptr, Hako_ActionRequestHeader &src, HakoCpp_ActionRequestHeader &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 2; ++i) {
        hako_convert_pdu2cpp(src.reserved[i], dst.reserved[i]);
    }
    return 0;
}
static inline int cpp_pdu2cpp_primitive_array_ActionRequestHeader_goal_id(const char* heap_ptr, Hako_ActionRequestHeader &src, HakoCpp_ActionRequestHeader &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 16; ++i) {
        hako_convert_pdu2cpp(src.goal_id[i], dst.goal_id[i]);
    }
    return 0;
}

static inline int cpp_pdu2cpp_ActionRequestHeader(const char* heap_ptr, Hako_ActionRequestHeader &src, HakoCpp_ActionRequestHeader &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.version, dst.version);
    // primitive convert
    hako_convert_pdu2cpp(src.request_kind, dst.request_kind);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_ActionRequestHeader_reserved(heap_ptr, src, dst);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_ActionRequestHeader_goal_id(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_ActionRequestHeader(Hako_ActionRequestHeader &src, HakoCpp_ActionRequestHeader &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_ActionRequestHeader((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_ActionRequestHeader_reserved(HakoCpp_ActionRequestHeader &src, Hako_ActionRequestHeader &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 2
    (void)dynamic_memory;
    (void)hako_convert_cpp2pdu_array(
        src.reserved, src.reserved.size(),
        dst.reserved, M_ARRAY_SIZE(Hako_ActionRequestHeader, Hako_uint8, reserved));
    return true;
}
static inline bool cpp_cpp2pdu_primitive_array_ActionRequestHeader_goal_id(HakoCpp_ActionRequestHeader &src, Hako_ActionRequestHeader &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 16
    (void)dynamic_memory;
    (void)hako_convert_cpp2pdu_array(
        src.goal_id, src.goal_id.size(),
        dst.goal_id, M_ARRAY_SIZE(Hako_ActionRequestHeader, Hako_uint8, goal_id));
    return true;
}

static inline bool cpp_cpp2pdu_ActionRequestHeader(HakoCpp_ActionRequestHeader &src, Hako_ActionRequestHeader &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.version, dst.version);
        // primitive convert
        hako_convert_cpp2pdu(src.request_kind, dst.request_kind);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_ActionRequestHeader_reserved(src, dst, dynamic_memory);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_ActionRequestHeader_goal_id(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_ActionRequestHeader(HakoCpp_ActionRequestHeader &src, Hako_ActionRequestHeader** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_ActionRequestHeader out;
    if (!cpp_cpp2pdu_ActionRequestHeader(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_ActionRequestHeader), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_ActionRequestHeader));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_ActionRequestHeader*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_ActionRequestHeader* hako_create_empty_pdu_ActionRequestHeader(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_ActionRequestHeader), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_ActionRequestHeader*)base_ptr;
}
namespace hako::pdu::msgs::hako_action_msgs
{
class ActionRequestHeader
{
public:
    ActionRequestHeader() = default;
    ~ActionRequestHeader() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_ActionRequestHeader& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "ActionRequestHeader" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_ActionRequestHeader(*(Hako_ActionRequestHeader*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "ActionRequestHeader" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_ActionRequestHeader& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_ActionRequestHeader(cppData, (Hako_ActionRequestHeader**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "ActionRequestHeader" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "ActionRequestHeader" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "ActionRequestHeader" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_action_msgs_ActionRequestHeader_HPP_ */
