#ifndef _PDU_CPPTYPE_CONV_HAKO_trajectory_msgs_MultiDOFJointTrajectoryPoint_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_trajectory_msgs_MultiDOFJointTrajectoryPoint_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "trajectory_msgs/pdu_ctype_MultiDOFJointTrajectoryPoint.h"
/*
 * Dependent cpp pdu data
 */
#include "trajectory_msgs/pdu_cpptype_MultiDOFJointTrajectoryPoint.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Duration.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Transform.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Vector3.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_struct_array_MultiDOFJointTrajectoryPoint_transforms(const char* heap_ptr, Hako_MultiDOFJointTrajectoryPoint &src, HakoCpp_MultiDOFJointTrajectoryPoint &dst)
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
static inline int cpp_pdu2cpp_struct_array_MultiDOFJointTrajectoryPoint_velocities(const char* heap_ptr, Hako_MultiDOFJointTrajectoryPoint &src, HakoCpp_MultiDOFJointTrajectoryPoint &dst)
{
    // Convert using len and off
    int offset = src._velocities_off;
    int length = src._velocities_len;
    if (length > 0) {
        dst.velocities.resize(length);
        Hako_Twist *temp_struct_ptr = (Hako_Twist *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_Twist(heap_ptr, *temp_struct_ptr, dst.velocities[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}
static inline int cpp_pdu2cpp_struct_array_MultiDOFJointTrajectoryPoint_accelerations(const char* heap_ptr, Hako_MultiDOFJointTrajectoryPoint &src, HakoCpp_MultiDOFJointTrajectoryPoint &dst)
{
    // Convert using len and off
    int offset = src._accelerations_off;
    int length = src._accelerations_len;
    if (length > 0) {
        dst.accelerations.resize(length);
        Hako_Twist *temp_struct_ptr = (Hako_Twist *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_Twist(heap_ptr, *temp_struct_ptr, dst.accelerations[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int cpp_pdu2cpp_MultiDOFJointTrajectoryPoint(const char* heap_ptr, Hako_MultiDOFJointTrajectoryPoint &src, HakoCpp_MultiDOFJointTrajectoryPoint &dst)
{
    // struct array convertor
    cpp_pdu2cpp_struct_array_MultiDOFJointTrajectoryPoint_transforms(heap_ptr, src, dst);
    // struct array convertor
    cpp_pdu2cpp_struct_array_MultiDOFJointTrajectoryPoint_velocities(heap_ptr, src, dst);
    // struct array convertor
    cpp_pdu2cpp_struct_array_MultiDOFJointTrajectoryPoint_accelerations(heap_ptr, src, dst);
    // Struct convert
    cpp_pdu2cpp_Duration(heap_ptr, src.time_from_start, dst.time_from_start);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_MultiDOFJointTrajectoryPoint(Hako_MultiDOFJointTrajectoryPoint &src, HakoCpp_MultiDOFJointTrajectoryPoint &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_MultiDOFJointTrajectoryPoint((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_struct_array_MultiDOFJointTrajectoryPoint_transforms(HakoCpp_MultiDOFJointTrajectoryPoint &src, Hako_MultiDOFJointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
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
static inline bool cpp_cpp2pdu_struct_array_MultiDOFJointTrajectoryPoint_velocities(HakoCpp_MultiDOFJointTrajectoryPoint &src, Hako_MultiDOFJointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._velocities_len = src.velocities.size();
    if (dst._velocities_len > 0) {
        Hako_Twist* temp_struct_ptr = (Hako_Twist*)dynamic_memory.allocate(dst._velocities_len, sizeof(Hako_Twist));
        dst._velocities_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._velocities_len; ++i) {
            cpp_cpp2pdu_Twist(src.velocities[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._velocities_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool cpp_cpp2pdu_struct_array_MultiDOFJointTrajectoryPoint_accelerations(HakoCpp_MultiDOFJointTrajectoryPoint &src, Hako_MultiDOFJointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._accelerations_len = src.accelerations.size();
    if (dst._accelerations_len > 0) {
        Hako_Twist* temp_struct_ptr = (Hako_Twist*)dynamic_memory.allocate(dst._accelerations_len, sizeof(Hako_Twist));
        dst._accelerations_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._accelerations_len; ++i) {
            cpp_cpp2pdu_Twist(src.accelerations[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._accelerations_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_MultiDOFJointTrajectoryPoint(HakoCpp_MultiDOFJointTrajectoryPoint &src, Hako_MultiDOFJointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //struct array convert
        cpp_cpp2pdu_struct_array_MultiDOFJointTrajectoryPoint_transforms(src, dst, dynamic_memory);
        //struct array convert
        cpp_cpp2pdu_struct_array_MultiDOFJointTrajectoryPoint_velocities(src, dst, dynamic_memory);
        //struct array convert
        cpp_cpp2pdu_struct_array_MultiDOFJointTrajectoryPoint_accelerations(src, dst, dynamic_memory);
        // struct convert
        cpp_cpp2pdu_Duration(src.time_from_start, dst.time_from_start, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_MultiDOFJointTrajectoryPoint(HakoCpp_MultiDOFJointTrajectoryPoint &src, Hako_MultiDOFJointTrajectoryPoint** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_MultiDOFJointTrajectoryPoint out;
    if (!cpp_cpp2pdu_MultiDOFJointTrajectoryPoint(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_MultiDOFJointTrajectoryPoint), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_MultiDOFJointTrajectoryPoint));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_MultiDOFJointTrajectoryPoint*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_MultiDOFJointTrajectoryPoint* hako_create_empty_pdu_MultiDOFJointTrajectoryPoint(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_MultiDOFJointTrajectoryPoint), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_MultiDOFJointTrajectoryPoint*)base_ptr;
}
namespace hako::pdu::msgs::trajectory_msgs
{
class MultiDOFJointTrajectoryPoint
{
public:
    MultiDOFJointTrajectoryPoint() = default;
    ~MultiDOFJointTrajectoryPoint() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_MultiDOFJointTrajectoryPoint& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "MultiDOFJointTrajectoryPoint" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_MultiDOFJointTrajectoryPoint(*(Hako_MultiDOFJointTrajectoryPoint*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "MultiDOFJointTrajectoryPoint" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_MultiDOFJointTrajectoryPoint& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_MultiDOFJointTrajectoryPoint(cppData, (Hako_MultiDOFJointTrajectoryPoint**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "MultiDOFJointTrajectoryPoint" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "MultiDOFJointTrajectoryPoint" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "MultiDOFJointTrajectoryPoint" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_trajectory_msgs_MultiDOFJointTrajectoryPoint_HPP_ */
