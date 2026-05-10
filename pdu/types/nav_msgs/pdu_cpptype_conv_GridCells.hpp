#ifndef _PDU_CPPTYPE_CONV_HAKO_nav_msgs_GridCells_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_nav_msgs_GridCells_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "nav_msgs/pdu_ctype_GridCells.h"
/*
 * Dependent cpp pdu data
 */
#include "nav_msgs/pdu_cpptype_GridCells.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_conv_Point.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_struct_array_GridCells_cells(const char* heap_ptr, Hako_GridCells &src, HakoCpp_GridCells &dst)
{
    // Convert using len and off
    int offset = src._cells_off;
    int length = src._cells_len;
    if (length > 0) {
        dst.cells.resize(length);
        Hako_Point *temp_struct_ptr = (Hako_Point *)(heap_ptr + offset);
        for (int i = 0; i < length; ++i) {
            cpp_pdu2cpp_Point(heap_ptr, *temp_struct_ptr, dst.cells[i]);
            temp_struct_ptr++;
        }
    }
    return 0;
}

static inline int cpp_pdu2cpp_GridCells(const char* heap_ptr, Hako_GridCells &src, HakoCpp_GridCells &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // primitive convert
    hako_convert_pdu2cpp(src.cell_width, dst.cell_width);
    // primitive convert
    hako_convert_pdu2cpp(src.cell_height, dst.cell_height);
    // struct array convertor
    cpp_pdu2cpp_struct_array_GridCells_cells(heap_ptr, src, dst);
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_GridCells(Hako_GridCells &src, HakoCpp_GridCells &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_GridCells((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_struct_array_GridCells_cells(HakoCpp_GridCells &src, Hako_GridCells &dst, PduDynamicMemory &dynamic_memory)
{
    // array struct
    dst._cells_len = src.cells.size();
    if (dst._cells_len > 0) {
        Hako_Point* temp_struct_ptr = (Hako_Point*)dynamic_memory.allocate(dst._cells_len, sizeof(Hako_Point));
        dst._cells_off = dynamic_memory.get_offset(temp_struct_ptr);
        for (int i = 0; i < dst._cells_len; ++i) {
            cpp_cpp2pdu_Point(src.cells[i], *temp_struct_ptr, dynamic_memory);
            temp_struct_ptr++;
        }
    }
    else {
        dst._cells_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_GridCells(HakoCpp_GridCells &src, Hako_GridCells &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory);
        // primitive convert
        hako_convert_cpp2pdu(src.cell_width, dst.cell_width);
        // primitive convert
        hako_convert_cpp2pdu(src.cell_height, dst.cell_height);
        //struct array convert
        cpp_cpp2pdu_struct_array_GridCells_cells(src, dst, dynamic_memory);
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_GridCells(HakoCpp_GridCells &src, Hako_GridCells** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_GridCells out;
    if (!cpp_cpp2pdu_GridCells(src, out, dynamic_memory)) {
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

static inline Hako_GridCells* hako_create_empty_pdu_GridCells(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_GridCells), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_GridCells*)base_ptr;
}
namespace hako::pdu::msgs::nav_msgs
{
class GridCells
{
public:
    GridCells() = default;
    ~GridCells() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_GridCells& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "GridCells" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_GridCells(*(Hako_GridCells*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "GridCells" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_GridCells& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_GridCells(cppData, (Hako_GridCells**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "GridCells" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "GridCells" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "GridCells" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_nav_msgs_GridCells_HPP_ */
