#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_NavSatFix_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_NavSatFix_HPP_

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
#include "sensor_msgs/pdu_cpptype_NavSatFix.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "sensor_msgs/pdu_cpptype_cdr_conv_NavSatStatus.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_NavSatFix(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_NavSatFix& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // nested struct: status
    cpp2cdr_NavSatStatus(cdr, src.status);
    // primitive: latitude
    cdr << src.latitude;
    // primitive: longitude
    cdr << src.longitude;
    // primitive: altitude
    cdr << src.altitude;
    // primitive fixed array: position_covariance[9]
    hako::pdu::cdr::serialize_fixed_array(cdr, src.position_covariance, 9);
    // primitive: position_covariance_type
    cdr << src.position_covariance_type;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_NavSatFix(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_NavSatFix& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // nested struct: status
    cdr2cpp_NavSatStatus(cdr, dst.status);
    // primitive: latitude
    cdr >> dst.latitude;
    // primitive: longitude
    cdr >> dst.longitude;
    // primitive: altitude
    cdr >> dst.altitude;
    // primitive fixed array: position_covariance[9]
    hako::pdu::cdr::deserialize_fixed_array(cdr, dst.position_covariance, 9);
    // primitive: position_covariance_type
    cdr >> dst.position_covariance_type;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_NavSatFix(
    const HakoCpp_NavSatFix& src,
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
        cpp2cdr_NavSatFix(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][NavSatFix] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_NavSatFix(
    const HakoCpp_NavSatFix& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_NavSatFix(
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
static inline bool hako_convert_cdr2cpp_NavSatFix(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_NavSatFix& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_NavSatFix(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][NavSatFix] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_NavSatFix(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_NavSatFix& dst)
{
    return hako_convert_cdr2cpp_NavSatFix(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::sensor_msgs
{

class NavSatFixCdr
{
public:
    NavSatFixCdr() = default;
    ~NavSatFixCdr() = default;

    int cpp2cdr(
        const HakoCpp_NavSatFix& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_NavSatFix(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_NavSatFix& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_NavSatFix(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_NavSatFix& cppData)
    {
        return hako_convert_cdr2cpp_NavSatFix(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_NavSatFix& cppData)
    {
        return hako_convert_cdr2cpp_NavSatFix(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::sensor_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_NavSatFix_HPP_ */
