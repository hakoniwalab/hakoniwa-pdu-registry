#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_DroneVisualState_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_DroneVisualState_HPP_

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
#include "hako_msgs/pdu_cpptype_DroneVisualState.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_DroneVisualState(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_DroneVisualState& src)
{
    // primitive: x
    cdr << src.x;
    // primitive: y
    cdr << src.y;
    // primitive: z
    cdr << src.z;
    // primitive: roll
    cdr << src.roll;
    // primitive: pitch
    cdr << src.pitch;
    // primitive: yaw
    cdr << src.yaw;
    // primitive sequence: pwm_duty
    hako::pdu::cdr::serialize_sequence(cdr, src.pwm_duty);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_DroneVisualState(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_DroneVisualState& dst)
{
    // primitive: x
    cdr >> dst.x;
    // primitive: y
    cdr >> dst.y;
    // primitive: z
    cdr >> dst.z;
    // primitive: roll
    cdr >> dst.roll;
    // primitive: pitch
    cdr >> dst.pitch;
    // primitive: yaw
    cdr >> dst.yaw;
    // primitive sequence: pwm_duty
    hako::pdu::cdr::deserialize_sequence(cdr, dst.pwm_duty);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_DroneVisualState(
    const HakoCpp_DroneVisualState& src,
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
        cpp2cdr_DroneVisualState(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][DroneVisualState] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_DroneVisualState(
    const HakoCpp_DroneVisualState& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_DroneVisualState(
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
static inline bool hako_convert_cdr2cpp_DroneVisualState(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_DroneVisualState& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_DroneVisualState(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][DroneVisualState] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_DroneVisualState(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_DroneVisualState& dst)
{
    return hako_convert_cdr2cpp_DroneVisualState(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_msgs
{

class DroneVisualStateCdr
{
public:
    DroneVisualStateCdr() = default;
    ~DroneVisualStateCdr() = default;

    int cpp2cdr(
        const HakoCpp_DroneVisualState& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_DroneVisualState(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_DroneVisualState& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_DroneVisualState(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_DroneVisualState& cppData)
    {
        return hako_convert_cdr2cpp_DroneVisualState(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_DroneVisualState& cppData)
    {
        return hako_convert_cdr2cpp_DroneVisualState(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_DroneVisualState_HPP_ */
