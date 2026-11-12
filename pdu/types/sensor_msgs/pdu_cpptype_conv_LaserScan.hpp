#ifndef _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_LaserScan_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_LaserScan_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_LaserScan.h"
/*
 * Dependent cpp pdu data
 */
#include "sensor_msgs/pdu_cpptype_LaserScan.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_LaserScan_ranges(const char* heap_ptr, Hako_LaserScan &src, HakoCpp_LaserScan &dst)
{
    // Convert using len and off
    int offset = src._ranges_off;
    int length = src._ranges_len;
    if (length > 0) {
        dst.ranges.resize(length);
        memcpy(dst.ranges.data(), heap_ptr + offset, length * sizeof(Hako_float32));
    }
    return 0;
}
static inline int cpp_pdu2cpp_primitive_array_LaserScan_intensities(const char* heap_ptr, Hako_LaserScan &src, HakoCpp_LaserScan &dst)
{
    // Convert using len and off
    int offset = src._intensities_off;
    int length = src._intensities_len;
    if (length > 0) {
        dst.intensities.resize(length);
        memcpy(dst.intensities.data(), heap_ptr + offset, length * sizeof(Hako_float32));
    }
    return 0;
}

static inline int cpp_pdu2cpp_LaserScan(const char* heap_ptr, Hako_LaserScan &src, HakoCpp_LaserScan &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // primitive convert
    hako_convert_pdu2cpp(src.angle_min, dst.angle_min);
    // primitive convert
    hako_convert_pdu2cpp(src.angle_max, dst.angle_max);
    // primitive convert
    hako_convert_pdu2cpp(src.angle_increment, dst.angle_increment);
    // primitive convert
    hako_convert_pdu2cpp(src.time_increment, dst.time_increment);
    // primitive convert
    hako_convert_pdu2cpp(src.scan_time, dst.scan_time);
    // primitive convert
    hako_convert_pdu2cpp(src.range_min, dst.range_min);
    // primitive convert
    hako_convert_pdu2cpp(src.range_max, dst.range_max);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_LaserScan_ranges(heap_ptr, src, dst);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_LaserScan_intensities(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_LaserScan(Hako_LaserScan &src, HakoCpp_LaserScan &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_LaserScan((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_LaserScan_ranges(HakoCpp_LaserScan &src, Hako_LaserScan &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._ranges_len = src.ranges.size();
    if (dst._ranges_len > 0) {
        dst._ranges_off = dynamic_memory.reference(src.ranges.data(), dst._ranges_len, sizeof(Hako_float32));
    }
    else {
        dst._ranges_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool cpp_cpp2pdu_primitive_array_LaserScan_intensities(HakoCpp_LaserScan &src, Hako_LaserScan &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._intensities_len = src.intensities.size();
    if (dst._intensities_len > 0) {
        dst._intensities_off = dynamic_memory.reference(src.intensities.data(), dst._intensities_len, sizeof(Hako_float32));
    }
    else {
        dst._intensities_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_LaserScan(HakoCpp_LaserScan &src, Hako_LaserScan &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory);
        // primitive convert
        hako_convert_cpp2pdu(src.angle_min, dst.angle_min);
        // primitive convert
        hako_convert_cpp2pdu(src.angle_max, dst.angle_max);
        // primitive convert
        hako_convert_cpp2pdu(src.angle_increment, dst.angle_increment);
        // primitive convert
        hako_convert_cpp2pdu(src.time_increment, dst.time_increment);
        // primitive convert
        hako_convert_cpp2pdu(src.scan_time, dst.scan_time);
        // primitive convert
        hako_convert_cpp2pdu(src.range_min, dst.range_min);
        // primitive convert
        hako_convert_cpp2pdu(src.range_max, dst.range_max);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_LaserScan_ranges(src, dst, dynamic_memory);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_LaserScan_intensities(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_LaserScan(HakoCpp_LaserScan &src, Hako_LaserScan** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_LaserScan out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_LaserScan(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_LaserScan), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_LaserScan));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_LaserScan*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_LaserScan* hako_create_empty_pdu_LaserScan(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_LaserScan), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_LaserScan*)base_ptr;
}
namespace hako::pdu::msgs::sensor_msgs
{
class LaserScan
{
public:
    LaserScan() = default;
    ~LaserScan() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_LaserScan& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "LaserScan" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_LaserScan(*(Hako_LaserScan*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "LaserScan" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_LaserScan() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_LaserScan& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_LaserScan out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_LaserScan(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "LaserScan" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        // Sizes in size_t, checked against the int-sized PDU fields and the buffer.
        const size_t meta_size = HAKO_PDU_META_DATA_SIZE();
        const size_t base_size = HAKO_ALIGN_SIZE(sizeof(Hako_LaserScan), HAKO_ALIGNMENT_SIZE);
        const size_t heap_used = static_cast<size_t>(dynamic_memory.get_total_size());
        const size_t heap_size = HAKO_ALIGN_SIZE(heap_used, static_cast<size_t>(HAKO_ALIGNMENT_SIZE));
        const size_t pdu_size = meta_size + base_size + heap_size;
        if (heap_size < heap_used || pdu_size > static_cast<size_t>(std::numeric_limits<int>::max())) {
            std::cerr << "[ConvertorError][" << "LaserScan" << "] PDU too large. heap=" << heap_used << std::endl;
            return -1;
        }
        if (pdu_buffer == nullptr || buffer_len < 0 || pdu_size > static_cast<size_t>(buffer_len)) {
            std::cerr << "[ConvertorError][" << "LaserScan" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        if (dynamic_memory.references_overlap(pdu_buffer, pdu_size)) {
            std::cerr << "[ConvertorError][" << "LaserScan" << "] pdu_buffer overlaps the message's arrays" << std::endl;
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
        memcpy(base_ptr, (const void*)&out, sizeof(Hako_LaserScan));
        memset(base_ptr + sizeof(Hako_LaserScan), 0, base_size - sizeof(Hako_LaserScan));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return static_cast<int>(pdu_size);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_LaserScan_HPP_ */
