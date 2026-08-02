#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_action_msgs_ActionResponseHeader_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_action_msgs_ActionResponseHeader_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_action_msgs/pdu_ctype_ActionResponseHeader.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_action_msgs/pdu_cpptype_ActionResponseHeader.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_ActionResponseHeader_goal_id(const char* heap_ptr, Hako_ActionResponseHeader &src, HakoCpp_ActionResponseHeader &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 16; ++i) {
        hako_convert_pdu2cpp(src.goal_id[i], dst.goal_id[i]);
    }
    return 0;
}

static inline int cpp_pdu2cpp_ActionResponseHeader(const char* heap_ptr, Hako_ActionResponseHeader &src, HakoCpp_ActionResponseHeader &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.version, dst.version);
    // primitive convert
    hako_convert_pdu2cpp(src.response_kind, dst.response_kind);
    // primitive convert
    hako_convert_pdu2cpp(src.status, dst.status);
    // primitive convert
    hako_convert_pdu2cpp(src.reserved, dst.reserved);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_ActionResponseHeader_goal_id(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_ActionResponseHeader(Hako_ActionResponseHeader &src, HakoCpp_ActionResponseHeader &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_ActionResponseHeader((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_ActionResponseHeader_goal_id(HakoCpp_ActionResponseHeader &src, Hako_ActionResponseHeader &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 16
    (void)dynamic_memory;
    (void)hako_convert_cpp2pdu_array(
        src.goal_id, src.goal_id.size(),
        dst.goal_id, M_ARRAY_SIZE(Hako_ActionResponseHeader, Hako_uint8, goal_id));
    return true;
}

static inline bool cpp_cpp2pdu_ActionResponseHeader(HakoCpp_ActionResponseHeader &src, Hako_ActionResponseHeader &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.version, dst.version);
        // primitive convert
        hako_convert_cpp2pdu(src.response_kind, dst.response_kind);
        // primitive convert
        hako_convert_cpp2pdu(src.status, dst.status);
        // primitive convert
        hako_convert_cpp2pdu(src.reserved, dst.reserved);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_ActionResponseHeader_goal_id(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_ActionResponseHeader(HakoCpp_ActionResponseHeader &src, Hako_ActionResponseHeader** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_ActionResponseHeader out;
    if (!cpp_cpp2pdu_ActionResponseHeader(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_ActionResponseHeader), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_ActionResponseHeader));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_ActionResponseHeader*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_ActionResponseHeader* hako_create_empty_pdu_ActionResponseHeader(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_ActionResponseHeader), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_ActionResponseHeader*)base_ptr;
}
namespace hako::pdu::msgs::hako_action_msgs
{
class ActionResponseHeader
{
public:
    ActionResponseHeader() = default;
    ~ActionResponseHeader() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_ActionResponseHeader& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "ActionResponseHeader" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_ActionResponseHeader(*(Hako_ActionResponseHeader*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "ActionResponseHeader" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_ActionResponseHeader& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_ActionResponseHeader(cppData, (Hako_ActionResponseHeader**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "ActionResponseHeader" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "ActionResponseHeader" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "ActionResponseHeader" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_action_msgs_ActionResponseHeader_HPP_ */
