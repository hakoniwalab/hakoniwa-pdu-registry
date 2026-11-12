#ifndef _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_CameraInfo_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_CameraInfo_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_CameraInfo.h"
/*
 * Dependent cpp pdu data
 */
#include "sensor_msgs/pdu_cpptype_CameraInfo.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "sensor_msgs/pdu_cpptype_conv_RegionOfInterest.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_CameraInfo_d(const char* heap_ptr, Hako_CameraInfo &src, HakoCpp_CameraInfo &dst)
{
    // Convert using len and off
    int offset = src._d_off;
    int length = src._d_len;
    if (length > 0) {
        dst.d.resize(length);
        memcpy(dst.d.data(), heap_ptr + offset, length * sizeof(Hako_float64));
    }
    else {
        dst.d.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}
static inline int cpp_pdu2cpp_primitive_array_CameraInfo_k(const char* heap_ptr, Hako_CameraInfo &src, HakoCpp_CameraInfo &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 9; ++i) {
        hako_convert_pdu2cpp(src.k[i], dst.k[i]);
    }
    return 0;
}
static inline int cpp_pdu2cpp_primitive_array_CameraInfo_r(const char* heap_ptr, Hako_CameraInfo &src, HakoCpp_CameraInfo &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 9; ++i) {
        hako_convert_pdu2cpp(src.r[i], dst.r[i]);
    }
    return 0;
}
static inline int cpp_pdu2cpp_primitive_array_CameraInfo_p(const char* heap_ptr, Hako_CameraInfo &src, HakoCpp_CameraInfo &dst)
{
    // Fixed size array convertor
    (void)heap_ptr;
    for (int i = 0; i < 12; ++i) {
        hako_convert_pdu2cpp(src.p[i], dst.p[i]);
    }
    return 0;
}

