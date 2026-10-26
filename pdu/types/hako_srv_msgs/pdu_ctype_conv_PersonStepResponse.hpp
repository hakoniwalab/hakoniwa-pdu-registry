#ifndef _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_PersonStepResponse_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_PersonStepResponse_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_srv_msgs/pdu_ctype_PersonStepResponse.h"
/*
 * Dependent ros data
 */
#include "hako_srv_msgs/msg/person_step_response.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "geometry_msgs/pdu_ctype_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_ctype_conv_Transform.hpp"
#include "geometry_msgs/pdu_ctype_conv_Twist.hpp"
#include "geometry_msgs/pdu_ctype_conv_Vector3.hpp"
#include "sensor_msgs/pdu_ctype_conv_JointState.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/

static inline int _pdu2ros_PersonStepResponse(const char* heap_ptr, Hako_PersonStepResponse &src, hako_srv_msgs::msg::PersonStepResponse &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.step, dst.step);
    // primitive convert
    hako_convert_pdu2ros(src.result_code, dst.result_code);
    // primitive convert
    hako_convert_pdu2ros(src.sim_time_usec, dst.sim_time_usec);
    // Struct convert
    _pdu2ros_Transform(heap_ptr, src.pose, dst.pose);
    // Struct convert
    _pdu2ros_Twist(heap_ptr, src.twist, dst.twist);
    // Struct convert
    _pdu2ros_JointState(heap_ptr, src.joints, dst.joints);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_PersonStepResponse(Hako_PersonStepResponse &src, hako_srv_msgs::msg::PersonStepResponse &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_PersonStepResponse((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/

static inline bool _ros2pdu_PersonStepResponse(hako_srv_msgs::msg::PersonStepResponse &src, Hako_PersonStepResponse &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.step, dst.step);
        // primitive convert
        hako_convert_ros2pdu(src.result_code, dst.result_code);
        // primitive convert
        hako_convert_ros2pdu(src.sim_time_usec, dst.sim_time_usec);
        // struct convert
        _ros2pdu_Transform(src.pose, dst.pose, dynamic_memory);
        // struct convert
        _ros2pdu_Twist(src.twist, dst.twist, dynamic_memory);
        // struct convert
        _ros2pdu_JointState(src.joints, dst.joints, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_PersonStepResponse(hako_srv_msgs::msg::PersonStepResponse &src, Hako_PersonStepResponse** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_PersonStepResponse out;
    if (!_ros2pdu_PersonStepResponse(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_PersonStepResponse), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_PersonStepResponse));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_PersonStepResponse*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_PersonStepResponse* hako_create_empty_pdu_PersonStepResponse(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_PersonStepResponse), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_PersonStepResponse*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_srv_msgs_PersonStepResponse_HPP_ */
