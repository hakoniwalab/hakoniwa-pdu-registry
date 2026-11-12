#ifndef _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_PoseWithCovarianceStamped_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_PoseWithCovarianceStamped_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_PoseWithCovarianceStamped.h"
/*
 * Dependent cpp pdu data
 */
#include "geometry_msgs/pdu_cpptype_PoseWithCovarianceStamped.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_conv_PoseWithCovariance.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Quaternion.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_PoseWithCovarianceStamped(const char* heap_ptr, Hako_PoseWithCovarianceStamped &src, HakoCpp_PoseWithCovarianceStamped &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // Struct convert
    cpp_pdu2cpp_PoseWithCovariance(heap_ptr, src.pose, dst.pose);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_PoseWithCovarianceStamped(Hako_PoseWithCovarianceStamped &src, HakoCpp_PoseWithCovarianceStamped &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_PoseWithCovarianceStamped((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_PoseWithCovarianceStamped(HakoCpp_PoseWithCovarianceStamped &src, Hako_PoseWithCovarianceStamped &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory);
        // struct convert
        cpp_cpp2pdu_PoseWithCovariance(src.pose, dst.pose, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_PoseWithCovarianceStamped(HakoCpp_PoseWithCovarianceStamped &src, Hako_PoseWithCovarianceStamped** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_PoseWithCovarianceStamped out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_PoseWithCovarianceStamped(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_PoseWithCovarianceStamped), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_PoseWithCovarianceStamped));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_PoseWithCovarianceStamped*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_PoseWithCovarianceStamped* hako_create_empty_pdu_PoseWithCovarianceStamped(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_PoseWithCovarianceStamped), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_PoseWithCovarianceStamped*)base_ptr;
}
namespace hako::pdu::msgs::geometry_msgs
{
class PoseWithCovarianceStamped
{
public:
    PoseWithCovarianceStamped() = default;
    ~PoseWithCovarianceStamped() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_PoseWithCovarianceStamped& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "PoseWithCovarianceStamped" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_PoseWithCovarianceStamped(*(Hako_PoseWithCovarianceStamped*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "PoseWithCovarianceStamped" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_PoseWithCovarianceStamped() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    int cpp2pdu(HakoCpp_PoseWithCovarianceStamped& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_PoseWithCovarianceStamped out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_PoseWithCovarianceStamped(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "PoseWithCovarianceStamped" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        const int meta_size = (int)HAKO_PDU_META_DATA_SIZE();
        const int base_size = (int)HAKO_ALIGN_SIZE(sizeof(Hako_PoseWithCovarianceStamped), HAKO_ALIGNMENT_SIZE);
        const int heap_used = dynamic_memory.get_total_size();
        const int heap_size = (int)HAKO_ALIGN_SIZE(heap_used, HAKO_ALIGNMENT_SIZE);
        const int pdu_size = meta_size + base_size + heap_size;
        if (pdu_buffer == nullptr || pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "PoseWithCovarianceStamped" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        memset(pdu_buffer, 0, meta_size);
        HakoPduMetaDataType* meta = (HakoPduMetaDataType*)pdu_buffer;
        meta->magicno = HAKO_PDU_META_DATA_MAGICNO;
        meta->version = HAKO_PDU_META_DATA_VERSION;
        meta->base_off = meta_size;
        meta->heap_off = meta_size + base_size;
        meta->total_size = pdu_size;
        char* base_ptr = pdu_buffer + meta_size;
        memcpy(base_ptr, (void*)&out, sizeof(Hako_PoseWithCovarianceStamped));
        memset(base_ptr + sizeof(Hako_PoseWithCovarianceStamped), 0, base_size - sizeof(Hako_PoseWithCovarianceStamped));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_PoseWithCovarianceStamped_HPP_ */
