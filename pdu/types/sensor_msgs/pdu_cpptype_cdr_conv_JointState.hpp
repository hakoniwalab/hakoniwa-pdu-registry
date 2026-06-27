#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_JointState_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_JointState_HPP_

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
#include "sensor_msgs/pdu_cpptype_JointState.hpp"

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
static inline void cpp2cdr_JointState(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_JointState& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // string sequence: name
    hako::pdu::cdr::serialize_sequence(cdr, src.name);
    // primitive sequence: position
    hako::pdu::cdr::serialize_sequence(cdr, src.position);
    // primitive sequence: velocity
    hako::pdu::cdr::serialize_sequence(cdr, src.velocity);
    // primitive sequence: effort
    hako::pdu::cdr::serialize_sequence(cdr, src.effort);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_JointState(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_JointState& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // string sequence: name
    hako::pdu::cdr::deserialize_sequence(cdr, dst.name);
    // primitive sequence: position
    hako::pdu::cdr::deserialize_sequence(cdr, dst.position);
    // primitive sequence: velocity
    hako::pdu::cdr::deserialize_sequence(cdr, dst.velocity);
    // primitive sequence: effort
    hako::pdu::cdr::deserialize_sequence(cdr, dst.effort);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_JointState(
    const HakoCpp_JointState& src,
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
        cpp2cdr_JointState(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][JointState] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_JointState(
    const HakoCpp_JointState& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_JointState(
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
static inline bool hako_convert_cdr2cpp_JointState(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_JointState& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_JointState(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][JointState] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_JointState(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_JointState& dst)
{
    return hako_convert_cdr2cpp_JointState(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::sensor_msgs
{

class JointStateCdr
{
public:
    JointStateCdr() = default;
    ~JointStateCdr() = default;

    int cpp2cdr(
        const HakoCpp_JointState& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_JointState(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_JointState& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_JointState(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_JointState& cppData)
    {
        return hako_convert_cdr2cpp_JointState(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_JointState& cppData)
    {
        return hako_convert_cdr2cpp_JointState(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::sensor_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_JointState_HPP_ */
