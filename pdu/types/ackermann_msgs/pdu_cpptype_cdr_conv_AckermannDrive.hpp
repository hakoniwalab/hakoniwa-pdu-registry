#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_ackermann_msgs_AckermannDrive_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_ackermann_msgs_AckermannDrive_HPP_

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
#include "ackermann_msgs/pdu_cpptype_AckermannDrive.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_AckermannDrive(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_AckermannDrive& src)
{
    // primitive: steering_angle
    cdr << src.steering_angle;
    // primitive: steering_angle_velocity
    cdr << src.steering_angle_velocity;
    // primitive: speed
    cdr << src.speed;
    // primitive: acceleration
    cdr << src.acceleration;
    // primitive: jerk
    cdr << src.jerk;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_AckermannDrive(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_AckermannDrive& dst)
{
    // primitive: steering_angle
    cdr >> dst.steering_angle;
    // primitive: steering_angle_velocity
    cdr >> dst.steering_angle_velocity;
    // primitive: speed
    cdr >> dst.speed;
    // primitive: acceleration
    cdr >> dst.acceleration;
    // primitive: jerk
    cdr >> dst.jerk;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_AckermannDrive(
    const HakoCpp_AckermannDrive& src,
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
        cpp2cdr_AckermannDrive(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][AckermannDrive] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_AckermannDrive(
    const HakoCpp_AckermannDrive& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_AckermannDrive(
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
static inline bool hako_convert_cdr2cpp_AckermannDrive(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_AckermannDrive& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_AckermannDrive(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][AckermannDrive] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_AckermannDrive(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_AckermannDrive& dst)
{
    return hako_convert_cdr2cpp_AckermannDrive(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::ackermann_msgs
{

class AckermannDriveCdr
{
public:
    AckermannDriveCdr() = default;
    ~AckermannDriveCdr() = default;

    int cpp2cdr(
        const HakoCpp_AckermannDrive& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_AckermannDrive(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_AckermannDrive& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_AckermannDrive(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_AckermannDrive& cppData)
    {
        return hako_convert_cdr2cpp_AckermannDrive(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_AckermannDrive& cppData)
    {
        return hako_convert_cdr2cpp_AckermannDrive(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::ackermann_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_ackermann_msgs_AckermannDrive_HPP_ */
