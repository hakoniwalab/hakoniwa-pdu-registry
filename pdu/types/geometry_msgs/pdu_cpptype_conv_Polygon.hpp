#ifndef _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_Polygon_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_Polygon_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "geometry_msgs/pdu_ctype_Polygon.h"
/*
 * Dependent cpp pdu data
 */
#include "geometry_msgs/pdu_cpptype_Polygon.hpp"

/*
 * Dependent Convertors
 */
#include "geometry_msgs/pdu_cpptype_conv_Point32.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_struct_array_Polygon_points(const char* heap_ptr, Hako_Polygon &src, HakoCpp_Polygon &dst)
{
    // Convert using len and off
    int offset = src._points_off;
    int length = src._points_len;
    if (length > 0) {
        dst.points.resize(length);
        Hako_Point32 *temp_struct_ptr = (Hako_Point32 *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_Point32(heap_ptr, *temp_struct_ptr, dst.points[i]);
            temp_struct_ptr++;
        }
    }
    else {
        dst.points.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}

static inline int cpp_pdu2cpp_Polygon(const char* heap_ptr, Hako_Polygon &src, HakoCpp_Polygon &dst)
{
    // struct array convertor
    cpp_pdu2cpp_struct_array_Polygon_points(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_Polygon(Hako_Polygon &src, HakoCpp_Polygon &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_Polygon((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_struct_array_Polygon_points(HakoCpp_Polygon &src, Hako_Polygon &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._points_len = src.points.size();
    if (dst._points_len > 0) {
        Hako_Point32* temp_struct_ptr = (Hako_Point32*)dynamic_memory.allocate(dst._points_len, sizeof(Hako_Point32));
        dst._points_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._points_len; ++i) {
            cpp_cpp2pdu_Point32(src.points[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._points_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_Polygon(HakoCpp_Polygon &src, Hako_Polygon &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //struct array convert
        cpp_cpp2pdu_struct_array_Polygon_points(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_Polygon(HakoCpp_Polygon &src, Hako_Polygon** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Polygon out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_Polygon(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Polygon), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Polygon));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Polygon*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Polygon* hako_create_empty_pdu_Polygon(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Polygon), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Polygon*)base_ptr;
}
namespace hako::pdu::msgs::geometry_msgs
{
class Polygon
{
public:
    Polygon() = default;
    ~Polygon() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_Polygon& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "Polygon" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_Polygon(*(Hako_Polygon*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "Polygon" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_Polygon() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_Polygon& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_Polygon out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_Polygon(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "Polygon" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        // Sizes in size_t, checked against the int-sized PDU fields and the buffer.
        const size_t meta_size = HAKO_PDU_META_DATA_SIZE();
        const size_t base_size = HAKO_ALIGN_SIZE(sizeof(Hako_Polygon), HAKO_ALIGNMENT_SIZE);
        const size_t heap_used = static_cast<size_t>(dynamic_memory.get_total_size());
        const size_t heap_size = HAKO_ALIGN_SIZE(heap_used, static_cast<size_t>(HAKO_ALIGNMENT_SIZE));
        const size_t pdu_size = meta_size + base_size + heap_size;
        if (heap_size < heap_used || pdu_size > static_cast<size_t>(std::numeric_limits<int>::max())) {
            std::cerr << "[ConvertorError][" << "Polygon" << "] PDU too large. heap=" << heap_used << std::endl;
            return -1;
        }
        if (pdu_buffer == nullptr || buffer_len < 0 || pdu_size > static_cast<size_t>(buffer_len)) {
            std::cerr << "[ConvertorError][" << "Polygon" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        if (dynamic_memory.references_overlap(pdu_buffer, pdu_size)) {
            std::cerr << "[ConvertorError][" << "Polygon" << "] pdu_buffer overlaps the message's arrays" << std::endl;
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
        memcpy(base_ptr, (const void*)&out, sizeof(Hako_Polygon));
        memset(base_ptr + sizeof(Hako_Polygon), 0, base_size - sizeof(Hako_Polygon));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return static_cast<int>(pdu_size);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_geometry_msgs_Polygon_HPP_ */
