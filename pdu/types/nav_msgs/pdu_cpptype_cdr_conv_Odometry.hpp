#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_nav_msgs_Odometry_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_nav_msgs_Odometry_HPP_

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
#include "nav_msgs/pdu_cpptype_Odometry.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_PoseWithCovariance.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_TwistWithCovariance.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Vector3.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_Odometry(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_Odometry& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // string: child_frame_id
    cdr << src.child_frame_id;
    // nested struct: pose
    cpp2cdr_PoseWithCovariance(cdr, src.pose);
    // nested struct: twist
    cpp2cdr_TwistWithCovariance(cdr, src.twist);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_Odometry(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_Odometry& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // string: child_frame_id
    cdr >> dst.child_frame_id;
    // nested struct: pose
    cdr2cpp_PoseWithCovariance(cdr, dst.pose);
    // nested struct: twist
    cdr2cpp_TwistWithCovariance(cdr, dst.twist);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_Odometry(
    const HakoCpp_Odometry& src,
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
        cpp2cdr_Odometry(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Odometry] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_Odometry(
    const HakoCpp_Odometry& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_Odometry(
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
static inline bool hako_convert_cdr2cpp_Odometry(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_Odometry& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_Odometry(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Odometry] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_Odometry(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_Odometry& dst)
{
    return hako_convert_cdr2cpp_Odometry(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::nav_msgs
{

class OdometryCdr
{
public:
    OdometryCdr() = default;
    ~OdometryCdr() = default;

    int cpp2cdr(
        const HakoCpp_Odometry& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_Odometry(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_Odometry& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_Odometry(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_Odometry& cppData)
    {
        return hako_convert_cdr2cpp_Odometry(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_Odometry& cppData)
    {
        return hako_convert_cdr2cpp_Odometry(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::nav_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_nav_msgs_Odometry_HPP_ */
