#ifndef _PDU_CTYPE_CONV_HAKO_nav_msgs_GridCells_HPP_
#define _PDU_CTYPE_CONV_HAKO_nav_msgs_GridCells_HPP_

#include "pdu_primitive_ctypes.h"
#include "ros_primitive_types.hpp"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "nav_msgs/pdu_ctype_GridCells.h"
/*
 * Dependent ros data
 */
#include "nav_msgs/msg/grid_cells.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_ctype_conv_Time.hpp"
#include "geometry_msgs/pdu_ctype_conv_Point.hpp"
#include "std_msgs/pdu_ctype_conv_Header.hpp"

/***************************
 *
 * PDU ==> ROS2
 *
 ***************************/
static inline int _pdu2ros_struct_array_GridCells_cells(const char* heap_ptr, Hako_GridCells &src, nav_msgs::msg::GridCells &dst)
{
    // Convert using len and off
    int offset = src._cells_off;
    int length = src._cells_len;
    if (length > 0) {
        dst.cells.resize(length);
        Hako_Point *temp_struct_ptr = (Hako_Point *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            _pdu2ros_Point(heap_ptr, *temp_struct_ptr, dst.cells[i]);
            temp_struct_ptr++;
        }
    }
    else {
        dst.cells.clear();  // a reused destination keeps nothing from before
    }
    return 0;
}

static inline int _pdu2ros_GridCells(const char* heap_ptr, Hako_GridCells &src, nav_msgs::msg::GridCells &dst)
{
    // Struct convert
    _pdu2ros_Header(heap_ptr, src.header, dst.header);
    // primitive convert
    hako_convert_pdu2ros(src.cell_width, dst.cell_width);
    // primitive convert
    hako_convert_pdu2ros(src.cell_height, dst.cell_height);
    // struct array convertor
    _pdu2ros_struct_array_GridCells_cells(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2ros_GridCells(Hako_GridCells &src, nav_msgs::msg::GridCells &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return _pdu2ros_GridCells((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * ROS2 ==> PDU
 *
 ***************************/
static inline bool _ros2pdu_struct_array_GridCells_cells(nav_msgs::msg::GridCells &src, Hako_GridCells &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._cells_len = hako_pdu_array_length(src.cells.size());
    if (dst._cells_len > 0) {
        Hako_Point* temp_struct_ptr = (Hako_Point*)dynamic_memory.allocate(dst._cells_len, sizeof(Hako_Point));
        dst._cells_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._cells_len; ++i) {
            if (!_ros2pdu_Point(src.cells[i], *temp_struct_ptr, dynamic_memory)) {
                return false;
            }
            temp_struct_ptr++;
        }
    }
    else {
        dst._cells_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool _ros2pdu_GridCells(nav_msgs::msg::GridCells &src, Hako_GridCells &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        if (!_ros2pdu_Header(src.header, dst.header, dynamic_memory)) {
            return false;
        }
        // primitive convert
        hako_convert_ros2pdu(src.cell_width, dst.cell_width);
        // primitive convert
        hako_convert_ros2pdu(src.cell_height, dst.cell_height);
        //struct array convert
        if (!_ros2pdu_struct_array_GridCells_cells(src, dst, dynamic_memory)) {
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_ros2pdu_GridCells(nav_msgs::msg::GridCells &src, Hako_GridCells** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_GridCells out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_GridCells(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_GridCells), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_GridCells));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_GridCells*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

// Builds the PDU straight into buffer (no intermediate PDU; each array of the
// message is copied once), byte for byte as hako_convert_ros2pdu_GridCells() lays
// it out. buffer needs no alignment and must not overlap src's arrays. Returns
// the PDU size, or -1 (nothing written) on a conversion error, a buffer too
// small or overlapping src's arrays.
static inline int hako_convert_ros2pdu_into_GridCells(nav_msgs::msg::GridCells &src, char* buffer, int buffer_len)
{
    PduDynamicMemory dynamic_memory;
    Hako_GridCells out{};  // zeroed: no stray bytes in the padding
    if (!_ros2pdu_GridCells(src, out, dynamic_memory)) {
        std::cerr << "[ConvertorError][" << "GridCells" << "] hako_convert_ros2pdu returned error code: " << -1 << std::endl;
        return -1;
    }
    return hako_pdu_build_into("GridCells", &out, sizeof(out), dynamic_memory, buffer, buffer_len);
}

static inline Hako_GridCells* hako_create_empty_pdu_GridCells(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_GridCells), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_GridCells*)base_ptr;
}
#endif /* _PDU_CTYPE_CONV_HAKO_nav_msgs_GridCells_HPP_ */
