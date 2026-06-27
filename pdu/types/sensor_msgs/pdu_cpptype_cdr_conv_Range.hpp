#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_Range_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_Range_HPP_

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
#include "sensor_msgs/pdu_cpptype_Range.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_Range(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_Range& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // primitive: radiation_type
    cdr << src.radiation_type;
    // primitive: field_of_view
    cdr << src.field_of_view;
    // primitive: min_range
    cdr << src.min_range;
    // primitive: max_range
    cdr << src.max_range;
    // primitive: range
    cdr << src.range;
    // primitive: variance
    cdr << src.variance;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_Range(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_Range& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // primitive: radiation_type
    cdr >> dst.radiation_type;
    // primitive: field_of_view
    cdr >> dst.field_of_view;
    // primitive: min_range
    cdr >> dst.min_range;
    // primitive: max_range
    cdr >> dst.max_range;
    // primitive: range
    cdr >> dst.range;
    // primitive: variance
    cdr >> dst.variance;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_Range(
    const HakoCpp_Range& src,
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
        cpp2cdr_Range(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Range] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_Range(
    const HakoCpp_Range& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_Range(
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
static inline bool hako_convert_cdr2cpp_Range(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_Range& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_Range(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Range] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_Range(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_Range& dst)
{
    return hako_convert_cdr2cpp_Range(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::sensor_msgs
{

class RangeCdr
{
public:
    RangeCdr() = default;
    ~RangeCdr() = default;

    int cpp2cdr(
        const HakoCpp_Range& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_Range(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_Range& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_Range(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_Range& cppData)
    {
        return hako_convert_cdr2cpp_Range(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_Range& cppData)
    {
        return hako_convert_cdr2cpp_Range(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::sensor_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_Range_HPP_ */
