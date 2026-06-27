#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_JoinResponsePacket_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_JoinResponsePacket_HPP_

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
#include "hako_srv_msgs/pdu_cpptype_JoinResponsePacket.hpp"

/*
 * Dependent CDR convertors
 */
#include "hako_srv_msgs/pdu_cpptype_cdr_conv_JoinResponse.hpp"
#include "hako_srv_msgs/pdu_cpptype_cdr_conv_ServiceResponseHeader.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_JoinResponsePacket(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_JoinResponsePacket& src)
{
    // nested struct: header
    cpp2cdr_ServiceResponseHeader(cdr, src.header);
    // nested struct: body
    cpp2cdr_JoinResponse(cdr, src.body);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_JoinResponsePacket(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_JoinResponsePacket& dst)
{
    // nested struct: header
    cdr2cpp_ServiceResponseHeader(cdr, dst.header);
    // nested struct: body
    cdr2cpp_JoinResponse(cdr, dst.body);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_JoinResponsePacket(
    const HakoCpp_JoinResponsePacket& src,
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
        cpp2cdr_JoinResponsePacket(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][JoinResponsePacket] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_JoinResponsePacket(
    const HakoCpp_JoinResponsePacket& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_JoinResponsePacket(
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
static inline bool hako_convert_cdr2cpp_JoinResponsePacket(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_JoinResponsePacket& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_JoinResponsePacket(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][JoinResponsePacket] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_JoinResponsePacket(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_JoinResponsePacket& dst)
{
    return hako_convert_cdr2cpp_JoinResponsePacket(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_srv_msgs
{

class JoinResponsePacketCdr
{
public:
    JoinResponsePacketCdr() = default;
    ~JoinResponsePacketCdr() = default;

    int cpp2cdr(
        const HakoCpp_JoinResponsePacket& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_JoinResponsePacket(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_JoinResponsePacket& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_JoinResponsePacket(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_JoinResponsePacket& cppData)
    {
        return hako_convert_cdr2cpp_JoinResponsePacket(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_JoinResponsePacket& cppData)
    {
        return hako_convert_cdr2cpp_JoinResponsePacket(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_srv_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_JoinResponsePacket_HPP_ */
