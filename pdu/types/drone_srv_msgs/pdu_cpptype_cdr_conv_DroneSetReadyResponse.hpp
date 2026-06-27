#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_drone_srv_msgs_DroneSetReadyResponse_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_drone_srv_msgs_DroneSetReadyResponse_HPP_

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
#include "drone_srv_msgs/pdu_cpptype_DroneSetReadyResponse.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_DroneSetReadyResponse(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_DroneSetReadyResponse& src)
{
    // primitive: ok
    cdr << static_cast<bool>(src.ok != 0);
    // string: message
    cdr << src.message;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_DroneSetReadyResponse(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_DroneSetReadyResponse& dst)
{
    // primitive: ok
    {
        bool value = false;
        cdr >> value;
        dst.ok = value ? 1 : 0;
    }
    // string: message
    cdr >> dst.message;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_DroneSetReadyResponse(
    const HakoCpp_DroneSetReadyResponse& src,
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
        cpp2cdr_DroneSetReadyResponse(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][DroneSetReadyResponse] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_DroneSetReadyResponse(
    const HakoCpp_DroneSetReadyResponse& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_DroneSetReadyResponse(
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
static inline bool hako_convert_cdr2cpp_DroneSetReadyResponse(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_DroneSetReadyResponse& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_DroneSetReadyResponse(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][DroneSetReadyResponse] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_DroneSetReadyResponse(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_DroneSetReadyResponse& dst)
{
    return hako_convert_cdr2cpp_DroneSetReadyResponse(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::drone_srv_msgs
{

class DroneSetReadyResponseCdr
{
public:
    DroneSetReadyResponseCdr() = default;
    ~DroneSetReadyResponseCdr() = default;

    int cpp2cdr(
        const HakoCpp_DroneSetReadyResponse& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_DroneSetReadyResponse(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_DroneSetReadyResponse& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_DroneSetReadyResponse(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_DroneSetReadyResponse& cppData)
    {
        return hako_convert_cdr2cpp_DroneSetReadyResponse(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_DroneSetReadyResponse& cppData)
    {
        return hako_convert_cdr2cpp_DroneSetReadyResponse(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::drone_srv_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_drone_srv_msgs_DroneSetReadyResponse_HPP_ */
