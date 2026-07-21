#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_trajectory_msgs_MultiDOFJointTrajectoryPoint_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_trajectory_msgs_MultiDOFJointTrajectoryPoint_HPP_

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
#include "trajectory_msgs/pdu_cpptype_MultiDOFJointTrajectoryPoint.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Duration.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Transform.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Vector3.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_MultiDOFJointTrajectoryPoint(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_MultiDOFJointTrajectoryPoint& src)
{
    // struct sequence: transforms
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.transforms);
        for (const auto& elem : src.transforms) {
            cpp2cdr_Transform(cdr, elem);
        }
    }
    // struct sequence: velocities
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.velocities);
        for (const auto& elem : src.velocities) {
            cpp2cdr_Twist(cdr, elem);
        }
    }
    // struct sequence: accelerations
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.accelerations);
        for (const auto& elem : src.accelerations) {
            cpp2cdr_Twist(cdr, elem);
        }
    }
    // nested struct: time_from_start
    cpp2cdr_Duration(cdr, src.time_from_start);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_MultiDOFJointTrajectoryPoint(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_MultiDOFJointTrajectoryPoint& dst)
{
    // struct sequence: transforms
    {
        uint32_t length = 0;
        cdr >> length;
        dst.transforms.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_Transform(cdr, dst.transforms[i]);
        }
    }
    // struct sequence: velocities
    {
        uint32_t length = 0;
        cdr >> length;
        dst.velocities.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_Twist(cdr, dst.velocities[i]);
        }
    }
    // struct sequence: accelerations
    {
        uint32_t length = 0;
        cdr >> length;
        dst.accelerations.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_Twist(cdr, dst.accelerations[i]);
        }
    }
    // nested struct: time_from_start
    cdr2cpp_Duration(cdr, dst.time_from_start);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_MultiDOFJointTrajectoryPoint(
    const HakoCpp_MultiDOFJointTrajectoryPoint& src,
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
        cpp2cdr_MultiDOFJointTrajectoryPoint(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][MultiDOFJointTrajectoryPoint] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_MultiDOFJointTrajectoryPoint(
    const HakoCpp_MultiDOFJointTrajectoryPoint& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_MultiDOFJointTrajectoryPoint(
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
static inline bool hako_convert_cdr2cpp_MultiDOFJointTrajectoryPoint(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_MultiDOFJointTrajectoryPoint& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_MultiDOFJointTrajectoryPoint(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][MultiDOFJointTrajectoryPoint] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_MultiDOFJointTrajectoryPoint(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_MultiDOFJointTrajectoryPoint& dst)
{
    return hako_convert_cdr2cpp_MultiDOFJointTrajectoryPoint(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::trajectory_msgs
{

class MultiDOFJointTrajectoryPointCdr
{
public:
    MultiDOFJointTrajectoryPointCdr() = default;
    ~MultiDOFJointTrajectoryPointCdr() = default;

    int cpp2cdr(
        const HakoCpp_MultiDOFJointTrajectoryPoint& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_MultiDOFJointTrajectoryPoint(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_MultiDOFJointTrajectoryPoint& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_MultiDOFJointTrajectoryPoint(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_MultiDOFJointTrajectoryPoint& cppData)
    {
        return hako_convert_cdr2cpp_MultiDOFJointTrajectoryPoint(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_MultiDOFJointTrajectoryPoint& cppData)
    {
        return hako_convert_cdr2cpp_MultiDOFJointTrajectoryPoint(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::trajectory_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_trajectory_msgs_MultiDOFJointTrajectoryPoint_HPP_ */
