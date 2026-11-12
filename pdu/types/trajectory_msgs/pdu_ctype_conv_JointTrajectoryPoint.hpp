#ifndef _PDU_CTYPE_CONV_HAKO_trajectory_msgs_JointTrajectoryPoint_HPP_
#define _PDU_CTYPE_CONV_HAKO_trajectory_msgs_JointTrajectoryPoint_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "trajectory_msgs/pdu_ctype_JointTrajectoryPoint.h"
/*
 * Dependent ros data
 */
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Duration.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_JointTrajectoryPoint_positions(const char* heap_ptr, Hako_JointTrajectoryPoint &src, trajectory_msgs::msg::JointTrajectoryPoint &dst)
{
    // Convert using len and off
    int offset = src._positions_off;
    int length = src._positions_len;
    if (length > 0) {
        dst.positions.resize(length);
        memcpy(dst.positions.data(), heap_ptr + offset, length * sizeof(Hako_float64));
    }
    else {
        dst.positions.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}
static inline int _pdu2ros_primitive_array_JointTrajectoryPoint_velocities(const char* heap_ptr, Hako_JointTrajectoryPoint &src, trajectory_msgs::msg::JointTrajectoryPoint &dst)
{
    // Convert using len and off
    int offset = src._velocities_off;
    int length = src._velocities_len;
    if (length > 0) {
        dst.velocities.resize(length);
        memcpy(dst.velocities.data(), heap_ptr + offset, length * sizeof(Hako_float64));
    }
    else {
        dst.velocities.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}
static inline int _pdu2ros_primitive_array_JointTrajectoryPoint_accelerations(const char* heap_ptr, Hako_JointTrajectoryPoint &src, trajectory_msgs::msg::JointTrajectoryPoint &dst)
{
    // Convert using len and off
    int offset = src._accelerations_off;
    int length = src._accelerations_len;
    if (length > 0) {
        dst.accelerations.resize(length);
        memcpy(dst.accelerations.data(), heap_ptr + offset, length * sizeof(Hako_float64));
    }
    else {
        dst.accelerations.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}
static inline int _pdu2ros_primitive_array_JointTrajectoryPoint_effort(const char* heap_ptr, Hako_JointTrajectoryPoint &src, trajectory_msgs::msg::JointTrajectoryPoint &dst)
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

static inline int _pdu2ros_JointTrajectoryPoint(const char* heap_ptr, Hako_JointTrajectoryPoint &src, trajectory_msgs::msg::JointTrajectoryPoint &dst)
{
    // primitive array convertor
    _pdu2ros_primitive_array_JointTrajectoryPoint_positions(heap_ptr, src, dst);
    // primitive array convertor
    _pdu2ros_primitive_array_JointTrajectoryPoint_velocities(heap_ptr, src, dst);
    // primitive array convertor
    _pdu2ros_primitive_array_JointTrajectoryPoint_accelerations(heap_ptr, src, dst);
    // primitive array convertor
    _pdu2ros_primitive_array_JointTrajectoryPoint_effort(heap_ptr, src, dst);
    // Struct convert
    _pdu2ros_Duration(heap_ptr, src.time_from_start, dst.time_from_start);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_JointTrajectoryPoint(Hako_JointTrajectoryPoint &src, trajectory_msgs::msg::JointTrajectoryPoint &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_JointTrajectoryPoint((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_JointTrajectoryPoint_positions(trajectory_msgs::msg::JointTrajectoryPoint &src, Hako_JointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._positions_len = hako_pdu_array_length(src.positions.size());
    if (dst._positions_len > 0) {
        dst._positions_off = dynamic_memory.reference(src.positions.data(), dst._positions_len, sizeof(Hako_float64));
    }
    else {
        dst._positions_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool _ros2pdu_primitive_array_JointTrajectoryPoint_velocities(trajectory_msgs::msg::JointTrajectoryPoint &src, Hako_JointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._velocities_len = hako_pdu_array_length(src.velocities.size());
    if (dst._velocities_len > 0) {
        dst._velocities_off = dynamic_memory.reference(src.velocities.data(), dst._velocities_len, sizeof(Hako_float64));
    }
    else {
        dst._velocities_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool _ros2pdu_primitive_array_JointTrajectoryPoint_accelerations(trajectory_msgs::msg::JointTrajectoryPoint &src, Hako_JointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._accelerations_len = hako_pdu_array_length(src.accelerations.size());
    if (dst._accelerations_len > 0) {
        dst._accelerations_off = dynamic_memory.reference(src.accelerations.data(), dst._accelerations_len, sizeof(Hako_float64));
    }
    else {
        dst._accelerations_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool _ros2pdu_primitive_array_JointTrajectoryPoint_effort(trajectory_msgs::msg::JointTrajectoryPoint &src, Hako_JointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray (the source's bytes are copied once, straight into the PDU)
    dst._effort_len = hako_pdu_array_length(src.effort.size());
    if (dst._effort_len > 0) {
        dst._effort_off = dynamic_memory.reference(src.effort.data(), dst._effort_len, sizeof(Hako_float64));
    }
    else {
        dst._effort_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_JointTrajectoryPoint(trajectory_msgs::msg::JointTrajectoryPoint &src, Hako_JointTrajectoryPoint &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //primitive array copy
        if (!_ros2pdu_primitive_array_JointTrajectoryPoint_positions(src, dst, dynamic_memory)) {
            return false;
        }
        //primitive array copy
        if (!_ros2pdu_primitive_array_JointTrajectoryPoint_velocities(src, dst, dynamic_memory)) {
            return false;
        }
        //primitive array copy
        if (!_ros2pdu_primitive_array_JointTrajectoryPoint_accelerations(src, dst, dynamic_memory)) {
            return false;
        }
        //primitive array copy
        if (!_ros2pdu_primitive_array_JointTrajectoryPoint_effort(src, dst, dynamic_memory)) {
            return false;
        }
        // struct convert
        if (!_ros2pdu_Duration(src.time_from_start, dst.time_from_start, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_JointTrajectoryPoint(trajectory_msgs::msg::JointTrajectoryPoint &src, Hako_JointTrajectoryPoint** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_JointTrajectoryPoint out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_JointTrajectoryPoint(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_JointTrajectoryPoint), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_JointTrajectoryPoint));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_JointTrajectoryPoint*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_JointTrajectoryPoint() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_JointTrajectoryPoint(trajectory_msgs::msg::JointTrajectoryPoint &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_JointTrajectoryPoint out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_JointTrajectoryPoint(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "JointTrajectoryPoint" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("JointTrajectoryPoint", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_JointTrajectoryPoint* hako_create_empty_pdu_JointTrajectoryPoint(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_JointTrajectoryPoint), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_JointTrajectoryPoint*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_trajectory_msgs_JointTrajectoryPoint_HPP_ */
