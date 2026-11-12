#ifndef _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_JoyFeedbackArray_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_JoyFeedbackArray_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_JoyFeedbackArray.h"
/*
 * Dependent cpp pdu data
 */
#include "sensor_msgs/pdu_cpptype_JoyFeedbackArray.hpp"

/*
 * Dependent Convertors
 */
#include "sensor_msgs/pdu_cpptype_conv_JoyFeedback.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_struct_array_JoyFeedbackArray_array(const char* heap_ptr, Hako_JoyFeedbackArray &src, HakoCpp_JoyFeedbackArray &dst)
{
    // Convert using len and off
    int offset = src._array_off;
    int length = src._array_len;
    if (length > 0) {
        dst.array.resize(length);
        Hako_JoyFeedback *temp_struct_ptr = (Hako_JoyFeedback *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_JoyFeedback(heap_ptr, *temp_struct_ptr, dst.array[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int cpp_pdu2cpp_JoyFeedbackArray(const char* heap_ptr, Hako_JoyFeedbackArray &src, HakoCpp_JoyFeedbackArray &dst)
{
    // struct array convertor
    cpp_pdu2cpp_struct_array_JoyFeedbackArray_array(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_JoyFeedbackArray(Hako_JoyFeedbackArray &src, HakoCpp_JoyFeedbackArray &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_JoyFeedbackArray((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_struct_array_JoyFeedbackArray_array(HakoCpp_JoyFeedbackArray &src, Hako_JoyFeedbackArray &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._array_len = src.array.size();
    if (dst._array_len > 0) {
        Hako_JoyFeedback* temp_struct_ptr = (Hako_JoyFeedback*)dynamic_memory.allocate(dst._array_len, sizeof(Hako_JoyFeedback));
        dst._array_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._array_len; ++i) {
            cpp_cpp2pdu_JoyFeedback(src.array[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._array_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_JoyFeedbackArray(HakoCpp_JoyFeedbackArray &src, Hako_JoyFeedbackArray &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //struct array convert
        cpp_cpp2pdu_struct_array_JoyFeedbackArray_array(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_JoyFeedbackArray(HakoCpp_JoyFeedbackArray &src, Hako_JoyFeedbackArray** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_JoyFeedbackArray out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_JoyFeedbackArray(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_JoyFeedbackArray), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_JoyFeedbackArray));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_JoyFeedbackArray*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_JoyFeedbackArray* hako_create_empty_pdu_JoyFeedbackArray(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_JoyFeedbackArray), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_JoyFeedbackArray*)base_ptr;
}
namespace hako::pdu::msgs::sensor_msgs
{
class JoyFeedbackArray
{
public:
    JoyFeedbackArray() = default;
    ~JoyFeedbackArray() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_JoyFeedbackArray& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "JoyFeedbackArray" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_JoyFeedbackArray(*(Hako_JoyFeedbackArray*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "JoyFeedbackArray" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_JoyFeedbackArray() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_JoyFeedbackArray& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_JoyFeedbackArray out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_JoyFeedbackArray(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "JoyFeedbackArray" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        // Sizes in size_t, checked against the int-sized PDU fields and the buffer.
        const size_t meta_size = HAKO_PDU_META_DATA_SIZE();
        const size_t base_size = HAKO_ALIGN_SIZE(sizeof(Hako_JoyFeedbackArray), HAKO_ALIGNMENT_SIZE);
        const size_t heap_used = static_cast<size_t>(dynamic_memory.get_total_size());
        const size_t heap_size = HAKO_ALIGN_SIZE(heap_used, static_cast<size_t>(HAKO_ALIGNMENT_SIZE));
        const size_t pdu_size = meta_size + base_size + heap_size;
        if (heap_size < heap_used || pdu_size > static_cast<size_t>(std::numeric_limits<int>::max())) {
            std::cerr << "[ConvertorError][" << "JoyFeedbackArray" << "] PDU too large. heap=" << heap_used << std::endl;
            return -1;
        }
        if (pdu_buffer == nullptr || buffer_len < 0 || pdu_size > static_cast<size_t>(buffer_len)) {
            std::cerr << "[ConvertorError][" << "JoyFeedbackArray" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        if (dynamic_memory.references_overlap(pdu_buffer, pdu_size)) {
            std::cerr << "[ConvertorError][" << "JoyFeedbackArray" << "] pdu_buffer overlaps the message's arrays" << std::endl;
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
        memcpy(base_ptr, (const void*)&out, sizeof(Hako_JoyFeedbackArray));
        memset(base_ptr + sizeof(Hako_JoyFeedbackArray), 0, base_size - sizeof(Hako_JoyFeedbackArray));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return static_cast<int>(pdu_size);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_JoyFeedbackArray_HPP_ */
