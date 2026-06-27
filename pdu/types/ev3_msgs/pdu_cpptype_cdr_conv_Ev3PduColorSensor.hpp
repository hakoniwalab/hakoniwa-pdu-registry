#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_ev3_msgs_Ev3PduColorSensor_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_ev3_msgs_Ev3PduColorSensor_HPP_

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
#include "ev3_msgs/pdu_cpptype_Ev3PduColorSensor.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_Ev3PduColorSensor(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_Ev3PduColorSensor& src)
{
    // primitive: color
    cdr << src.color;
    // primitive: reflect
    cdr << src.reflect;
    // primitive: rgb_r
    cdr << src.rgb_r;
    // primitive: rgb_g
    cdr << src.rgb_g;
    // primitive: rgb_b
    cdr << src.rgb_b;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_Ev3PduColorSensor(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_Ev3PduColorSensor& dst)
{
    // primitive: color
    cdr >> dst.color;
    // primitive: reflect
    cdr >> dst.reflect;
    // primitive: rgb_r
    cdr >> dst.rgb_r;
    // primitive: rgb_g
    cdr >> dst.rgb_g;
    // primitive: rgb_b
    cdr >> dst.rgb_b;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_Ev3PduColorSensor(
    const HakoCpp_Ev3PduColorSensor& src,
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
        cpp2cdr_Ev3PduColorSensor(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Ev3PduColorSensor] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_Ev3PduColorSensor(
    const HakoCpp_Ev3PduColorSensor& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_Ev3PduColorSensor(
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
static inline bool hako_convert_cdr2cpp_Ev3PduColorSensor(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_Ev3PduColorSensor& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_Ev3PduColorSensor(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Ev3PduColorSensor] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_Ev3PduColorSensor(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_Ev3PduColorSensor& dst)
{
    return hako_convert_cdr2cpp_Ev3PduColorSensor(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::ev3_msgs
{

class Ev3PduColorSensorCdr
{
public:
    Ev3PduColorSensorCdr() = default;
    ~Ev3PduColorSensorCdr() = default;

    int cpp2cdr(
        const HakoCpp_Ev3PduColorSensor& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_Ev3PduColorSensor(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_Ev3PduColorSensor& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_Ev3PduColorSensor(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_Ev3PduColorSensor& cppData)
    {
        return hako_convert_cdr2cpp_Ev3PduColorSensor(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_Ev3PduColorSensor& cppData)
    {
        return hako_convert_cdr2cpp_Ev3PduColorSensor(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::ev3_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_ev3_msgs_Ev3PduColorSensor_HPP_ */
