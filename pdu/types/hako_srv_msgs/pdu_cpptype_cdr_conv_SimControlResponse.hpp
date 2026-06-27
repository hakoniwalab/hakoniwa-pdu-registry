#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_SimControlResponse_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_SimControlResponse_HPP_

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
#include "hako_srv_msgs/pdu_cpptype_SimControlResponse.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_SimControlResponse(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_SimControlResponse& src)
{
    // primitive: status_code
    cdr << src.status_code;
    // string: message
    cdr << src.message;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_SimControlResponse(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_SimControlResponse& dst)
{
    // primitive: status_code
    cdr >> dst.status_code;
    // string: message
    cdr >> dst.message;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_SimControlResponse(
    const HakoCpp_SimControlResponse& src,
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
        cpp2cdr_SimControlResponse(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][SimControlResponse] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_SimControlResponse(
    const HakoCpp_SimControlResponse& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_SimControlResponse(
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
static inline bool hako_convert_cdr2cpp_SimControlResponse(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_SimControlResponse& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_SimControlResponse(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][SimControlResponse] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_SimControlResponse(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_SimControlResponse& dst)
{
    return hako_convert_cdr2cpp_SimControlResponse(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_srv_msgs
{

class SimControlResponseCdr
{
public:
    SimControlResponseCdr() = default;
    ~SimControlResponseCdr() = default;

    int cpp2cdr(
        const HakoCpp_SimControlResponse& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_SimControlResponse(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_SimControlResponse& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_SimControlResponse(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_SimControlResponse& cppData)
    {
        return hako_convert_cdr2cpp_SimControlResponse(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_SimControlResponse& cppData)
    {
        return hako_convert_cdr2cpp_SimControlResponse(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_srv_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_SimControlResponse_HPP_ */
