#ifndef _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_TransformStamped_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_TransformStamped_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_TransformStamped.h"
/*
 * Dependent cpp pdu data
 */
#include "geometry_msgs/pdu_cpptype_TransformStamped.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Transform.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Vector3.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_TransformStamped(const char* heap_ptr, Hako_TransformStamped &src, HakoCpp_TransformStamped &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // string convertor
    dst.child_frame_id = hako_convert_string_from_pdu(src.child_frame_id, M_SIZE(Hako_TransformStamped, child_frame_id));
    // Struct convert
    cpp_pdu2cpp_Transform(heap_ptr, src.transform, dst.transform);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_TransformStamped(Hako_TransformStamped &src, HakoCpp_TransformStamped &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_TransformStamped((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_TransformStamped(HakoCpp_TransformStamped &src, Hako_TransformStamped &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory)) {
            return false;
        }
        // string convertor
        hako_convert_string_to_pdu(src.child_frame_id, dst.child_frame_id, M_SIZE(Hako_TransformStamped, child_frame_id));
        // struct convert
        if (!cpp_cpp2pdu_Transform(src.transform, dst.transform, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_TransformStamped(HakoCpp_TransformStamped &src, Hako_TransformStamped** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_TransformStamped out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_TransformStamped(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_TransformStamped), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_TransformStamped));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_TransformStamped*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_TransformStamped* hako_create_empty_pdu_TransformStamped(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_TransformStamped), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_TransformStamped*)base_ptr;
}
namespace hako::pdu::msgs::geometry_msgs
{
class TransformStamped
{
public:
    TransformStamped() = default;
    ~TransformStamped() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_TransformStamped& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "TransformStamped" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_TransformStamped(*(Hako_TransformStamped*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "TransformStamped" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_TransformStamped() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_TransformStamped& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_TransformStamped out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_TransformStamped(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "TransformStamped" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("TransformStamped", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_TransformStamped_HPP_ */
