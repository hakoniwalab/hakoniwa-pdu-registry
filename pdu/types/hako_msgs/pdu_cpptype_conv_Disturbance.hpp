#ifndef _PDU_CPPTYPE_CONV_HAKO_hako_msgs_Disturbance_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_hako_msgs_Disturbance_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_Disturbance.h"
/*
 * Dependent cpp pdu data
 */
#include "hako_msgs/pdu_cpptype_Disturbance.hpp"

/*
 * Dependent Convertors
 */
#include "geometry_msgs/pdu_cpptype_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Vector3.hpp"
#include "hako_msgs/pdu_cpptype_conv_DisturbanceAtm.hpp"
#include "hako_msgs/pdu_cpptype_conv_DisturbanceBoundary.hpp"
#include "hako_msgs/pdu_cpptype_conv_DisturbanceTemperature.hpp"
#include "hako_msgs/pdu_cpptype_conv_DisturbanceUserCustom.hpp"
#include "hako_msgs/pdu_cpptype_conv_DisturbanceWind.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_struct_array_Disturbance_d_user_custom(const char* heap_ptr, Hako_Disturbance &src, HakoCpp_Disturbance &dst)
{
    // Convert using len and off
    int offset = src._d_user_custom_off;
    int length = src._d_user_custom_len;
    if (length > 0) {
        dst.d_user_custom.resize(length);
        Hako_DisturbanceUserCustom *temp_struct_ptr = (Hako_DisturbanceUserCustom *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_DisturbanceUserCustom(heap_ptr, *temp_struct_ptr, dst.d_user_custom[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int cpp_pdu2cpp_Disturbance(const char* heap_ptr, Hako_Disturbance &src, HakoCpp_Disturbance &dst)
{
    // Struct convert
    cpp_pdu2cpp_DisturbanceTemperature(heap_ptr, src.d_temp, dst.d_temp);
    // Struct convert
    cpp_pdu2cpp_DisturbanceWind(heap_ptr, src.d_wind, dst.d_wind);
    // Struct convert
    cpp_pdu2cpp_DisturbanceAtm(heap_ptr, src.d_atm, dst.d_atm);
    // Struct convert
    cpp_pdu2cpp_DisturbanceBoundary(heap_ptr, src.d_boundary, dst.d_boundary);
    // struct array convertor
    cpp_pdu2cpp_struct_array_Disturbance_d_user_custom(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_Disturbance(Hako_Disturbance &src, HakoCpp_Disturbance &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_Disturbance((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_struct_array_Disturbance_d_user_custom(HakoCpp_Disturbance &src, Hako_Disturbance &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._d_user_custom_len = src.d_user_custom.size();
    if (dst._d_user_custom_len > 0) {
        Hako_DisturbanceUserCustom* temp_struct_ptr = (Hako_DisturbanceUserCustom*)dynamic_memory.allocate(dst._d_user_custom_len, sizeof(Hako_DisturbanceUserCustom));
        dst._d_user_custom_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._d_user_custom_len; ++i) {
            cpp_cpp2pdu_DisturbanceUserCustom(src.d_user_custom[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._d_user_custom_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_Disturbance(HakoCpp_Disturbance &src, Hako_Disturbance &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_DisturbanceTemperature(src.d_temp, dst.d_temp, dynamic_memory);
        // struct convert
        cpp_cpp2pdu_DisturbanceWind(src.d_wind, dst.d_wind, dynamic_memory);
        // struct convert
        cpp_cpp2pdu_DisturbanceAtm(src.d_atm, dst.d_atm, dynamic_memory);
        // struct convert
        cpp_cpp2pdu_DisturbanceBoundary(src.d_boundary, dst.d_boundary, dynamic_memory);
        //struct array convert
        cpp_cpp2pdu_struct_array_Disturbance_d_user_custom(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_Disturbance(HakoCpp_Disturbance &src, Hako_Disturbance** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_Disturbance out{};  // zeroed: no stray bytes in the padding
    if (!cpp_cpp2pdu_Disturbance(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_Disturbance), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_Disturbance));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_Disturbance*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_Disturbance* hako_create_empty_pdu_Disturbance(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_Disturbance), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_Disturbance*)base_ptr;
}
namespace hako::pdu::msgs::hako_msgs
{
class Disturbance
{
public:
    Disturbance() = default;
    ~Disturbance() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_Disturbance& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "Disturbance" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_Disturbance(*(Hako_Disturbance*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "Disturbance" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    // Builds the PDU straight into pdu_buffer, byte for byte as
    // hako_convert_cpp2pdu_Disturbance() lays it out (metadata, base, heap), without
    // an intermediate PDU: each array of the message is copied once.
    // pdu_buffer needs no alignment. It must not overlap cppData's arrays (they
    // are read while the PDU is written): an overlap is refused.
    int cpp2pdu(HakoCpp_Disturbance& cppData, char* pdu_buffer, int buffer_len)
    {
        PduDynamicMemory dynamic_memory;
        Hako_Disturbance out{};  // zeroed: no stray bytes in the padding
        if (!cpp_cpp2pdu_Disturbance(cppData, out, dynamic_memory)) {
            std::cerr << "[ConvertorError][" << "Disturbance" << "] hako_convert_cpp2pdu returned error code: " << -1 << std::endl;
            return -1;
        }
        // Sizes in size_t, checked against the int-sized PDU fields and the buffer.
        const size_t meta_size = HAKO_PDU_META_DATA_SIZE();
        const size_t base_size = HAKO_ALIGN_SIZE(sizeof(Hako_Disturbance), HAKO_ALIGNMENT_SIZE);
        const size_t heap_used = static_cast<size_t>(dynamic_memory.get_total_size());
        const size_t heap_size = HAKO_ALIGN_SIZE(heap_used, static_cast<size_t>(HAKO_ALIGNMENT_SIZE));
        const size_t pdu_size = meta_size + base_size + heap_size;
        if (heap_size < heap_used || pdu_size > static_cast<size_t>(std::numeric_limits<int>::max())) {
            std::cerr << "[ConvertorError][" << "Disturbance" << "] PDU too large. heap=" << heap_used << std::endl;
            return -1;
        }
        if (pdu_buffer == nullptr || buffer_len < 0 || pdu_size > static_cast<size_t>(buffer_len)) {
            std::cerr << "[ConvertorError][" << "Disturbance" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        if (dynamic_memory.references_overlap(pdu_buffer, pdu_size)) {
            std::cerr << "[ConvertorError][" << "Disturbance" << "] pdu_buffer overlaps the message's arrays" << std::endl;
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
        memcpy(base_ptr, (const void*)&out, sizeof(Hako_Disturbance));
        memset(base_ptr + sizeof(Hako_Disturbance), 0, base_size - sizeof(Hako_Disturbance));
        char* heap_ptr = base_ptr + base_size;
        dynamic_memory.copy_to_pdu(heap_ptr);
        memset(heap_ptr + heap_used, 0, heap_size - heap_used);
        return static_cast<int>(pdu_size);
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_hako_msgs_Disturbance_HPP_ */
