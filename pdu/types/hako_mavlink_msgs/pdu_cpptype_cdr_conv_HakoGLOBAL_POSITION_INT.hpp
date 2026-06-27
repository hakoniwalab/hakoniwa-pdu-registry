#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_mavlink_msgs_HakoGLOBAL_POSITION_INT_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_mavlink_msgs_HakoGLOBAL_POSITION_INT_HPP_

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
#include "hako_mavlink_msgs/pdu_cpptype_HakoGLOBAL_POSITION_INT.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_HakoGLOBAL_POSITION_INT(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_HakoGLOBAL_POSITION_INT& src)
{
    // primitive: time_boot_ms
    cdr << src.time_boot_ms;
    // primitive: lat
    cdr << src.lat;
    // primitive: lon
    cdr << src.lon;
    // primitive: alt
    cdr << src.alt;
    // primitive: relative_alt
    cdr << src.relative_alt;
    // primitive: vx
    cdr << src.vx;
    // primitive: vy
    cdr << src.vy;
    // primitive: vz
    cdr << src.vz;
    // primitive: hdg
    cdr << src.hdg;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_HakoGLOBAL_POSITION_INT(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_HakoGLOBAL_POSITION_INT& dst)
{
    // primitive: time_boot_ms
    cdr >> dst.time_boot_ms;
    // primitive: lat
    cdr >> dst.lat;
    // primitive: lon
    cdr >> dst.lon;
    // primitive: alt
    cdr >> dst.alt;
    // primitive: relative_alt
    cdr >> dst.relative_alt;
    // primitive: vx
    cdr >> dst.vx;
    // primitive: vy
    cdr >> dst.vy;
    // primitive: vz
    cdr >> dst.vz;
    // primitive: hdg
    cdr >> dst.hdg;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_HakoGLOBAL_POSITION_INT(
    const HakoCpp_HakoGLOBAL_POSITION_INT& src,
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
        cpp2cdr_HakoGLOBAL_POSITION_INT(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][HakoGLOBAL_POSITION_INT] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_HakoGLOBAL_POSITION_INT(
    const HakoCpp_HakoGLOBAL_POSITION_INT& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_HakoGLOBAL_POSITION_INT(
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
static inline bool hako_convert_cdr2cpp_HakoGLOBAL_POSITION_INT(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_HakoGLOBAL_POSITION_INT& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_HakoGLOBAL_POSITION_INT(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][HakoGLOBAL_POSITION_INT] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_HakoGLOBAL_POSITION_INT(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_HakoGLOBAL_POSITION_INT& dst)
{
    return hako_convert_cdr2cpp_HakoGLOBAL_POSITION_INT(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_mavlink_msgs
{

class HakoGLOBAL_POSITION_INTCdr
{
public:
    HakoGLOBAL_POSITION_INTCdr() = default;
    ~HakoGLOBAL_POSITION_INTCdr() = default;

    int cpp2cdr(
        const HakoCpp_HakoGLOBAL_POSITION_INT& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_HakoGLOBAL_POSITION_INT(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_HakoGLOBAL_POSITION_INT& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_HakoGLOBAL_POSITION_INT(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_HakoGLOBAL_POSITION_INT& cppData)
    {
        return hako_convert_cdr2cpp_HakoGLOBAL_POSITION_INT(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_HakoGLOBAL_POSITION_INT& cppData)
    {
        return hako_convert_cdr2cpp_HakoGLOBAL_POSITION_INT(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_mavlink_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_mavlink_msgs_HakoGLOBAL_POSITION_INT_HPP_ */
