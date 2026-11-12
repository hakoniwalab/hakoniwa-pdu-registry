#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_RenderObject_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_RenderObject_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_RenderObject.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_srv_msgs/pdu_cpptype_RenderObject.hpp"

/*
 * Dependent Convertors
 */
#include "geometry_msgs/pdu_cpptype_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Quaternion.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_RenderObject(const char* heap_ptr, Hako_RenderObject &src, HakoCpp_RenderObject &dst)
{
    // string convertor
    dst.name = hako_convert_string_from_pdu(src.name, M_SIZE(Hako_RenderObject, name));
    // string convertor
    dst.model = hako_convert_string_from_pdu(src.model, M_SIZE(Hako_RenderObject, model));
    // Struct convert
    cpp_pdu2cpp_Pose(heap_ptr, src.pose, dst.pose);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_RenderObject(Hako_RenderObject &src, HakoCpp_RenderObject &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_RenderObject((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_RenderObject(HakoCpp_RenderObject &src, Hako_RenderObject &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // string convertor
        hako_convert_string_to_pdu(src.name, dst.name, M_SIZE(Hako_RenderObject, name));
        // string convertor
        hako_convert_string_to_pdu(src.model, dst.model, M_SIZE(Hako_RenderObject, model));
        // struct convert
        if (!cpp_cpp2pdu_Pose(src.pose, dst.pose, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_RenderObject(HakoCpp_RenderObject &src, Hako_RenderObject** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_RenderObject out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_RenderObject(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_RenderObject), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_RenderObject));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_RenderObject*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_RenderObject* hako_create_empty_pdu_RenderObject(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_RenderObject), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_RenderObject*)base_ptr;
}
namespace hako::pdu::msgs::hako_srv_msgs
{
class RenderObject
{
public:
    RenderObject() = default;
    ~RenderObject() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_RenderObject& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "RenderObject" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_RenderObject(*(Hako_RenderObject*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "RenderObject" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_RenderObject() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_RenderObject& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_RenderObject out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_RenderObject(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "RenderObject" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("RenderObject", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_srv_msgs_RenderObject_HPP_ */
