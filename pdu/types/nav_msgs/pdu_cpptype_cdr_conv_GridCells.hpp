#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_nav_msgs_GridCells_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_nav_msgs_GridCells_HPP_

#include <cstring>
#include <iostream>
#include <vector>

#include <fastcdr/Cdr.h>
#include <fastcdr/FastBuffer.h>

#include "pdu_cdr_runtime.hpp"
#include "pdu_primitive_ctypes.h"

/*
 * Dependent cpp pdu data
 */
#include "nav_msgs/pdu_cpptype_GridCells.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Point.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_GridCells(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_GridCells& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // primitive: cell_width
    cdr << src.cell_width;
    // primitive: cell_height
    cdr << src.cell_height;
    // struct sequence: cells
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.cells);
        for (const auto& elem : src.cells) {
            cpp2cdr_Point(cdr, elem);
        }
    }
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_GridCells(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_GridCells& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // primitive: cell_width
    cdr >> dst.cell_width;
    // primitive: cell_height
    cdr >> dst.cell_height;
    // struct sequence: cells
    {
        uint32_t length = 0;
        cdr >> length;
        dst.cells.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_Point(cdr, dst.cells[i]);
        }
    }
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_GridCells(
    const HakoCpp_GridCells& src,
    char* cdr_buffer,
    int buffer_len)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return -1;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(cdr_buffer, static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.serialize_encapsulation();
        cpp2cdr_GridCells(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][GridCells] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_GridCells(
    const HakoCpp_GridCells& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_GridCells(
            src,
            reinterpret_cast<char*>(cdr_payload.data()),
            static_cast<int>(cdr_payload.size()));
        if (len >= 0) {
            cdr_payload.resize(static_cast<size_t>(len));
            return len;
        }
        capacity *= 2;
    }

    cdr_payload.clear();
    return -1;
}

/***************************
 *
 * full CDR payload ==> CPP PDU
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline bool hako_convert_cdr2cpp_GridCells(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_GridCells& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_GridCells(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][GridCells] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_GridCells(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_GridCells& dst)
{
    return hako_convert_cdr2cpp_GridCells(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::nav_msgs
{

class GridCellsCdr
{
public:
    GridCellsCdr() = default;
    ~GridCellsCdr() = default;

    int cpp2cdr(
        const HakoCpp_GridCells& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_GridCells(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_GridCells& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_GridCells(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_GridCells& cppData)
    {
        return hako_convert_cdr2cpp_GridCells(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_GridCells& cppData)
    {
        return hako_convert_cdr2cpp_GridCells(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::nav_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_nav_msgs_GridCells_HPP_ */
