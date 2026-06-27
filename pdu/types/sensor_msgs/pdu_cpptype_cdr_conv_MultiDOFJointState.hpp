#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_MultiDOFJointState_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_MultiDOFJointState_HPP_

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
#include "sensor_msgs/pdu_cpptype_MultiDOFJointState.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Transform.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Vector3.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Wrench.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_MultiDOFJointState(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_MultiDOFJointState& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // string sequence: joint_names
    hako::pdu::cdr::serialize_sequence(cdr, src.joint_names);
    // struct sequence: transforms
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.transforms);
        for (const auto& elem : src.transforms) {
            cpp2cdr_Transform(cdr, elem);
        }
    }
    // struct sequence: twist
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.twist);
        for (const auto& elem : src.twist) {
            cpp2cdr_Twist(cdr, elem);
        }
    }
    // struct sequence: wrench
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.wrench);
        for (const auto& elem : src.wrench) {
            cpp2cdr_Wrench(cdr, elem);
        }
    }
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_MultiDOFJointState(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_MultiDOFJointState& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // string sequence: joint_names
    hako::pdu::cdr::deserialize_sequence(cdr, dst.joint_names);
    // struct sequence: transforms
    {
        uint32_t length = 0;
        cdr >> length;
        dst.transforms.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_Transform(cdr, dst.transforms[i]);
        }
    }
    // struct sequence: twist
    {
        uint32_t length = 0;
        cdr >> length;
        dst.twist.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_Twist(cdr, dst.twist[i]);
        }
    }
    // struct sequence: wrench
    {
        uint32_t length = 0;
        cdr >> length;
        dst.wrench.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_Wrench(cdr, dst.wrench[i]);
        }
    }
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_MultiDOFJointState(
    const HakoCpp_MultiDOFJointState& src,
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
        cpp2cdr_MultiDOFJointState(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][MultiDOFJointState] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_MultiDOFJointState(
    const HakoCpp_MultiDOFJointState& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_MultiDOFJointState(
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
static inline bool hako_convert_cdr2cpp_MultiDOFJointState(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_MultiDOFJointState& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_MultiDOFJointState(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][MultiDOFJointState] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_MultiDOFJointState(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_MultiDOFJointState& dst)
{
    return hako_convert_cdr2cpp_MultiDOFJointState(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::sensor_msgs
{

class MultiDOFJointStateCdr
{
public:
    MultiDOFJointStateCdr() = default;
    ~MultiDOFJointStateCdr() = default;

    int cpp2cdr(
        const HakoCpp_MultiDOFJointState& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_MultiDOFJointState(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_MultiDOFJointState& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_MultiDOFJointState(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_MultiDOFJointState& cppData)
    {
        return hako_convert_cdr2cpp_MultiDOFJointState(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_MultiDOFJointState& cppData)
    {
        return hako_convert_cdr2cpp_MultiDOFJointState(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::sensor_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_MultiDOFJointState_HPP_ */
