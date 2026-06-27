#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_mavros_msgs_GlobalPositionTarget_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_mavros_msgs_GlobalPositionTarget_HPP_

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
#include "mavros_msgs/pdu_cpptype_GlobalPositionTarget.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Vector3.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_GlobalPositionTarget(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_GlobalPositionTarget& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // primitive: coordinate_frame
    cdr << src.coordinate_frame;
    // primitive: type_mask
    cdr << src.type_mask;
    // primitive: latitude
    cdr << src.latitude;
    // primitive: longitude
    cdr << src.longitude;
    // primitive: altitude
    cdr << src.altitude;
    // nested struct: velocity
    cpp2cdr_Vector3(cdr, src.velocity);
    // nested struct: acceleration_or_force
    cpp2cdr_Vector3(cdr, src.acceleration_or_force);
    // primitive: yaw
    cdr << src.yaw;
    // primitive: yaw_rate
    cdr << src.yaw_rate;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_GlobalPositionTarget(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_GlobalPositionTarget& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // primitive: coordinate_frame
    cdr >> dst.coordinate_frame;
    // primitive: type_mask
    cdr >> dst.type_mask;
    // primitive: latitude
    cdr >> dst.latitude;
    // primitive: longitude
    cdr >> dst.longitude;
    // primitive: altitude
    cdr >> dst.altitude;
    // nested struct: velocity
    cdr2cpp_Vector3(cdr, dst.velocity);
    // nested struct: acceleration_or_force
    cdr2cpp_Vector3(cdr, dst.acceleration_or_force);
    // primitive: yaw
    cdr >> dst.yaw;
    // primitive: yaw_rate
    cdr >> dst.yaw_rate;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_GlobalPositionTarget(
    const HakoCpp_GlobalPositionTarget& src,
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
        cpp2cdr_GlobalPositionTarget(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][GlobalPositionTarget] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_GlobalPositionTarget(
    const HakoCpp_GlobalPositionTarget& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_GlobalPositionTarget(
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
static inline bool hako_convert_cdr2cpp_GlobalPositionTarget(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_GlobalPositionTarget& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_GlobalPositionTarget(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][GlobalPositionTarget] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_GlobalPositionTarget(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_GlobalPositionTarget& dst)
{
    return hako_convert_cdr2cpp_GlobalPositionTarget(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::mavros_msgs
{

class GlobalPositionTargetCdr
{
public:
    GlobalPositionTargetCdr() = default;
    ~GlobalPositionTargetCdr() = default;

    int cpp2cdr(
        const HakoCpp_GlobalPositionTarget& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_GlobalPositionTarget(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_GlobalPositionTarget& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_GlobalPositionTarget(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_GlobalPositionTarget& cppData)
    {
        return hako_convert_cdr2cpp_GlobalPositionTarget(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_GlobalPositionTarget& cppData)
    {
        return hako_convert_cdr2cpp_GlobalPositionTarget(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::mavros_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_mavros_msgs_GlobalPositionTarget_HPP_ */
