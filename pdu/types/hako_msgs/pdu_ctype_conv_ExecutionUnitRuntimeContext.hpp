#ifndef _PDU_CTYPE_CONV_HAKO_hako_msgs_ExecutionUnitRuntimeContext_HPP_
#define _PDU_CTYPE_CONV_HAKO_hako_msgs_ExecutionUnitRuntimeContext_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "hako_msgs/pdu_ctype_ExecutionUnitRuntimeContext.h"
/*
 * Dependent ros data
 */
#include "hako_msgs/msg/execution_unit_runtime_context.hpp"

/*
 * Dependent Convertors
 */

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_primitive_array_ExecutionUnitRuntimeContext_context(const char* heap_ptr, Hako_ExecutionUnitRuntimeContext &src, hako_msgs::msg::ExecutionUnitRuntimeContext &dst)
{
    // Convert using len and off
    int offset = src._context_off;
    int length = src._context_len;
    if (length > 0) {
        dst.context.resize(length);
        memcpy(dst.context.data(), heap_ptr + offset, length * sizeof(Hako_uint8));
    }
    return 0;
}

static inline int _pdu2ros_ExecutionUnitRuntimeContext(const char* heap_ptr, Hako_ExecutionUnitRuntimeContext &src, hako_msgs::msg::ExecutionUnitRuntimeContext &dst)
{
    // primitive convert
    hako_convert_pdu2ros(src.config_hash, dst.config_hash);
    // primitive convert
    hako_convert_pdu2ros(src.epoch, dst.epoch);
    // primitive convert
    hako_convert_pdu2ros(src.owner_id, dst.owner_id);
    // primitive array convertor
    _pdu2ros_primitive_array_ExecutionUnitRuntimeContext_context(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_ExecutionUnitRuntimeContext(Hako_ExecutionUnitRuntimeContext &src, hako_msgs::msg::ExecutionUnitRuntimeContext &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_ExecutionUnitRuntimeContext((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_primitive_array_ExecutionUnitRuntimeContext_context(hako_msgs::msg::ExecutionUnitRuntimeContext &src, Hako_ExecutionUnitRuntimeContext &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray
    dst._context_len = src.context.size();
    if (dst._context_len > 0) {
        void* temp_ptr = dynamic_memory.allocate(dst._context_len, sizeof(Hako_uint8));
        memcpy(temp_ptr, src.context.data(), dst._context_len * sizeof(Hako_uint8));
        dst._context_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._context_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_ExecutionUnitRuntimeContext(hako_msgs::msg::ExecutionUnitRuntimeContext &src, Hako_ExecutionUnitRuntimeContext &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // primitive convert
        hako_convert_ros2pdu(src.config_hash, dst.config_hash);
        // primitive convert
        hako_convert_ros2pdu(src.epoch, dst.epoch);
        // primitive convert
        hako_convert_ros2pdu(src.owner_id, dst.owner_id);
        //primitive array copy
        _ros2pdu_primitive_array_ExecutionUnitRuntimeContext_context(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_ExecutionUnitRuntimeContext(hako_msgs::msg::ExecutionUnitRuntimeContext &src, Hako_ExecutionUnitRuntimeContext** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_ExecutionUnitRuntimeContext out;
    if (!_ros2pdu_ExecutionUnitRuntimeContext(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_ExecutionUnitRuntimeContext), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_ExecutionUnitRuntimeContext));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_ExecutionUnitRuntimeContext*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_ExecutionUnitRuntimeContext* hako_create_empty_pdu_ExecutionUnitRuntimeContext(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_ExecutionUnitRuntimeContext), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_ExecutionUnitRuntimeContext*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_hako_msgs_ExecutionUnitRuntimeContext_HPP_ */
