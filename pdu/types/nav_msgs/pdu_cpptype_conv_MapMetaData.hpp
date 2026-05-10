#ifndef _PDU_CPPTYPE_CONV_HAKO_nav_msgs_MapMetaData_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_nav_msgs_MapMetaData_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "nav_msgs/pdu_ctype_MapMetaData.h"
/*
 * Dependent cpp pdu data
 */
#include "nav_msgs/pdu_cpptype_MapMetaData.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Quaternion.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/

static inline int cpp_pdu2cpp_MapMetaData(const char* heap_ptr, Hako_MapMetaData &src, HakoCpp_MapMetaData &dst)
{
    // Struct convert
    cpp_pdu2cpp_Time(heap_ptr, src.map_load_time, dst.map_load_time);
    // primitive convert
    hako_convert_pdu2cpp(src.resolution, dst.resolution);
    // primitive convert
    hako_convert_pdu2cpp(src.width, dst.width);
    // primitive convert
    hako_convert_pdu2cpp(src.height, dst.height);
    // Struct convert
    cpp_pdu2cpp_Pose(heap_ptr, src.origin, dst.origin);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_MapMetaData(Hako_MapMetaData &src, HakoCpp_MapMetaData &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_MapMetaData((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/

static inline bool cpp_cpp2pdu_MapMetaData(HakoCpp_MapMetaData &src, Hako_MapMetaData &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_Time(src.map_load_time, dst.map_load_time, dynamic_memory);
        // primitive convert
        hako_convert_cpp2pdu(src.resolution, dst.resolution);
        // primitive convert
        hako_convert_cpp2pdu(src.width, dst.width);
        // primitive convert
        hako_convert_cpp2pdu(src.height, dst.height);
        // struct convert
        cpp_cpp2pdu_Pose(src.origin, dst.origin, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_MapMetaData(HakoCpp_MapMetaData &src, Hako_MapMetaData** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_MapMetaData out;
    if (!cpp_cpp2pdu_MapMetaData(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_MapMetaData), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_MapMetaData));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_MapMetaData*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_MapMetaData* hako_create_empty_pdu_MapMetaData(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_MapMetaData), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_MapMetaData*)base_ptr;
}
namespace hako::pdu::msgs::nav_msgs
{
class MapMetaData
{
public:
    MapMetaData() = default;
    ~MapMetaData() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_MapMetaData& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "MapMetaData" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_MapMetaData(*(Hako_MapMetaData*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "MapMetaData" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_MapMetaData& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_MapMetaData(cppData, (Hako_MapMetaData**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "MapMetaData" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "MapMetaData" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "MapMetaData" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_nav_msgs_MapMetaData_HPP_ */
