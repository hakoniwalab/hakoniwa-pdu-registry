#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_SimpleVarray_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_SimpleVarray_HPP_

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
#include "hako_msgs/pdu_cpptype_SimpleVarray.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_SimpleVarray(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_SimpleVarray& src)
{
    // primitive sequence: data
    hako::pdu::cdr::serialize_sequence(cdr, src.data);
    // primitive fixed array: fixed_array[10]
    hako::pdu::cdr::serialize_fixed_array(cdr, src.fixed_array, 10);
    // primitive: p_mem1
    cdr << src.p_mem1;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_SimpleVarray(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_SimpleVarray& dst)
{
    // primitive sequence: data
    hako::pdu::cdr::deserialize_sequence(cdr, dst.data);
    // primitive fixed array: fixed_array[10]
    hako::pdu::cdr::deserialize_fixed_array(cdr, dst.fixed_array, 10);
    // primitive: p_mem1
    cdr >> dst.p_mem1;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_SimpleVarray(
    const HakoCpp_SimpleVarray& src,
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
        cpp2cdr_SimpleVarray(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][SimpleVarray] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_SimpleVarray(
    const HakoCpp_SimpleVarray& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_SimpleVarray(
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
static inline bool hako_convert_cdr2cpp_SimpleVarray(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_SimpleVarray& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_SimpleVarray(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][SimpleVarray] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_SimpleVarray(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_SimpleVarray& dst)
{
    return hako_convert_cdr2cpp_SimpleVarray(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_msgs
{

class SimpleVarrayCdr
{
public:
    SimpleVarrayCdr() = default;
    ~SimpleVarrayCdr() = default;

    int cpp2cdr(
        const HakoCpp_SimpleVarray& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_SimpleVarray(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_SimpleVarray& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_SimpleVarray(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_SimpleVarray& cppData)
    {
        return hako_convert_cdr2cpp_SimpleVarray(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_SimpleVarray& cppData)
    {
        return hako_convert_cdr2cpp_SimpleVarray(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_SimpleVarray_HPP_ */
