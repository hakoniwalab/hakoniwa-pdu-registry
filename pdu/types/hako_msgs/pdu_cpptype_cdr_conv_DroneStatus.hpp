#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_DroneStatus_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_DroneStatus_HPP_

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
#include "hako_msgs/pdu_cpptype_DroneStatus.hpp"

/*
 * Dependent CDR convertors
 */
#include "geometry_msgs/pdu_cpptype_cdr_conv_Vector3.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_DroneStatus(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_DroneStatus& src)
{
    // primitive: flight_mode
    cdr << src.flight_mode;
    // primitive: internal_state
    cdr << src.internal_state;
    // nested struct: propeller_wind
    cpp2cdr_Vector3(cdr, src.propeller_wind);
    // primitive: collided_counts
    cdr << src.collided_counts;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_DroneStatus(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_DroneStatus& dst)
{
    // primitive: flight_mode
    cdr >> dst.flight_mode;
    // primitive: internal_state
    cdr >> dst.internal_state;
    // nested struct: propeller_wind
    cdr2cpp_Vector3(cdr, dst.propeller_wind);
    // primitive: collided_counts
    cdr >> dst.collided_counts;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_DroneStatus(
    const HakoCpp_DroneStatus& src,
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
        cpp2cdr_DroneStatus(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][DroneStatus] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_DroneStatus(
    const HakoCpp_DroneStatus& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_DroneStatus(
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
static inline bool hako_convert_cdr2cpp_DroneStatus(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_DroneStatus& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_DroneStatus(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][DroneStatus] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_DroneStatus(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_DroneStatus& dst)
{
    return hako_convert_cdr2cpp_DroneStatus(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_msgs
{

class DroneStatusCdr
{
public:
    DroneStatusCdr() = default;
    ~DroneStatusCdr() = default;

    int cpp2cdr(
        const HakoCpp_DroneStatus& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_DroneStatus(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_DroneStatus& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_DroneStatus(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_DroneStatus& cppData)
    {
        return hako_convert_cdr2cpp_DroneStatus(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_DroneStatus& cppData)
    {
        return hako_convert_cdr2cpp_DroneStatus(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_DroneStatus_HPP_ */
