#ifndef _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_Image_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_Image_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_Image.h"
/*
 * Dependent cpp pdu data
 */
#include "sensor_msgs/pdu_cpptype_Image.hpp"

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
static inline int cpp_pdu2cpp_primitive_array_Image_data(const char* heap_ptr, Hako_Image &src, HakoCpp_Image &dst)
{
    // Convert using len and off
    int offset = src._data_off;
    int length = src._data_len;
    if (length > 0) {
        dst.data.resize(length);
        memcpy(dst.data.data(), heap_ptr + offset, length * sizeof(Hako_uint8));
    }
    return 0;
}

static inline int cpp_pdu2cpp_Image(const char* heap_ptr, Hako_Image &src, HakoCpp_Image &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // primitive convert
    hako_convert_pdu2cpp(src.height, dst.height);
    // primitive convert
    hako_convert_pdu2cpp(src.width, dst.width);
    // string convertor
    dst.encoding = (const char*)src.encoding;
    // primitive convert
    hako_convert_pdu2cpp(src.is_bigendian, dst.is_bigendian);
    // primitive convert
    hako_convert_pdu2cpp(src.step, dst.step);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_Image_data(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_Image(Hako_Image &src, HakoCpp_Image &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_Image((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_Image_data(HakoCpp_Image &src, Hako_Image &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._data_len = src.data.size();
    if (dst._data_len > 0) {
        dst._data_off = dynamic_memory.reference(src.data.data(), dst._data_len, sizeof(Hako_uint8));
    }
    else {
        dst._data_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_Image(HakoCpp_Image &src, Hako_Image &dst, PduDynamicMemory &dynamic_memory)
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
            src.encoding, src.encoding.length(),
            dst.encoding, M_ARRAY_SIZE(Hako_Image, char, encoding));
        dst.encoding[src.encoding.length()] = '\0';
        // primitive convert
        hako_convert_cpp2pdu(src.is_bigendian, dst.is_bigendian);
        // primitive convert
        hako_convert_cpp2pdu(src.step, dst.step);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_Image_data(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_Image(HakoCpp_Image &src, Hako_Image** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Image out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_Image(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Image), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Image));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Image*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Image* hako_create_empty_pdu_Image(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Image), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Image*)base_ptr;
}
namespace hako::pdu::msgs::sensor_msgs
{
class Image
{
public:
    Image() = default;
    ~Image() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_Image& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "Image" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_Image(*(Hako_Image*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "Image" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_Image() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_Image& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_Image out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_Image(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "Image" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        // Sizes in size_t, checked against the int-sized PDU fields and the buffer.
        const size_t meta_size = HAKO_PDU_META_DATA_SIZE();
        const size_t base_size = HAKO_ALIGN_SIZE(sizeof(Hako_Image), HAKO_ALIGNMENT_SIZE);
        const size_t heap_used = static_cast<size_t>(dynamic_memory.get_total_size());
        const size_t heap_size = HAKO_ALIGN_SIZE(heap_used, static_cast<size_t>(HAKO_ALIGNMENT_SIZE));
        const size_t pdu_size = meta_size + base_size + heap_size;
        if (heap_size < heap_used || pdu_size > static_cast<size_t>(std::numeric_limits<int>::max())) {
            std::cerr << "[ConvertorError][" << "Image" << "] PDU too large. heap=" << heap_used << std::endl;
            return -1;
        }
        if (pdu_buffer == nullptr || buffer_len < 0 || pdu_size > static_cast<size_t>(buffer_len)) {
            std::cerr << "[ConvertorError][" << "Image" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        if (dynamic_memory.references_overlap(pdu_buffer, pdu_size)) {
            std::cerr << "[ConvertorError][" << "Image" << "] pdu_buffer overlaps the message's arrays" << std::endl;
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
        memcpy(base_ptr, (const void*)&out, sizeof(Hako_Image));
        memset(base_ptr + sizeof(Hako_Image), 0, base_size - sizeof(Hako_Image));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return static_cast<int>(pdu_size);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_Image_HPP_ */
