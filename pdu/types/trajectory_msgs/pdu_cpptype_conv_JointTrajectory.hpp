#ifndef _PDU_CPPTYPE_CONV_HAKO_trajectory_msgs_JointTrajectory_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_trajectory_msgs_JointTrajectory_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "trajectory_msgs/pdu_ctype_JointTrajectory.h"
/*
 * Dependent cpp pdu data
 */
#include "trajectory_msgs/pdu_cpptype_JointTrajectory.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Duration.hpp"
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"
#include "trajectory_msgs/pdu_cpptype_conv_JointTrajectoryPoint.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_string_array_JointTrajectory_joint_names(const char* heap_ptr, Hako_JointTrajectory &src, HakoCpp_JointTrajectory &dst)
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
static inline int cpp_pdu2cpp_struct_array_JointTrajectory_points(const char* heap_ptr, Hako_JointTrajectory &src, HakoCpp_JointTrajectory &dst)
{
    // Convert using len and off
    int offset = src._points_off;
    int length = src._points_len;
    if (length > 0) {
        dst.points.resize(length);
        Hako_JointTrajectoryPoint *temp_struct_ptr = (Hako_JointTrajectoryPoint *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_JointTrajectoryPoint(heap_ptr, *temp_struct_ptr, dst.points[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int cpp_pdu2cpp_JointTrajectory(const char* heap_ptr, Hako_JointTrajectory &src, HakoCpp_JointTrajectory &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // string array convertor
    cpp_pdu2cpp_string_array_JointTrajectory_joint_names(heap_ptr, src, dst);
    // struct array convertor
    cpp_pdu2cpp_struct_array_JointTrajectory_points(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_JointTrajectory(Hako_JointTrajectory &src, HakoCpp_JointTrajectory &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_JointTrajectory((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_string_array_JointTrajectory_joint_names(HakoCpp_JointTrajectory &src, Hako_JointTrajectory &dst, PduDynamicMemory &dynamic_memory)
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
static inline bool cpp_cpp2pdu_struct_array_JointTrajectory_points(HakoCpp_JointTrajectory &src, Hako_JointTrajectory &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._points_len = src.points.size();
    if (dst._points_len > 0) {
        Hako_JointTrajectoryPoint* temp_struct_ptr = (Hako_JointTrajectoryPoint*)dynamic_memory.allocate(dst._points_len, sizeof(Hako_JointTrajectoryPoint));
        dst._points_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._points_len; ++i) {
            cpp_cpp2pdu_JointTrajectoryPoint(src.points[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._points_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_JointTrajectory(HakoCpp_JointTrajectory &src, Hako_JointTrajectory &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory);
        // string array convert
        cpp_cpp2pdu_string_array_JointTrajectory_joint_names(src, dst, dynamic_memory);
        //struct array convert
        cpp_cpp2pdu_struct_array_JointTrajectory_points(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_JointTrajectory(HakoCpp_JointTrajectory &src, Hako_JointTrajectory** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_JointTrajectory out;
    if (!cpp_cpp2pdu_JointTrajectory(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_JointTrajectory), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_JointTrajectory));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_JointTrajectory*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_JointTrajectory* hako_create_empty_pdu_JointTrajectory(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_JointTrajectory), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_JointTrajectory*)base_ptr;
}
namespace hako::pdu::msgs::trajectory_msgs
{
class JointTrajectory
{
public:
    JointTrajectory() = default;
    ~JointTrajectory() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_JointTrajectory& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "JointTrajectory" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_JointTrajectory(*(Hako_JointTrajectory*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "JointTrajectory" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_JointTrajectory& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_JointTrajectory(cppData, (Hako_JointTrajectory**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "JointTrajectory" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "JointTrajectory" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "JointTrajectory" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_trajectory_msgs_JointTrajectory_HPP_ */
