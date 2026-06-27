#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_drone_srv_msgs_DroneGetStateResponse_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_drone_srv_msgs_DroneGetStateResponse_HPP_

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
#include "drone_srv_msgs/pdu_cpptype_DroneGetStateResponse.hpp"

/*
 * Dependent CDR convertors
 */
#include "geometry_msgs/pdu_cpptype_cdr_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Quaternion.hpp"
#include "hako_msgs/pdu_cpptype_cdr_conv_HakoBatteryStatus.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_DroneGetStateResponse(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_DroneGetStateResponse& src)
{
    // primitive: ok
    cdr << static_cast<bool>(src.ok != 0);
    // primitive: is_ready
    cdr << static_cast<bool>(src.is_ready != 0);
    // nested struct: current_pose
    cpp2cdr_Pose(cdr, src.current_pose);
    // nested struct: battery_status
    cpp2cdr_HakoBatteryStatus(cdr, src.battery_status);
    // string: mode
    cdr << src.mode;
    // string: message
    cdr << src.message;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_DroneGetStateResponse(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_DroneGetStateResponse& dst)
{
    // primitive: ok
    {
        bool value = false;
        cdr >> value;
        dst.ok = value ? 1 : 0;
    }
    // primitive: is_ready
    {
        bool value = false;
        cdr >> value;
        dst.is_ready = value ? 1 : 0;
    }
    // nested struct: current_pose
    cdr2cpp_Pose(cdr, dst.current_pose);
    // nested struct: battery_status
    cdr2cpp_HakoBatteryStatus(cdr, dst.battery_status);
    // string: mode
    cdr >> dst.mode;
    // string: message
    cdr >> dst.message;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_DroneGetStateResponse(
    const HakoCpp_DroneGetStateResponse& src,
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
        cpp2cdr_DroneGetStateResponse(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][DroneGetStateResponse] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_DroneGetStateResponse(
    const HakoCpp_DroneGetStateResponse& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_DroneGetStateResponse(
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
static inline bool hako_convert_cdr2cpp_DroneGetStateResponse(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_DroneGetStateResponse& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_DroneGetStateResponse(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][DroneGetStateResponse] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_DroneGetStateResponse(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_DroneGetStateResponse& dst)
{
    return hako_convert_cdr2cpp_DroneGetStateResponse(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::drone_srv_msgs
{

class DroneGetStateResponseCdr
{
public:
    DroneGetStateResponseCdr() = default;
    ~DroneGetStateResponseCdr() = default;

    int cpp2cdr(
        const HakoCpp_DroneGetStateResponse& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_DroneGetStateResponse(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_DroneGetStateResponse& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_DroneGetStateResponse(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_DroneGetStateResponse& cppData)
    {
        return hako_convert_cdr2cpp_DroneGetStateResponse(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_DroneGetStateResponse& cppData)
    {
        return hako_convert_cdr2cpp_DroneGetStateResponse(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::drone_srv_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_drone_srv_msgs_DroneGetStateResponse_HPP_ */
