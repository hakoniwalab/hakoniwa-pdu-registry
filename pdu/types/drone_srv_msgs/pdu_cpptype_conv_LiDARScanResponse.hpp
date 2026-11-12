#ifndef _PDU_CPPTYPE_CONV_HAKO_drone_srv_msgs_LiDARScanResponse_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_drone_srv_msgs_LiDARScanResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "drone_srv_msgs/pdu_ctype_LiDARScanResponse.h"
/*
 * Dependent cpp pdu data
 */
#include "drone_srv_msgs/pdu_cpptype_LiDARScanResponse.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Quaternion.hpp"
#include "sensor_msgs/pdu_cpptype_conv_PointCloud2.hpp"
#include "sensor_msgs/pdu_cpptype_conv_PointField.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_LiDARScanResponse(const char* heap_ptr, Hako_LiDARScanResponse &src, HakoCpp_LiDARScanResponse &dst)
{
    // primitive convert
    hako_convert_pdu2cpp(src.ok, dst.ok);
    // Struct convert
    cpp_pdu2cpp_PointCloud2(heap_ptr, src.point_cloud, dst.point_cloud);
    // Struct convert
    cpp_pdu2cpp_Pose(heap_ptr, src.lidar_pose, dst.lidar_pose);
    // string convertor
    dst.message = (const char*)src.message;
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_LiDARScanResponse(Hako_LiDARScanResponse &src, HakoCpp_LiDARScanResponse &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_LiDARScanResponse((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_LiDARScanResponse(HakoCpp_LiDARScanResponse &src, Hako_LiDARScanResponse &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_cpp2pdu(src.ok, dst.ok);
        // struct convert
        cpp_cpp2pdu_PointCloud2(src.point_cloud, dst.point_cloud, dynamic_memory);
        // struct convert
        cpp_cpp2pdu_Pose(src.lidar_pose, dst.lidar_pose, dynamic_memory);
        // string convertor
        (void)hako_convert_cpp2pdu_array(
            src.message, src.message.length(),
            dst.message, M_ARRAY_SIZE(Hako_LiDARScanResponse, char, message));
        dst.message[src.message.length()] = '\0';
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_LiDARScanResponse(HakoCpp_LiDARScanResponse &src, Hako_LiDARScanResponse** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_LiDARScanResponse out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_LiDARScanResponse(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_LiDARScanResponse), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_LiDARScanResponse));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_LiDARScanResponse*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_LiDARScanResponse* hako_create_empty_pdu_LiDARScanResponse(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_LiDARScanResponse), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_LiDARScanResponse*)base_ptr;
}
namespace hako::pdu::msgs::drone_srv_msgs
{
class LiDARScanResponse
{
public:
    LiDARScanResponse() = default;
    ~LiDARScanResponse() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_LiDARScanResponse& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "LiDARScanResponse" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_LiDARScanResponse(*(Hako_LiDARScanResponse*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "LiDARScanResponse" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_LiDARScanResponse() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    int cpp2pdu(HakoCpp_LiDARScanResponse& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_LiDARScanResponse out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_LiDARScanResponse(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "LiDARScanResponse" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        const int meta_size = (int)HAKO_PDU_META_DATA_SIZE();
        const int base_size = (int)HAKO_ALIGN_SIZE(sizeof(Hako_LiDARScanResponse), HAKO_ALIGNMENT_SIZE);
        const int heap_used = dynamic_memory.get_total_size();
        const int heap_size = (int)HAKO_ALIGN_SIZE(heap_used, HAKO_ALIGNMENT_SIZE);
        const int pdu_size = meta_size + base_size + heap_size;
        if (pdu_buffer == nullptr || pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "LiDARScanResponse" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
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
        memcpy(base_ptr, (void*)&out, sizeof(Hako_LiDARScanResponse));
        memset(base_ptr + sizeof(Hako_LiDARScanResponse), 0, base_size - sizeof(Hako_LiDARScanResponse));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_drone_srv_msgs_LiDARScanResponse_HPP_ */
