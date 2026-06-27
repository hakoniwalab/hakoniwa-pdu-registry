#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_CameraInfo_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_CameraInfo_HPP_

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
#include "sensor_msgs/pdu_cpptype_CameraInfo.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "sensor_msgs/pdu_cpptype_cdr_conv_RegionOfInterest.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_CameraInfo(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_CameraInfo& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // primitive: height
    cdr << src.height;
    // primitive: width
    cdr << src.width;
    // string: distortion_model
    cdr << src.distortion_model;
    // primitive sequence: d
    hako::pdu::cdr::serialize_sequence(cdr, src.d);
    // primitive fixed array: k[9]
    hako::pdu::cdr::serialize_fixed_array(cdr, src.k, 9);
    // primitive fixed array: r[9]
    hako::pdu::cdr::serialize_fixed_array(cdr, src.r, 9);
    // primitive fixed array: p[12]
    hako::pdu::cdr::serialize_fixed_array(cdr, src.p, 12);
    // primitive: binning_x
    cdr << src.binning_x;
    // primitive: binning_y
    cdr << src.binning_y;
    // nested struct: roi
    cpp2cdr_RegionOfInterest(cdr, src.roi);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_CameraInfo(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_CameraInfo& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // primitive: height
    cdr >> dst.height;
    // primitive: width
    cdr >> dst.width;
    // string: distortion_model
    cdr >> dst.distortion_model;
    // primitive sequence: d
    hako::pdu::cdr::deserialize_sequence(cdr, dst.d);
    // primitive fixed array: k[9]
    hako::pdu::cdr::deserialize_fixed_array(cdr, dst.k, 9);
    // primitive fixed array: r[9]
    hako::pdu::cdr::deserialize_fixed_array(cdr, dst.r, 9);
    // primitive fixed array: p[12]
    hako::pdu::cdr::deserialize_fixed_array(cdr, dst.p, 12);
    // primitive: binning_x
    cdr >> dst.binning_x;
    // primitive: binning_y
    cdr >> dst.binning_y;
    // nested struct: roi
    cdr2cpp_RegionOfInterest(cdr, dst.roi);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_CameraInfo(
    const HakoCpp_CameraInfo& src,
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
        cpp2cdr_CameraInfo(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][CameraInfo] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_CameraInfo(
    const HakoCpp_CameraInfo& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_CameraInfo(
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
static inline bool hako_convert_cdr2cpp_CameraInfo(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_CameraInfo& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_CameraInfo(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][CameraInfo] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_CameraInfo(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_CameraInfo& dst)
{
    return hako_convert_cdr2cpp_CameraInfo(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::sensor_msgs
{

class CameraInfoCdr
{
public:
    CameraInfoCdr() = default;
    ~CameraInfoCdr() = default;

    int cpp2cdr(
        const HakoCpp_CameraInfo& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_CameraInfo(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_CameraInfo& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_CameraInfo(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_CameraInfo& cppData)
    {
        return hako_convert_cdr2cpp_CameraInfo(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_CameraInfo& cppData)
    {
        return hako_convert_cdr2cpp_CameraInfo(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::sensor_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_CameraInfo_HPP_ */
