#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_MetaPdu_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_MetaPdu_HPP_

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
#include "hako_msgs/pdu_cpptype_MetaPdu.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_MetaPdu(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_MetaPdu& src)
{
    // primitive: total_len
    cdr << src.total_len;
    // primitive: magicno
    cdr << src.magicno;
    // primitive: version
    cdr << src.version;
    // primitive: flags
    cdr << src.flags;
    // primitive: meta_request_type
    cdr << src.meta_request_type;
    // primitive: hako_time_us
    cdr << src.hako_time_us;
    // primitive: asset_time_us
    cdr << src.asset_time_us;
    // primitive: real_time_us
    cdr << src.real_time_us;
    // string: robot_name
    cdr << src.robot_name;
    // primitive: channel_id
    cdr << src.channel_id;
    // primitive: body_len
    cdr << src.body_len;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_MetaPdu(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_MetaPdu& dst)
{
    // primitive: total_len
    cdr >> dst.total_len;
    // primitive: magicno
    cdr >> dst.magicno;
    // primitive: version
    cdr >> dst.version;
    // primitive: flags
    cdr >> dst.flags;
    // primitive: meta_request_type
    cdr >> dst.meta_request_type;
    // primitive: hako_time_us
    cdr >> dst.hako_time_us;
    // primitive: asset_time_us
    cdr >> dst.asset_time_us;
    // primitive: real_time_us
    cdr >> dst.real_time_us;
    // string: robot_name
    cdr >> dst.robot_name;
    // primitive: channel_id
    cdr >> dst.channel_id;
    // primitive: body_len
    cdr >> dst.body_len;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_MetaPdu(
    const HakoCpp_MetaPdu& src,
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
        cpp2cdr_MetaPdu(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][MetaPdu] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_MetaPdu(
    const HakoCpp_MetaPdu& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_MetaPdu(
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
static inline bool hako_convert_cdr2cpp_MetaPdu(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_MetaPdu& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_MetaPdu(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][MetaPdu] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_MetaPdu(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_MetaPdu& dst)
{
    return hako_convert_cdr2cpp_MetaPdu(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_msgs
{

class MetaPduCdr
{
public:
    MetaPduCdr() = default;
    ~MetaPduCdr() = default;

    int cpp2cdr(
        const HakoCpp_MetaPdu& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_MetaPdu(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_MetaPdu& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_MetaPdu(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_MetaPdu& cppData)
    {
        return hako_convert_cdr2cpp_MetaPdu(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_MetaPdu& cppData)
    {
        return hako_convert_cdr2cpp_MetaPdu(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_MetaPdu_HPP_ */
