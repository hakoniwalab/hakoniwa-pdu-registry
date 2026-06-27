#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_PointCloud_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_PointCloud_HPP_

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
#include "sensor_msgs/pdu_cpptype_PointCloud.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Point32.hpp"
#include "sensor_msgs/pdu_cpptype_cdr_conv_ChannelFloat32.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_PointCloud(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_PointCloud& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // struct sequence: points
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.points);
        for (const auto& elem : src.points) {
            cpp2cdr_Point32(cdr, elem);
        }
    }
    // struct sequence: channels
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.channels);
        for (const auto& elem : src.channels) {
            cpp2cdr_ChannelFloat32(cdr, elem);
        }
    }
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_PointCloud(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_PointCloud& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // struct sequence: points
    {
        uint32_t length = 0;
        cdr >> length;
        dst.points.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_Point32(cdr, dst.points[i]);
        }
    }
    // struct sequence: channels
    {
        uint32_t length = 0;
        cdr >> length;
        dst.channels.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_ChannelFloat32(cdr, dst.channels[i]);
        }
    }
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_PointCloud(
    const HakoCpp_PointCloud& src,
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
        cpp2cdr_PointCloud(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][PointCloud] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_PointCloud(
    const HakoCpp_PointCloud& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_PointCloud(
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
static inline bool hako_convert_cdr2cpp_PointCloud(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_PointCloud& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_PointCloud(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][PointCloud] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_PointCloud(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_PointCloud& dst)
{
    return hako_convert_cdr2cpp_PointCloud(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::sensor_msgs
{

class PointCloudCdr
{
public:
    PointCloudCdr() = default;
    ~PointCloudCdr() = default;

    int cpp2cdr(
        const HakoCpp_PointCloud& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_PointCloud(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_PointCloud& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_PointCloud(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_PointCloud& cppData)
    {
        return hako_convert_cdr2cpp_PointCloud(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_PointCloud& cppData)
    {
        return hako_convert_cdr2cpp_PointCloud(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::sensor_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_PointCloud_HPP_ */
