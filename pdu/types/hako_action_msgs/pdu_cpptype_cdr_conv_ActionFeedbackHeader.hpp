#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_action_msgs_ActionFeedbackHeader_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_action_msgs_ActionFeedbackHeader_HPP_

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
#include "hako_action_msgs/pdu_cpptype_ActionFeedbackHeader.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_ActionFeedbackHeader(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_ActionFeedbackHeader& src)
{
    // primitive: version
    cdr << src.version;
    // primitive fixed array: reserved[3]
    hako::pdu::cdr::serialize_fixed_array(cdr, src.reserved, 3);
    // primitive fixed array: goal_id[16]
    hako::pdu::cdr::serialize_fixed_array(cdr, src.goal_id, 16);
    // primitive: sequence_no
    cdr << src.sequence_no;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_ActionFeedbackHeader(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_ActionFeedbackHeader& dst)
{
    // primitive: version
    cdr >> dst.version;
    // primitive fixed array: reserved[3]
    hako::pdu::cdr::deserialize_fixed_array(cdr, dst.reserved, 3);
    // primitive fixed array: goal_id[16]
    hako::pdu::cdr::deserialize_fixed_array(cdr, dst.goal_id, 16);
    // primitive: sequence_no
    cdr >> dst.sequence_no;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_ActionFeedbackHeader(
    const HakoCpp_ActionFeedbackHeader& src,
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
        cpp2cdr_ActionFeedbackHeader(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][ActionFeedbackHeader] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_ActionFeedbackHeader(
    const HakoCpp_ActionFeedbackHeader& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_ActionFeedbackHeader(
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
static inline bool hako_convert_cdr2cpp_ActionFeedbackHeader(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_ActionFeedbackHeader& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_ActionFeedbackHeader(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][ActionFeedbackHeader] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_ActionFeedbackHeader(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_ActionFeedbackHeader& dst)
{
    return hako_convert_cdr2cpp_ActionFeedbackHeader(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_action_msgs
{

class ActionFeedbackHeaderCdr
{
public:
    ActionFeedbackHeaderCdr() = default;
    ~ActionFeedbackHeaderCdr() = default;

    int cpp2cdr(
        const HakoCpp_ActionFeedbackHeader& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_ActionFeedbackHeader(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_ActionFeedbackHeader& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_ActionFeedbackHeader(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_ActionFeedbackHeader& cppData)
    {
        return hako_convert_cdr2cpp_ActionFeedbackHeader(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_ActionFeedbackHeader& cppData)
    {
        return hako_convert_cdr2cpp_ActionFeedbackHeader(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_action_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_action_msgs_ActionFeedbackHeader_HPP_ */