static inline int cpp_pdu2cpp_CameraInfo(const char* heap_ptr, Hako_CameraInfo &src, HakoCpp_CameraInfo &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // primitive convert
    hako_convert_pdu2cpp(src.height, dst.height);
    // primitive convert
    hako_convert_pdu2cpp(src.width, dst.width);
    // string convertor
    dst.distortion_model = (const char*)src.distortion_model;
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_CameraInfo_d(heap_ptr, src, dst);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_CameraInfo_k(heap_ptr, src, dst);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_CameraInfo_r(heap_ptr, src, dst);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_CameraInfo_p(heap_ptr, src, dst);
    // primitive convert
    hako_convert_pdu2cpp(src.binning_x, dst.binning_x);
    // primitive convert
    hako_convert_pdu2cpp(src.binning_y, dst.binning_y);
    // Struct convert
    cpp_pdu2cpp_RegionOfInterest(heap_ptr, src.roi, dst.roi);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_CameraInfo(Hako_CameraInfo &src, HakoCpp_CameraInfo &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_CameraInfo((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_CameraInfo_d(HakoCpp_CameraInfo &src, Hako_CameraInfo &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._d_len = src.d.size();
    if (dst._d_len > 0) {
        dst._d_off = dynamic_memory.reference(src.d.data(), dst._d_len, sizeof(Hako_float64));
    }
    else {
        dst._d_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool cpp_cpp2pdu_primitive_array_CameraInfo_k(HakoCpp_CameraInfo &src, Hako_CameraInfo &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 9
    (void)dynamic_memory;
    (void)hako_convert_cpp2pdu_array(
        src.k, src.k.size(),
        dst.k, M_ARRAY_SIZE(Hako_CameraInfo, Hako_float64, k));
    return true;
}
static inline bool cpp_cpp2pdu_primitive_array_CameraInfo_r(HakoCpp_CameraInfo &src, Hako_CameraInfo &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 9
    (void)dynamic_memory;
    (void)hako_convert_cpp2pdu_array(
        src.r, src.r.size(),
        dst.r, M_ARRAY_SIZE(Hako_CameraInfo, Hako_float64, r));
    return true;
}
static inline bool cpp_cpp2pdu_primitive_array_CameraInfo_p(HakoCpp_CameraInfo &src, Hako_CameraInfo &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy fixed array 12
    (void)dynamic_memory;
    (void)hako_convert_cpp2pdu_array(
        src.p, src.p.size(),
        dst.p, M_ARRAY_SIZE(Hako_CameraInfo, Hako_float64, p));
    return true;
}

static inline bool cpp_cpp2pdu_CameraInfo(HakoCpp_CameraInfo &src, Hako_CameraInfo &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory);
        // primitive convert
        hako_convert_cpp2pdu(src.height, dst.height);
        // primitive convert
        hako_convert_cpp2pdu(src.width, dst.width);
        // string convertor
        (void)hako_convert_cpp2pdu_array(
            src.distortion_model, src.distortion_model.length(),
            dst.distortion_model, M_ARRAY_SIZE(Hako_CameraInfo, char, distortion_model));
        dst.distortion_model[src.distortion_model.length()] = '\0';
        //primitive array copy
        cpp_cpp2pdu_primitive_array_CameraInfo_d(src, dst, dynamic_memory);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_CameraInfo_k(src, dst, dynamic_memory);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_CameraInfo_r(src, dst, dynamic_memory);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_CameraInfo_p(src, dst, dynamic_memory);
        // primitive convert
        hako_convert_cpp2pdu(src.binning_x, dst.binning_x);
        // primitive convert
        hako_convert_cpp2pdu(src.binning_y, dst.binning_y);
        // struct convert
        cpp_cpp2pdu_RegionOfInterest(src.roi, dst.roi, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_CameraInfo(HakoCpp_CameraInfo &src, Hako_CameraInfo** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_CameraInfo out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_CameraInfo(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_CameraInfo), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_CameraInfo));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_CameraInfo*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_CameraInfo* hako_create_empty_pdu_CameraInfo(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_CameraInfo), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_CameraInfo*)base_ptr;
}
namespace hako::pdu::msgs::sensor_msgs
{
class CameraInfo
{
public:
    CameraInfo() = default;
    ~CameraInfo() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_CameraInfo& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "CameraInfo" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_CameraInfo(*(Hako_CameraInfo*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "CameraInfo" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_CameraInfo() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_CameraInfo& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_CameraInfo out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_CameraInfo(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "CameraInfo" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        // Sizes in size_t, checked against the int-sized PDU fields and the buffer.
        const size_t meta_size = HAKO_PDU_META_DATA_SIZE();
        const size_t base_size = HAKO_ALIGN_SIZE(sizeof(Hako_CameraInfo), HAKO_ALIGNMENT_SIZE);
        const size_t heap_used = static_cast<size_t>(dynamic_memory.get_total_size());
        const size_t heap_size = HAKO_ALIGN_SIZE(heap_used, static_cast<size_t>(HAKO_ALIGNMENT_SIZE));
        const size_t pdu_size = meta_size + base_size + heap_size;
        if (heap_size < heap_used || pdu_size > static_cast<size_t>(std::numeric_limits<int>::max())) {
            std::cerr << "[ConvertorError][" << "CameraInfo" << "] PDU too large. heap=" << heap_used << std::endl;
            return -1;
        }
        // The whole buffer the caller gave must be clear of the message's arrays.
        if (pdu_buffer != nullptr && buffer_len > 0 &&
            dynamic_memory.references_overlap(pdu_buffer, static_cast<size_t>(buffer_len))) {
            std::cerr << "[ConvertorError][" << "CameraInfo" << "] pdu_buffer overlaps the message's arrays" << std::endl;
            return -1;
        }
        if (pdu_buffer == nullptr || buffer_len < 0 || pdu_size > static_cast<size_t>(buffer_len)) {
            std::cerr << "[ConvertorError][" << "CameraInfo" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        HakoPduMetaDataType meta;
        memset(&meta, 0, sizeof(meta));
        meta.magicno = HAKO_PDU_META_DATA_MAGICNO;
        meta.version = HAKO_PDU_META_DATA_VERSION;
        meta.base_off = static_cast<uint32_t>(meta_size);
        meta.heap_off = static_cast<uint32_t>(meta_size + base_size);
        meta.total_size = static_cast<uint32_t>(pdu_size);
        memset(pdu_buffer, 0, meta_size);
        memcpy(pdu_buffer, &meta, sizeof(meta));
        char* base_ptr = pdu_buffer + meta_size;
        memcpy(base_ptr, (const void*)&out, sizeof(Hako_CameraInfo));
        memset(base_ptr + sizeof(Hako_CameraInfo), 0, base_size - sizeof(Hako_CameraInfo));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return static_cast<int>(pdu_size);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_CameraInfo_HPP_ */
