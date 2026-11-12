#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_msgs_ContactEvent_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_msgs_ContactEvent_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_ContactEvent.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_msgs/pdu_cpptype_ContactEvent.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Point.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_ContactEvent(const char* heap_ptr, Hako_ContactEvent &src, HakoCpp_ContactEvent &dst)
{
    // Struct convert
    cpp_pdu2cpp_Time(heap_ptr, src.stamp, dst.stamp);
    // string convertor
    dst.self_name = hako_convert_string_from_pdu(src.self_name, M_SIZE(Hako_ContactEvent, self_name));
    // string convertor
    dst.other_name = hako_convert_string_from_pdu(src.other_name, M_SIZE(Hako_ContactEvent, other_name));
    // string convertor
    dst.other_kind = hako_convert_string_from_pdu(src.other_kind, M_SIZE(Hako_ContactEvent, other_kind));
    // Struct convert
    cpp_pdu2cpp_Point(heap_ptr, src.position, dst.position);
    // primitive convert
    hako_convert_pdu2cpp(src.relative_speed, dst.relative_speed);
    // primitive convert
    hako_convert_pdu2cpp(src.started, dst.started);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_ContactEvent(Hako_ContactEvent &src, HakoCpp_ContactEvent &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_ContactEvent((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_ContactEvent(HakoCpp_ContactEvent &src, Hako_ContactEvent &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!cpp_cpp2pdu_Time(src.stamp, dst.stamp, dynamic_memory)) {
            return false;
        }
        // string convertor
        hako_convert_string_to_pdu(src.self_name, dst.self_name, M_SIZE(Hako_ContactEvent, self_name));
        // string convertor
        hako_convert_string_to_pdu(src.other_name, dst.other_name, M_SIZE(Hako_ContactEvent, other_name));
        // string convertor
        hako_convert_string_to_pdu(src.other_kind, dst.other_kind, M_SIZE(Hako_ContactEvent, other_kind));
        // struct convert
        if (!cpp_cpp2pdu_Point(src.position, dst.position, dynamic_memory)) {
            return false;
        }
        // primitive convert
        hako_convert_cpp2pdu(src.relative_speed, dst.relative_speed);
        // primitive convert
        hako_convert_cpp2pdu(src.started, dst.started);
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_ContactEvent(HakoCpp_ContactEvent &src, Hako_ContactEvent** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_ContactEvent out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_ContactEvent(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_ContactEvent), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_ContactEvent));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_ContactEvent*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_ContactEvent* hako_create_empty_pdu_ContactEvent(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_ContactEvent), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_ContactEvent*)base_ptr;
}
namespace hako::pdu::msgs::hako_msgs
{
class ContactEvent
{
public:
    ContactEvent() = default;
    ~ContactEvent() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_ContactEvent& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "ContactEvent" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_ContactEvent(*(Hako_ContactEvent*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "ContactEvent" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_ContactEvent() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_ContactEvent& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_ContactEvent out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_ContactEvent(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "ContactEvent" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("ContactEvent", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_msgs_ContactEvent_HPP_ */
