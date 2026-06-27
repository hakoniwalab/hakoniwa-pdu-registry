#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_ServiceRequestHeader_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_ServiceRequestHeader_HPP_

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
#include "hako_srv_msgs/pdu_cpptype_ServiceRequestHeader.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_ServiceRequestHeader(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_ServiceRequestHeader& src)
{
    // primitive: request_id
    cdr << src.request_id;
    // string: service_name
    cdr << src.service_name;
    // string: client_name
    cdr << src.client_name;
    // primitive: opcode
    cdr << src.opcode;
    // primitive: status_poll_interval_msec
    cdr << src.status_poll_interval_msec;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_ServiceRequestHeader(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_ServiceRequestHeader& dst)
{
    // primitive: request_id
    cdr >> dst.request_id;
    // string: service_name
    cdr >> dst.service_name;
    // string: client_name
    cdr >> dst.client_name;
    // primitive: opcode
    cdr >> dst.opcode;
    // primitive: status_poll_interval_msec
    cdr >> dst.status_poll_interval_msec;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_ServiceRequestHeader(
    const HakoCpp_ServiceRequestHeader& src,
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
        cpp2cdr_ServiceRequestHeader(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][ServiceRequestHeader] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_ServiceRequestHeader(
    const HakoCpp_ServiceRequestHeader& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_ServiceRequestHeader(
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
static inline bool hako_convert_cdr2cpp_ServiceRequestHeader(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_ServiceRequestHeader& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_ServiceRequestHeader(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][ServiceRequestHeader] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_ServiceRequestHeader(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_ServiceRequestHeader& dst)
{
    return hako_convert_cdr2cpp_ServiceRequestHeader(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_srv_msgs
{

class ServiceRequestHeaderCdr
{
public:
    ServiceRequestHeaderCdr() = default;
    ~ServiceRequestHeaderCdr() = default;

    int cpp2cdr(
        const HakoCpp_ServiceRequestHeader& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_ServiceRequestHeader(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_ServiceRequestHeader& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_ServiceRequestHeader(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_ServiceRequestHeader& cppData)
    {
        return hako_convert_cdr2cpp_ServiceRequestHeader(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_ServiceRequestHeader& cppData)
    {
        return hako_convert_cdr2cpp_ServiceRequestHeader(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_srv_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_ServiceRequestHeader_HPP_ */
