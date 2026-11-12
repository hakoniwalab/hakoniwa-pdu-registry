#ifndef _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_CompressedImage_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_CompressedImage_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_CompressedImage.h"
/*
 * Dependent cpp pdu data
 */
#include "sensor_msgs/pdu_cpptype_CompressedImage.hpp"

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
static inline int cpp_pdu2cpp_primitive_array_CompressedImage_data(const char* heap_ptr, Hako_CompressedImage &src, HakoCpp_CompressedImage &dst)
{
    // Convert using len and off
    int offset = src._data_off;
    int length = src._data_len;
    if (length > 0) {
        dst.data.resize(length);
        memcpy(dst.data.data(), heap_ptr + offset, length * sizeof(Hako_uint8));
    }
    else {
        dst.data.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}

static inline int cpp_pdu2cpp_CompressedImage(const char* heap_ptr, Hako_CompressedImage &src, HakoCpp_CompressedImage &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // string convertor
    dst.format = hako_convert_string_from_pdu(src.format, M_SIZE(Hako_CompressedImage, format));
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_CompressedImage_data(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_CompressedImage(Hako_CompressedImage &src, HakoCpp_CompressedImage &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_CompressedImage((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_CompressedImage_data(HakoCpp_CompressedImage &src, Hako_CompressedImage &dst, PduDynamicMemory &dynamic_memory)
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

static inline bool cpp_cpp2pdu_CompressedImage(HakoCpp_CompressedImage &src, Hako_CompressedImage &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory)) {
            return false;
        }
        // string convertor
        hako_convert_string_to_pdu(src.format, dst.format, M_SIZE(Hako_CompressedImage, format));
        //primitive array copy
        if (!cpp_cpp2pdu_primitive_array_CompressedImage_data(src, dst, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_CompressedImage(HakoCpp_CompressedImage &src, Hako_CompressedImage** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_CompressedImage out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_CompressedImage(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_CompressedImage), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_CompressedImage));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_CompressedImage*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_CompressedImage* hako_create_empty_pdu_CompressedImage(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_CompressedImage), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_CompressedImage*)base_ptr;
}
namespace hako::pdu::msgs::sensor_msgs
{
class CompressedImage
{
public:
    CompressedImage() = default;
    ~CompressedImage() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_CompressedImage& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "CompressedImage" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_CompressedImage(*(Hako_CompressedImage*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "CompressedImage" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_CompressedImage() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_CompressedImage& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_CompressedImage out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_CompressedImage(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "CompressedImage" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        return hako_pdu_build_into("CompressedImage", &out, sizeof(out), dynamic_memory, pdu_buffer, buffer_len);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_CompressedImage_HPP_ */
