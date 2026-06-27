#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_JoinRequestPacket_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_JoinRequestPacket_HPP_

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
#include "hako_srv_msgs/pdu_cpptype_JoinRequestPacket.hpp"

/*
 * Dependent CDR convertors
 */
#include "hako_srv_msgs/pdu_cpptype_cdr_conv_JoinRequest.hpp"
#include "hako_srv_msgs/pdu_cpptype_cdr_conv_ServiceRequestHeader.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_JoinRequestPacket(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_JoinRequestPacket& src)
{
    // nested struct: header
    cpp2cdr_ServiceRequestHeader(cdr, src.header);
    // nested struct: body
    cpp2cdr_JoinRequest(cdr, src.body);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_JoinRequestPacket(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_JoinRequestPacket& dst)
{
    // nested struct: header
    cdr2cpp_ServiceRequestHeader(cdr, dst.header);
    // nested struct: body
    cdr2cpp_JoinRequest(cdr, dst.body);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_JoinRequestPacket(
    const HakoCpp_JoinRequestPacket& src,
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
        cpp2cdr_JoinRequestPacket(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][JoinRequestPacket] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_JoinRequestPacket(
    const HakoCpp_JoinRequestPacket& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_JoinRequestPacket(
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
static inline bool hako_convert_cdr2cpp_JoinRequestPacket(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_JoinRequestPacket& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_JoinRequestPacket(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][JoinRequestPacket] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_JoinRequestPacket(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_JoinRequestPacket& dst)
{
    return hako_convert_cdr2cpp_JoinRequestPacket(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_srv_msgs
{

class JoinRequestPacketCdr
{
public:
    JoinRequestPacketCdr() = default;
    ~JoinRequestPacketCdr() = default;

    int cpp2cdr(
        const HakoCpp_JoinRequestPacket& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_JoinRequestPacket(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_JoinRequestPacket& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_JoinRequestPacket(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_JoinRequestPacket& cppData)
    {
        return hako_convert_cdr2cpp_JoinRequestPacket(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_JoinRequestPacket& cppData)
    {
        return hako_convert_cdr2cpp_JoinRequestPacket(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_srv_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_JoinRequestPacket_HPP_ */
