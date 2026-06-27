#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_MultiEchoLaserScan_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_MultiEchoLaserScan_HPP_

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
#include "sensor_msgs/pdu_cpptype_MultiEchoLaserScan.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "sensor_msgs/pdu_cpptype_cdr_conv_LaserEcho.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_MultiEchoLaserScan(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_MultiEchoLaserScan& src)
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
    // struct sequence: ranges
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.ranges);
        for (const auto& elem : src.ranges) {
            cpp2cdr_LaserEcho(cdr, elem);
        }
    }
    // struct sequence: intensities
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.intensities);
        for (const auto& elem : src.intensities) {
            cpp2cdr_LaserEcho(cdr, elem);
        }
    }
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_MultiEchoLaserScan(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_MultiEchoLaserScan& dst)
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
    // struct sequence: ranges
    {
        uint32_t length = 0;
        cdr >> length;
        dst.ranges.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_LaserEcho(cdr, dst.ranges[i]);
        }
    }
    // struct sequence: intensities
    {
        uint32_t length = 0;
        cdr >> length;
        dst.intensities.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_LaserEcho(cdr, dst.intensities[i]);
        }
    }
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_MultiEchoLaserScan(
    const HakoCpp_MultiEchoLaserScan& src,
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
        cpp2cdr_MultiEchoLaserScan(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][MultiEchoLaserScan] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_MultiEchoLaserScan(
    const HakoCpp_MultiEchoLaserScan& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_MultiEchoLaserScan(
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
static inline bool hako_convert_cdr2cpp_MultiEchoLaserScan(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_MultiEchoLaserScan& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_MultiEchoLaserScan(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][MultiEchoLaserScan] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_MultiEchoLaserScan(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_MultiEchoLaserScan& dst)
{
    return hako_convert_cdr2cpp_MultiEchoLaserScan(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::sensor_msgs
{

class MultiEchoLaserScanCdr
{
public:
    MultiEchoLaserScanCdr() = default;
    ~MultiEchoLaserScanCdr() = default;

    int cpp2cdr(
        const HakoCpp_MultiEchoLaserScan& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_MultiEchoLaserScan(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_MultiEchoLaserScan& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_MultiEchoLaserScan(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_MultiEchoLaserScan& cppData)
    {
        return hako_convert_cdr2cpp_MultiEchoLaserScan(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_MultiEchoLaserScan& cppData)
    {
        return hako_convert_cdr2cpp_MultiEchoLaserScan(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::sensor_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_MultiEchoLaserScan_HPP_ */
