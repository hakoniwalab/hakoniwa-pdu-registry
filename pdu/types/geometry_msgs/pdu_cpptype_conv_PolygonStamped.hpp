#ifndef _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_PolygonStamped_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_PolygonStamped_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_PolygonStamped.h"
/*
 * Dependent cpp pdu data
 */
#include "geometry_msgs/pdu_cpptype_PolygonStamped.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Point32.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Polygon.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_PolygonStamped(const char* heap_ptr, Hako_PolygonStamped &src, HakoCpp_PolygonStamped &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // Struct convert
    cpp_pdu2cpp_Polygon(heap_ptr, src.polygon, dst.polygon);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_PolygonStamped(Hako_PolygonStamped &src, HakoCpp_PolygonStamped &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_PolygonStamped((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_PolygonStamped(HakoCpp_PolygonStamped &src, Hako_PolygonStamped &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory)) {
            return false;
        }
        // struct convert
        if (!cpp_cpp2pdu_Polygon(src.polygon, dst.polygon, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_PolygonStamped(HakoCpp_PolygonStamped &src, Hako_PolygonStamped** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_PolygonStamped out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_PolygonStamped(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_PolygonStamped), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_PolygonStamped));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_PolygonStamped*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_PolygonStamped* hako_create_empty_pdu_PolygonStamped(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_PolygonStamped), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_PolygonStamped*)base_ptr;
}
namespace hako::pdu::msgs::geometry_msgs
{
class PolygonStamped
{
public:
    PolygonStamped() = default;
    ~PolygonStamped() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_PolygonStamped& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "PolygonStamped" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_PolygonStamped(*(Hako_PolygonStamped*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "PolygonStamped" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_PolygonStamped() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_PolygonStamped& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_PolygonStamped out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_PolygonStamped(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "PolygonStamped" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("PolygonStamped", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_PolygonStamped_HPP_ */
