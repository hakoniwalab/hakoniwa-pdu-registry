#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_nav_msgs_MapMetaData_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_nav_msgs_MapMetaData_HPP_

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
#include "nav_msgs/pdu_cpptype_MapMetaData.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Quaternion.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_MapMetaData(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_MapMetaData& src)
{
    // nested struct: map_load_time
    cpp2cdr_Time(cdr, src.map_load_time);
    // primitive: resolution
    cdr << src.resolution;
    // primitive: width
    cdr << src.width;
    // primitive: height
    cdr << src.height;
    // nested struct: origin
    cpp2cdr_Pose(cdr, src.origin);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_MapMetaData(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_MapMetaData& dst)
{
    // nested struct: map_load_time
    cdr2cpp_Time(cdr, dst.map_load_time);
    // primitive: resolution
    cdr >> dst.resolution;
    // primitive: width
    cdr >> dst.width;
    // primitive: height
    cdr >> dst.height;
    // nested struct: origin
    cdr2cpp_Pose(cdr, dst.origin);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_MapMetaData(
    const HakoCpp_MapMetaData& src,
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
        cpp2cdr_MapMetaData(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][MapMetaData] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_MapMetaData(
    const HakoCpp_MapMetaData& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_MapMetaData(
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
static inline bool hako_convert_cdr2cpp_MapMetaData(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_MapMetaData& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_MapMetaData(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][MapMetaData] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_MapMetaData(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_MapMetaData& dst)
{
    return hako_convert_cdr2cpp_MapMetaData(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::nav_msgs
{

class MapMetaDataCdr
{
public:
    MapMetaDataCdr() = default;
    ~MapMetaDataCdr() = default;

    int cpp2cdr(
        const HakoCpp_MapMetaData& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_MapMetaData(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_MapMetaData& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_MapMetaData(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_MapMetaData& cppData)
    {
        return hako_convert_cdr2cpp_MapMetaData(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_MapMetaData& cppData)
    {
        return hako_convert_cdr2cpp_MapMetaData(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::nav_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_nav_msgs_MapMetaData_HPP_ */
