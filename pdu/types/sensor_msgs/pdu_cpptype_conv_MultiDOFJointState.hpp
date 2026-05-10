#ifndef _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_MultiDOFJointState_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_MultiDOFJointState_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_MultiDOFJointState.h"
/*
 * Dependent cpp pdu data
 */
#include "sensor_msgs/pdu_cpptype_MultiDOFJointState.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Transform.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Vector3.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Wrench.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_string_array_MultiDOFJointState_joint_names(const char* heap_ptr, Hako_MultiDOFJointState &src, HakoCpp_MultiDOFJointState &dst)
{
    // Convert using len and off
    int offset = src._joint_names_off;
    int length = src._joint_names_len;
    if (length > 0) {
        Hako_cstring *temp_struct_ptr = (Hako_cstring *)(heap_ptr + offset);
        hako_convert_pdu2cpp_array_string_varray(temp_struct_ptr, dst.joint_names, length);
    }
    return 0;
}
static inline int cpp_pdu2cpp_struct_array_MultiDOFJointState_transforms(const char* heap_ptr, Hako_MultiDOFJointState &src, HakoCpp_MultiDOFJointState &dst)
{
    // Convert using len and off
    int offset = src._transforms_off;
    int length = src._transforms_len;
    if (length > 0) {
        dst.transforms.resize(length);
        Hako_Transform *temp_struct_ptr = (Hako_Transform *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_Transform(heap_ptr, *temp_struct_ptr, dst.transforms[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}
static inline int cpp_pdu2cpp_struct_array_MultiDOFJointState_twist(const char* heap_ptr, Hako_MultiDOFJointState &src, HakoCpp_MultiDOFJointState &dst)
{
    // Convert using len and off
    int offset = src._twist_off;
    int length = src._twist_len;
    if (length > 0) {
        dst.twist.resize(length);
        Hako_Twist *temp_struct_ptr = (Hako_Twist *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_Twist(heap_ptr, *temp_struct_ptr, dst.twist[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}
static inline int cpp_pdu2cpp_struct_array_MultiDOFJointState_wrench(const char* heap_ptr, Hako_MultiDOFJointState &src, HakoCpp_MultiDOFJointState &dst)
{
    // Convert using len and off
    int offset = src._wrench_off;
    int length = src._wrench_len;
    if (length > 0) {
        dst.wrench.resize(length);
        Hako_Wrench *temp_struct_ptr = (Hako_Wrench *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_Wrench(heap_ptr, *temp_struct_ptr, dst.wrench[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int cpp_pdu2cpp_MultiDOFJointState(const char* heap_ptr, Hako_MultiDOFJointState &src, HakoCpp_MultiDOFJointState &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // string array convertor
    cpp_pdu2cpp_string_array_MultiDOFJointState_joint_names(heap_ptr, src, dst);
    // struct array convertor
    cpp_pdu2cpp_struct_array_MultiDOFJointState_transforms(heap_ptr, src, dst);
    // struct array convertor
    cpp_pdu2cpp_struct_array_MultiDOFJointState_twist(heap_ptr, src, dst);
    // struct array convertor
    cpp_pdu2cpp_struct_array_MultiDOFJointState_wrench(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_MultiDOFJointState(Hako_MultiDOFJointState &src, HakoCpp_MultiDOFJointState &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_MultiDOFJointState((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_string_array_MultiDOFJointState_joint_names(HakoCpp_MultiDOFJointState &src, Hako_MultiDOFJointState &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray string
    dst._joint_names_len = src.joint_names.size();
    if (dst._joint_names_len > 0) {
        Hako_cstring* temp_ptr = (Hako_cstring*)dynamic_memory.allocate(dst._joint_names_len, sizeof(Hako_cstring));
        (void)hako_convert_cpp2pdu_array_string_varray(src.joint_names, temp_ptr);
        dst._joint_names_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._joint_names_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool cpp_cpp2pdu_struct_array_MultiDOFJointState_transforms(HakoCpp_MultiDOFJointState &src, Hako_MultiDOFJointState &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._transforms_len = src.transforms.size();
    if (dst._transforms_len > 0) {
        Hako_Transform* temp_struct_ptr = (Hako_Transform*)dynamic_memory.allocate(dst._transforms_len, sizeof(Hako_Transform));
        dst._transforms_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._transforms_len; ++i) {
            cpp_cpp2pdu_Transform(src.transforms[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._transforms_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool cpp_cpp2pdu_struct_array_MultiDOFJointState_twist(HakoCpp_MultiDOFJointState &src, Hako_MultiDOFJointState &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._twist_len = src.twist.size();
    if (dst._twist_len > 0) {
        Hako_Twist* temp_struct_ptr = (Hako_Twist*)dynamic_memory.allocate(dst._twist_len, sizeof(Hako_Twist));
        dst._twist_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._twist_len; ++i) {
            cpp_cpp2pdu_Twist(src.twist[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._twist_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool cpp_cpp2pdu_struct_array_MultiDOFJointState_wrench(HakoCpp_MultiDOFJointState &src, Hako_MultiDOFJointState &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._wrench_len = src.wrench.size();
    if (dst._wrench_len > 0) {
        Hako_Wrench* temp_struct_ptr = (Hako_Wrench*)dynamic_memory.allocate(dst._wrench_len, sizeof(Hako_Wrench));
        dst._wrench_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._wrench_len; ++i) {
            cpp_cpp2pdu_Wrench(src.wrench[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._wrench_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_MultiDOFJointState(HakoCpp_MultiDOFJointState &src, Hako_MultiDOFJointState &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory);
        // string array convert
        cpp_cpp2pdu_string_array_MultiDOFJointState_joint_names(src, dst, dynamic_memory);
        //struct array convert
        cpp_cpp2pdu_struct_array_MultiDOFJointState_transforms(src, dst, dynamic_memory);
        //struct array convert
        cpp_cpp2pdu_struct_array_MultiDOFJointState_twist(src, dst, dynamic_memory);
        //struct array convert
        cpp_cpp2pdu_struct_array_MultiDOFJointState_wrench(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_MultiDOFJointState(HakoCpp_MultiDOFJointState &src, Hako_MultiDOFJointState** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_MultiDOFJointState out;
    if (!cpp_cpp2pdu_MultiDOFJointState(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_MultiDOFJointState), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_MultiDOFJointState));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_MultiDOFJointState*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_MultiDOFJointState* hako_create_empty_pdu_MultiDOFJointState(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_MultiDOFJointState), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_MultiDOFJointState*)base_ptr;
}
namespace hako::pdu::msgs::sensor_msgs
{
class MultiDOFJointState
{
public:
    MultiDOFJointState() = default;
    ~MultiDOFJointState() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_MultiDOFJointState& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "MultiDOFJointState" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_MultiDOFJointState(*(Hako_MultiDOFJointState*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "MultiDOFJointState" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_MultiDOFJointState& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_MultiDOFJointState(cppData, (Hako_MultiDOFJointState**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "MultiDOFJointState" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "MultiDOFJointState" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "MultiDOFJointState" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_MultiDOFJointState_HPP_ */
