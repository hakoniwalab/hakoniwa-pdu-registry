#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_LaserScan_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_LaserScan_HPP_

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
#include "sensor_msgs/pdu_cpptype_LaserScan.hpp"

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
static inline void cpp2cdr_LaserScan(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_LaserScan& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // primitive: angle_min
    cdr << src.angle_min;
    // primitive: angle_max
    cdr << src.angle_max;
    // primitive: angle_increment
    cdr << src.angle_increment;
    // primitive: time_increment
    cdr << src.time_increment;
    // primitive: scan_time
    cdr << src.scan_time;
    // primitive: range_min
    cdr << src.range_min;
    // primitive: range_max
    cdr << src.range_max;
    // primitive sequence: ranges
    hako::pdu::cdr::serialize_sequence(cdr, src.ranges);
    // primitive sequence: intensities
    hako::pdu::cdr::serialize_sequence(cdr, src.intensities);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_LaserScan(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_LaserScan& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // primitive: angle_min
    cdr >> dst.angle_min;
    // primitive: angle_max
    cdr >> dst.angle_max;
    // primitive: angle_increment
    cdr >> dst.angle_increment;
    // primitive: time_increment
    cdr >> dst.time_increment;
    // primitive: scan_time
    cdr >> dst.scan_time;
    // primitive: range_min
    cdr >> dst.range_min;
    // primitive: range_max
    cdr >> dst.range_max;
    // primitive sequence: ranges
    hako::pdu::cdr::deserialize_sequence(cdr, dst.ranges);
    // primitive sequence: intensities
    hako::pdu::cdr::deserialize_sequence(cdr, dst.intensities);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_LaserScan(
    const HakoCpp_LaserScan& src,
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
        cpp2cdr_LaserScan(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][LaserScan] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_LaserScan(
    const HakoCpp_LaserScan& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_LaserScan(
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
static inline bool hako_convert_cdr2cpp_LaserScan(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_LaserScan& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_LaserScan(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][LaserScan] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_LaserScan(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_LaserScan& dst)
{
    return hako_convert_cdr2cpp_LaserScan(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::sensor_msgs
{

class LaserScanCdr
{
public:
    LaserScanCdr() = default;
    ~LaserScanCdr() = default;

    int cpp2cdr(
        const HakoCpp_LaserScan& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_LaserScan(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_LaserScan& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_LaserScan(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_LaserScan& cppData)
    {
        return hako_convert_cdr2cpp_LaserScan(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_LaserScan& cppData)
    {
        return hako_convert_cdr2cpp_LaserScan(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::sensor_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_LaserScan_HPP_ */
