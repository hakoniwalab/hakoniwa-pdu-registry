#ifndef _PDU_CPPTYPE_CONV_HAKO_nav_msgs_Path_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_nav_msgs_Path_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "nav_msgs/pdu_ctype_Path.h"
/*
 * Dependent cpp pdu data
 */
#include "nav_msgs/pdu_cpptype_Path.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_conv_PoseStamped.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Quaternion.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_struct_array_Path_poses(const char* heap_ptr, Hako_Path &src, HakoCpp_Path &dst)
{
    // Convert using len and off
    int offset = src._poses_off;
    int length = src._poses_len;
    if (length > 0) {
        dst.poses.resize(length);
        Hako_PoseStamped *temp_struct_ptr = (Hako_PoseStamped *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_PoseStamped(heap_ptr, *temp_struct_ptr, dst.poses[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int cpp_pdu2cpp_Path(const char* heap_ptr, Hako_Path &src, HakoCpp_Path &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // struct array convertor
    cpp_pdu2cpp_struct_array_Path_poses(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_Path(Hako_Path &src, HakoCpp_Path &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_Path((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_struct_array_Path_poses(HakoCpp_Path &src, Hako_Path &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._poses_len = src.poses.size();
    if (dst._poses_len > 0) {
        Hako_PoseStamped* temp_struct_ptr = (Hako_PoseStamped*)dynamic_memory.allocate(dst._poses_len, sizeof(Hako_PoseStamped));
        dst._poses_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._poses_len; ++i) {
            cpp_cpp2pdu_PoseStamped(src.poses[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._poses_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_Path(HakoCpp_Path &src, Hako_Path &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory);
        //struct array convert
        cpp_cpp2pdu_struct_array_Path_poses(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_Path(HakoCpp_Path &src, Hako_Path** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Path out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_Path(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Path), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Path));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Path*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Path* hako_create_empty_pdu_Path(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Path), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Path*)base_ptr;
}
namespace hako::pdu::msgs::nav_msgs
{
class Path
{
public:
    Path() = default;
    ~Path() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_Path& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "Path" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_Path(*(Hako_Path*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "Path" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_Path() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    int cpp2pdu(HakoCpp_Path& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_Path out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_Path(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "Path" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        const int meta_size = (int)HAKO_PDU_META_DATA_SIZE();
        const int base_size = (int)HAKO_ALIGN_SIZE(sizeof(Hako_Path), HAKO_ALIGNMENT_SIZE);
        const int heap_used = dynamic_memory.get_total_size();
        const int heap_size = (int)HAKO_ALIGN_SIZE(heap_used, HAKO_ALIGNMENT_SIZE);
        const int pdu_size = meta_size + base_size + heap_size;
        if (pdu_buffer == nullptr || pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "Path" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
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
        memcpy(base_ptr, (void*)&out, sizeof(Hako_Path));
        memset(base_ptr + sizeof(Hako_Path), 0, base_size - sizeof(Hako_Path));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_nav_msgs_Path_HPP_ */
