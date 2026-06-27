#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_std_msgs_Int32MultiArray_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_std_msgs_Int32MultiArray_HPP_

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
#include "std_msgs/pdu_cpptype_Int32MultiArray.hpp"

/*
 * Dependent CDR convertors
 */
#include "std_msgs/pdu_cpptype_cdr_conv_MultiArrayDimension.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_MultiArrayLayout.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_Int32MultiArray(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_Int32MultiArray& src)
{
    // nested struct: layout
    cpp2cdr_MultiArrayLayout(cdr, src.layout);
    // primitive sequence: data
    hako::pdu::cdr::serialize_sequence(cdr, src.data);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_Int32MultiArray(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_Int32MultiArray& dst)
{
    // nested struct: layout
    cdr2cpp_MultiArrayLayout(cdr, dst.layout);
    // primitive sequence: data
    hako::pdu::cdr::deserialize_sequence(cdr, dst.data);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_Int32MultiArray(
    const HakoCpp_Int32MultiArray& src,
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
        cpp2cdr_Int32MultiArray(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Int32MultiArray] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_Int32MultiArray(
    const HakoCpp_Int32MultiArray& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_Int32MultiArray(
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
static inline bool hako_convert_cdr2cpp_Int32MultiArray(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_Int32MultiArray& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_Int32MultiArray(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Int32MultiArray] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_Int32MultiArray(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_Int32MultiArray& dst)
{
    return hako_convert_cdr2cpp_Int32MultiArray(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::std_msgs
{

class Int32MultiArrayCdr
{
public:
    Int32MultiArrayCdr() = default;
    ~Int32MultiArrayCdr() = default;

    int cpp2cdr(
        const HakoCpp_Int32MultiArray& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_Int32MultiArray(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_Int32MultiArray& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_Int32MultiArray(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_Int32MultiArray& cppData)
    {
        return hako_convert_cdr2cpp_Int32MultiArray(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_Int32MultiArray& cppData)
    {
        return hako_convert_cdr2cpp_Int32MultiArray(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::std_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_std_msgs_Int32MultiArray_HPP_ */
