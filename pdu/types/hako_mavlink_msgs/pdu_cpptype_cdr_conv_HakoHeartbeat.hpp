#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_mavlink_msgs_HakoHeartbeat_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_mavlink_msgs_HakoHeartbeat_HPP_

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
#include "hako_mavlink_msgs/pdu_cpptype_HakoHeartbeat.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_HakoHeartbeat(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_HakoHeartbeat& src)
{
    // primitive: type
    cdr << src.type;
    // primitive: autopilot
    cdr << src.autopilot;
    // primitive: base_mode
    cdr << src.base_mode;
    // primitive: custom_mode
    cdr << src.custom_mode;
    // primitive: system_status
    cdr << src.system_status;
    // primitive: mavlink_version
    cdr << src.mavlink_version;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_HakoHeartbeat(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_HakoHeartbeat& dst)
{
    // primitive: type
    cdr >> dst.type;
    // primitive: autopilot
    cdr >> dst.autopilot;
    // primitive: base_mode
    cdr >> dst.base_mode;
    // primitive: custom_mode
    cdr >> dst.custom_mode;
    // primitive: system_status
    cdr >> dst.system_status;
    // primitive: mavlink_version
    cdr >> dst.mavlink_version;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_HakoHeartbeat(
    const HakoCpp_HakoHeartbeat& src,
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
        cpp2cdr_HakoHeartbeat(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][HakoHeartbeat] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_HakoHeartbeat(
    const HakoCpp_HakoHeartbeat& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_HakoHeartbeat(
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
static inline bool hako_convert_cdr2cpp_HakoHeartbeat(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_HakoHeartbeat& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_HakoHeartbeat(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][HakoHeartbeat] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_HakoHeartbeat(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_HakoHeartbeat& dst)
{
    return hako_convert_cdr2cpp_HakoHeartbeat(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_mavlink_msgs
{

class HakoHeartbeatCdr
{
public:
    HakoHeartbeatCdr() = default;
    ~HakoHeartbeatCdr() = default;

    int cpp2cdr(
        const HakoCpp_HakoHeartbeat& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_HakoHeartbeat(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_HakoHeartbeat& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_HakoHeartbeat(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_HakoHeartbeat& cppData)
    {
        return hako_convert_cdr2cpp_HakoHeartbeat(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_HakoHeartbeat& cppData)
    {
        return hako_convert_cdr2cpp_HakoHeartbeat(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_mavlink_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_mavlink_msgs_HakoHeartbeat_HPP_ */
