#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_geometry_msgs_PoseArray_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_geometry_msgs_PoseArray_HPP_

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
#include "geometry_msgs/pdu_cpptype_PoseArray.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Quaternion.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_PoseArray(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_PoseArray& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // struct sequence: poses
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.poses);
        for (const auto& elem : src.poses) {
            cpp2cdr_Pose(cdr, elem);
        }
    }
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_PoseArray(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_PoseArray& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // struct sequence: poses
    {
        uint32_t length = 0;
        cdr >> length;
        dst.poses.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_Pose(cdr, dst.poses[i]);
        }
    }
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_PoseArray(
    const HakoCpp_PoseArray& src,
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
        cpp2cdr_PoseArray(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][PoseArray] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_PoseArray(
    const HakoCpp_PoseArray& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_PoseArray(
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
static inline bool hako_convert_cdr2cpp_PoseArray(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_PoseArray& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_PoseArray(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][PoseArray] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_PoseArray(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_PoseArray& dst)
{
    return hako_convert_cdr2cpp_PoseArray(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::geometry_msgs
{

class PoseArrayCdr
{
public:
    PoseArrayCdr() = default;
    ~PoseArrayCdr() = default;

    int cpp2cdr(
        const HakoCpp_PoseArray& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_PoseArray(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_PoseArray& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_PoseArray(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_PoseArray& cppData)
    {
        return hako_convert_cdr2cpp_PoseArray(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_PoseArray& cppData)
    {
        return hako_convert_cdr2cpp_PoseArray(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::geometry_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_geometry_msgs_PoseArray_HPP_ */
