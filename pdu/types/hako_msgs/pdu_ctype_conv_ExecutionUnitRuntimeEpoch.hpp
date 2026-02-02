#ifndef _PDU_CTYPE_CONV_HAKO_hako_msgs_ExecutionUnitRuntimeEpoch_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_msgs_ExecutionUnitRuntimeEpoch_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_ExecutionUnitRuntimeEpoch.h"
/*
 * Dependent ros data
 */
#include "hako_msgs/msg/execution_unit_runtime_epoch.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_ExecutionUnitRuntimeEpoch_epoch(const char* heap_ptr, Hako_ExecutionUnitRuntimeEpoch &src, hako_msgs::msg::ExecutionUnitRuntimeEpoch &dst)
{
    // Convert using len and off
    int offset = src._epoch_off;
    int length = src._epoch_len;
    if (length > 0) {
        dst.epoch.resize(length);
        memcpy(dst.epoch.data(), heap_ptr + offset, length * sizeof(Hako_uint8));
    }
    return 0;
}

static inline int _pdu2ros_ExecutionUnitRuntimeEpoch(const char* heap_ptr, Hako_ExecutionUnitRuntimeEpoch &src, hako_msgs::msg::ExecutionUnitRuntimeEpoch &dst)
{
    // primitive array convertor
    _pdu2ros_primitive_array_ExecutionUnitRuntimeEpoch_epoch(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_ExecutionUnitRuntimeEpoch(Hako_ExecutionUnitRuntimeEpoch &src, hako_msgs::msg::ExecutionUnitRuntimeEpoch &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_ExecutionUnitRuntimeEpoch((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_ExecutionUnitRuntimeEpoch_epoch(hako_msgs::msg::ExecutionUnitRuntimeEpoch &src, Hako_ExecutionUnitRuntimeEpoch &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray
    dst._epoch_len = src.epoch.size();
    if (dst._epoch_len > 0) {
        void* temp_ptr = dynamic_memory.allocate(dst._epoch_len, sizeof(Hako_uint8));
        memcpy(temp_ptr, src.epoch.data(), dst._epoch_len * sizeof(Hako_uint8));
        dst._epoch_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._epoch_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_ExecutionUnitRuntimeEpoch(hako_msgs::msg::ExecutionUnitRuntimeEpoch &src, Hako_ExecutionUnitRuntimeEpoch &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        //primitive array copy
        _ros2pdu_primitive_array_ExecutionUnitRuntimeEpoch_epoch(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_ExecutionUnitRuntimeEpoch(hako_msgs::msg::ExecutionUnitRuntimeEpoch &src, Hako_ExecutionUnitRuntimeEpoch** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_ExecutionUnitRuntimeEpoch out;
    if (!_ros2pdu_ExecutionUnitRuntimeEpoch(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_ExecutionUnitRuntimeEpoch), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_ExecutionUnitRuntimeEpoch));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_ExecutionUnitRuntimeEpoch*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_ExecutionUnitRuntimeEpoch* hako_create_empty_pdu_ExecutionUnitRuntimeEpoch(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_ExecutionUnitRuntimeEpoch), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_ExecutionUnitRuntimeEpoch*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_msgs_ExecutionUnitRuntimeEpoch_HPP_ */
