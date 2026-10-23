#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_RenderCameraRequest_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_RenderCameraRequest_HPP_

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
#include "hako_srv_msgs/pdu_cpptype_RenderCameraRequest.hpp"

/*
 * Dependent CDR convertors
 */
#include "geometry_msgs/pdu_cpptype_cdr_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Quaternion.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_RenderCameraRequest(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_RenderCameraRequest& src)
{
    // string: camera_name
    cdr << src.camera_name;
    // primitive: sim_time_usec
    cdr << src.sim_time_usec;
    // nested struct: camera_pose
    cpp2cdr_Pose(cdr, src.camera_pose);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_RenderCameraRequest(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_RenderCameraRequest& dst)
{
    // string: camera_name
    cdr >> dst.camera_name;
    // primitive: sim_time_usec
    cdr >> dst.sim_time_usec;
    // nested struct: camera_pose
    cdr2cpp_Pose(cdr, dst.camera_pose);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_RenderCameraRequest(
    const HakoCpp_RenderCameraRequest& src,
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
        cpp2cdr_RenderCameraRequest(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][RenderCameraRequest] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_RenderCameraRequest(
    const HakoCpp_RenderCameraRequest& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_RenderCameraRequest(
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
static inline bool hako_convert_cdr2cpp_RenderCameraRequest(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_RenderCameraRequest& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_RenderCameraRequest(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][RenderCameraRequest] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_RenderCameraRequest(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_RenderCameraRequest& dst)
{
    return hako_convert_cdr2cpp_RenderCameraRequest(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_srv_msgs
{

class RenderCameraRequestCdr
{
public:
    RenderCameraRequestCdr() = default;
    ~RenderCameraRequestCdr() = default;

    int cpp2cdr(
        const HakoCpp_RenderCameraRequest& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_RenderCameraRequest(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_RenderCameraRequest& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_RenderCameraRequest(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_RenderCameraRequest& cppData)
    {
        return hako_convert_cdr2cpp_RenderCameraRequest(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_RenderCameraRequest& cppData)
    {
        return hako_convert_cdr2cpp_RenderCameraRequest(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_srv_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_RenderCameraRequest_HPP_ */
