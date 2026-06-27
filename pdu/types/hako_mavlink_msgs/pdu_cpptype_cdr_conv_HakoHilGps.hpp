#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_mavlink_msgs_HakoHilGps_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_mavlink_msgs_HakoHilGps_HPP_

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
#include "hako_mavlink_msgs/pdu_cpptype_HakoHilGps.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_HakoHilGps(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_HakoHilGps& src)
{
    // primitive: time_usec
    cdr << src.time_usec;
    // primitive: lat
    cdr << src.lat;
    // primitive: lon
    cdr << src.lon;
    // primitive: alt
    cdr << src.alt;
    // primitive: eph
    cdr << src.eph;
    // primitive: epv
    cdr << src.epv;
    // primitive: vel
    cdr << src.vel;
    // primitive: vn
    cdr << src.vn;
    // primitive: ve
    cdr << src.ve;
    // primitive: vd
    cdr << src.vd;
    // primitive: cog
    cdr << src.cog;
    // primitive: satellites_visible
    cdr << src.satellites_visible;
    // primitive: id
    cdr << src.id;
    // primitive: yaw
    cdr << src.yaw;
    // primitive: fix_type
    cdr << src.fix_type;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_HakoHilGps(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_HakoHilGps& dst)
{
    // primitive: time_usec
    cdr >> dst.time_usec;
    // primitive: lat
    cdr >> dst.lat;
    // primitive: lon
    cdr >> dst.lon;
    // primitive: alt
    cdr >> dst.alt;
    // primitive: eph
    cdr >> dst.eph;
    // primitive: epv
    cdr >> dst.epv;
    // primitive: vel
    cdr >> dst.vel;
    // primitive: vn
    cdr >> dst.vn;
    // primitive: ve
    cdr >> dst.ve;
    // primitive: vd
    cdr >> dst.vd;
    // primitive: cog
    cdr >> dst.cog;
    // primitive: satellites_visible
    cdr >> dst.satellites_visible;
    // primitive: id
    cdr >> dst.id;
    // primitive: yaw
    cdr >> dst.yaw;
    // primitive: fix_type
    cdr >> dst.fix_type;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_HakoHilGps(
    const HakoCpp_HakoHilGps& src,
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
        cpp2cdr_HakoHilGps(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][HakoHilGps] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_HakoHilGps(
    const HakoCpp_HakoHilGps& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_HakoHilGps(
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
static inline bool hako_convert_cdr2cpp_HakoHilGps(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_HakoHilGps& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_HakoHilGps(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][HakoHilGps] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_HakoHilGps(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_HakoHilGps& dst)
{
    return hako_convert_cdr2cpp_HakoHilGps(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_mavlink_msgs
{

class HakoHilGpsCdr
{
public:
    HakoHilGpsCdr() = default;
    ~HakoHilGpsCdr() = default;

    int cpp2cdr(
        const HakoCpp_HakoHilGps& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_HakoHilGps(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_HakoHilGps& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_HakoHilGps(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_HakoHilGps& cppData)
    {
        return hako_convert_cdr2cpp_HakoHilGps(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_HakoHilGps& cppData)
    {
        return hako_convert_cdr2cpp_HakoHilGps(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_mavlink_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_mavlink_msgs_HakoHilGps_HPP_ */
