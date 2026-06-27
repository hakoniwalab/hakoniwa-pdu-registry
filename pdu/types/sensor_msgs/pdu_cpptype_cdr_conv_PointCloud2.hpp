#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_PointCloud2_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_PointCloud2_HPP_

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
#include "sensor_msgs/pdu_cpptype_PointCloud2.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "sensor_msgs/pdu_cpptype_cdr_conv_PointField.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_PointCloud2(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_PointCloud2& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // primitive: height
    cdr << src.height;
    // primitive: width
    cdr << src.width;
    // struct sequence: fields
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.fields);
        for (const auto& elem : src.fields) {
            cpp2cdr_PointField(cdr, elem);
        }
    }
    // primitive: is_bigendian
    cdr << static_cast<bool>(src.is_bigendian != 0);
    // primitive: point_step
    cdr << src.point_step;
    // primitive: row_step
    cdr << src.row_step;
    // primitive sequence: data
    hako::pdu::cdr::serialize_sequence(cdr, src.data);
    // primitive: is_dense
    cdr << static_cast<bool>(src.is_dense != 0);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_PointCloud2(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_PointCloud2& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // primitive: height
    cdr >> dst.height;
    // primitive: width
    cdr >> dst.width;
    // struct sequence: fields
    {
        uint32_t length = 0;
        cdr >> length;
        dst.fields.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_PointField(cdr, dst.fields[i]);
        }
    }
    // primitive: is_bigendian
    {
        bool value = false;
        cdr >> value;
        dst.is_bigendian = value ? 1 : 0;
    }
    // primitive: point_step
    cdr >> dst.point_step;
    // primitive: row_step
    cdr >> dst.row_step;
    // primitive sequence: data
    hako::pdu::cdr::deserialize_sequence(cdr, dst.data);
    // primitive: is_dense
    {
        bool value = false;
        cdr >> value;
        dst.is_dense = value ? 1 : 0;
    }
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_PointCloud2(
    const HakoCpp_PointCloud2& src,
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
        cpp2cdr_PointCloud2(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][PointCloud2] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_PointCloud2(
    const HakoCpp_PointCloud2& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_PointCloud2(
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
static inline bool hako_convert_cdr2cpp_PointCloud2(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_PointCloud2& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_PointCloud2(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][PointCloud2] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_PointCloud2(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_PointCloud2& dst)
{
    return hako_convert_cdr2cpp_PointCloud2(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::sensor_msgs
{

class PointCloud2Cdr
{
public:
    PointCloud2Cdr() = default;
    ~PointCloud2Cdr() = default;

    int cpp2cdr(
        const HakoCpp_PointCloud2& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_PointCloud2(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_PointCloud2& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_PointCloud2(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_PointCloud2& cppData)
    {
        return hako_convert_cdr2cpp_PointCloud2(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_PointCloud2& cppData)
    {
        return hako_convert_cdr2cpp_PointCloud2(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::sensor_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_PointCloud2_HPP_ */
