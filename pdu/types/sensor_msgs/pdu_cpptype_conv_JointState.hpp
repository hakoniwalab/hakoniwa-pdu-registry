#ifndef _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_JointState_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_JointState_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_JointState.h"
/*
 * Dependent cpp pdu data
 */
#include "sensor_msgs/pdu_cpptype_JointState.hpp"

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
static inline int cpp_pdu2cpp_string_array_JointState_name(const char* heap_ptr, Hako_JointState &src, HakoCpp_JointState &dst)
{
    // Convert using len and off
    int offset = src._name_off;
    int length = src._name_len;
    if (length > 0) {
        Hako_cstring *temp_struct_ptr = (Hako_cstring *)(heap_ptr + offset);
        hako_convert_pdu2cpp_array_string_varray(temp_struct_ptr, dst.name, length);
    }
    else {
        dst.name.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}
static inline int cpp_pdu2cpp_primitive_array_JointState_position(const char* heap_ptr, Hako_JointState &src, HakoCpp_JointState &dst)
{
    // Convert using len and off
    int offset = src._position_off;
    int length = src._position_len;
    if (length > 0) {
        dst.position.resize(length);
        memcpy(dst.position.data(), heap_ptr + offset, length * sizeof(Hako_float64));
    }
    else {
        dst.position.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}
static inline int cpp_pdu2cpp_primitive_array_JointState_velocity(const char* heap_ptr, Hako_JointState &src, HakoCpp_JointState &dst)
{
    // Convert using len and off
    int offset = src._velocity_off;
    int length = src._velocity_len;
    if (length > 0) {
        dst.velocity.resize(length);
        memcpy(dst.velocity.data(), heap_ptr + offset, length * sizeof(Hako_float64));
    }
    else {
        dst.velocity.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}
static inline int cpp_pdu2cpp_primitive_array_JointState_effort(const char* heap_ptr, Hako_JointState &src, HakoCpp_JointState &dst)
{
    // Convert using len and off
    int offset = src._effort_off;
    int length = src._effort_len;
    if (length > 0) {
        dst.effort.resize(length);
        memcpy(dst.effort.data(), heap_ptr + offset, length * sizeof(Hako_float64));
    }
    else {
        dst.effort.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}

static inline int cpp_pdu2cpp_JointState(const char* heap_ptr, Hako_JointState &src, HakoCpp_JointState &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // string array convertor
    cpp_pdu2cpp_string_array_JointState_name(heap_ptr, src, dst);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_JointState_position(heap_ptr, src, dst);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_JointState_velocity(heap_ptr, src, dst);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_JointState_effort(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_JointState(Hako_JointState &src, HakoCpp_JointState &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_JointState((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_string_array_JointState_name(HakoCpp_JointState &src, Hako_JointState &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray string
    dst._name_len = src.name.size();
    if (dst._name_len > 0) {
        Hako_cstring* temp_ptr = (Hako_cstring*)dynamic_memory.allocate(dst._name_len, sizeof(Hako_cstring));
        (void)hako_convert_cpp2pdu_array_string_varray(src.name, temp_ptr);
        dst._name_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._name_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool cpp_cpp2pdu_primitive_array_JointState_position(HakoCpp_JointState &src, Hako_JointState &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._position_len = src.position.size();
    if (dst._position_len > 0) {
        dst._position_off = dynamic_memory.reference(src.position.data(), dst._position_len, sizeof(Hako_float64));
    }
    else {
        dst._position_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool cpp_cpp2pdu_primitive_array_JointState_velocity(HakoCpp_JointState &src, Hako_JointState &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._velocity_len = src.velocity.size();
    if (dst._velocity_len > 0) {
        dst._velocity_off = dynamic_memory.reference(src.velocity.data(), dst._velocity_len, sizeof(Hako_float64));
    }
    else {
        dst._velocity_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool cpp_cpp2pdu_primitive_array_JointState_effort(HakoCpp_JointState &src, Hako_JointState &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._effort_len = src.effort.size();
    if (dst._effort_len > 0) {
        dst._effort_off = dynamic_memory.reference(src.effort.data(), dst._effort_len, sizeof(Hako_float64));
    }
    else {
        dst._effort_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_JointState(HakoCpp_JointState &src, Hako_JointState &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory);
        // string array convert
        cpp_cpp2pdu_string_array_JointState_name(src, dst, dynamic_memory);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_JointState_position(src, dst, dynamic_memory);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_JointState_velocity(src, dst, dynamic_memory);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_JointState_effort(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_JointState(HakoCpp_JointState &src, Hako_JointState** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_JointState out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_JointState(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_JointState), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_JointState));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_JointState*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_JointState* hako_create_empty_pdu_JointState(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_JointState), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_JointState*)base_ptr;
}
namespace hako::pdu::msgs::sensor_msgs
{
class JointState
{
public:
    JointState() = default;
    ~JointState() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_JointState& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "JointState" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_JointState(*(Hako_JointState*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "JointState" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_JointState() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_JointState& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_JointState out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_JointState(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "JointState" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        // Sizes in size_t, checked against the int-sized PDU fields and the buffer.
        const size_t meta_size = HAKO_PDU_META_DATA_SIZE();
        const size_t base_size = HAKO_ALIGN_SIZE(sizeof(Hako_JointState), HAKO_ALIGNMENT_SIZE);
        const size_t heap_used = static_cast<size_t>(dynamic_memory.get_total_size());
        const size_t heap_size = HAKO_ALIGN_SIZE(heap_used, static_cast<size_t>(HAKO_ALIGNMENT_SIZE));
        const size_t pdu_size = meta_size + base_size + heap_size;
        if (heap_size < heap_used || pdu_size > static_cast<size_t>(std::numeric_limits<int>::max())) {
            std::cerr << "[ConvertorError][" << "JointState" << "] PDU too large. heap=" << heap_used << std::endl;
            return -1;
        }
        if (pdu_buffer == nullptr || buffer_len < 0 || pdu_size > static_cast<size_t>(buffer_len)) {
            std::cerr << "[ConvertorError][" << "JointState" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        if (dynamic_memory.references_overlap(pdu_buffer, pdu_size)) {
            std::cerr << "[ConvertorError][" << "JointState" << "] pdu_buffer overlaps the message's arrays" << std::endl;
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
        memcpy(base_ptr, (const void*)&out, sizeof(Hako_JointState));
        memset(base_ptr + sizeof(Hako_JointState), 0, base_size - sizeof(Hako_JointState));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return static_cast<int>(pdu_size);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_JointState_HPP_ */
