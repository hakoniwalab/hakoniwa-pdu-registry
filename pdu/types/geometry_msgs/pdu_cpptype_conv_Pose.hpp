#ifndef _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_Pose_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_Pose_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_Pose.h"
/*
 * Dependent cpp pdu data
 */
#include "geometry_msgs/pdu_cpptype_Pose.hpp"

/*
 * Dependent Convertors
 */
#include "geometry_msgs/pdu_cpptype_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Quaternion.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_Pose(const char* heap_ptr, Hako_Pose &src, HakoCpp_Pose &dst)
{
    // Struct convert
    cpp_pdu2cpp_Point(heap_ptr, src.position, dst.position);
    // Struct convert
    cpp_pdu2cpp_Quaternion(heap_ptr, src.orientation, dst.orientation);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_Pose(Hako_Pose &src, HakoCpp_Pose &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_Pose((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_Pose(HakoCpp_Pose &src, Hako_Pose &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!cpp_cpp2pdu_Point(src.position, dst.position, dynamic_memory)) {
            return false;
        }
        // struct convert
        if (!cpp_cpp2pdu_Quaternion(src.orientation, dst.orientation, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_Pose(HakoCpp_Pose &src, Hako_Pose** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Pose out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_Pose(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Pose), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Pose));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Pose*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Pose* hako_create_empty_pdu_Pose(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Pose), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Pose*)base_ptr;
}
namespace hako::pdu::msgs::geometry_msgs
{
class Pose
{
public:
    Pose() = default;
    ~Pose() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_Pose& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "Pose" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_Pose(*(Hako_Pose*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "Pose" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_Pose() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_Pose& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_Pose out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_Pose(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "Pose" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("Pose", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_Pose_HPP_ */
