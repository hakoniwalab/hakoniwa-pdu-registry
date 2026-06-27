#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_mavlink_msgs_HakoSERVO_OUTPUT_RAW_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_mavlink_msgs_HakoSERVO_OUTPUT_RAW_HPP_

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
#include "hako_mavlink_msgs/pdu_cpptype_HakoSERVO_OUTPUT_RAW.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_HakoSERVO_OUTPUT_RAW(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_HakoSERVO_OUTPUT_RAW& src)
{
    // primitive: time_usec
    cdr << src.time_usec;
    // primitive: port
    cdr << src.port;
    // primitive: servo1_raw
    cdr << src.servo1_raw;
    // primitive: servo2_raw
    cdr << src.servo2_raw;
    // primitive: servo3_raw
    cdr << src.servo3_raw;
    // primitive: servo4_raw
    cdr << src.servo4_raw;
    // primitive: servo5_raw
    cdr << src.servo5_raw;
    // primitive: servo6_raw
    cdr << src.servo6_raw;
    // primitive: servo7_raw
    cdr << src.servo7_raw;
    // primitive: servo8_raw
    cdr << src.servo8_raw;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_HakoSERVO_OUTPUT_RAW(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_HakoSERVO_OUTPUT_RAW& dst)
{
    // primitive: time_usec
    cdr >> dst.time_usec;
    // primitive: port
    cdr >> dst.port;
    // primitive: servo1_raw
    cdr >> dst.servo1_raw;
    // primitive: servo2_raw
    cdr >> dst.servo2_raw;
    // primitive: servo3_raw
    cdr >> dst.servo3_raw;
    // primitive: servo4_raw
    cdr >> dst.servo4_raw;
    // primitive: servo5_raw
    cdr >> dst.servo5_raw;
    // primitive: servo6_raw
    cdr >> dst.servo6_raw;
    // primitive: servo7_raw
    cdr >> dst.servo7_raw;
    // primitive: servo8_raw
    cdr >> dst.servo8_raw;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_HakoSERVO_OUTPUT_RAW(
    const HakoCpp_HakoSERVO_OUTPUT_RAW& src,
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
        cpp2cdr_HakoSERVO_OUTPUT_RAW(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][HakoSERVO_OUTPUT_RAW] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_HakoSERVO_OUTPUT_RAW(
    const HakoCpp_HakoSERVO_OUTPUT_RAW& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_HakoSERVO_OUTPUT_RAW(
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
static inline bool hako_convert_cdr2cpp_HakoSERVO_OUTPUT_RAW(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_HakoSERVO_OUTPUT_RAW& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_HakoSERVO_OUTPUT_RAW(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][HakoSERVO_OUTPUT_RAW] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_HakoSERVO_OUTPUT_RAW(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_HakoSERVO_OUTPUT_RAW& dst)
{
    return hako_convert_cdr2cpp_HakoSERVO_OUTPUT_RAW(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_mavlink_msgs
{

class HakoSERVO_OUTPUT_RAWCdr
{
public:
    HakoSERVO_OUTPUT_RAWCdr() = default;
    ~HakoSERVO_OUTPUT_RAWCdr() = default;

    int cpp2cdr(
        const HakoCpp_HakoSERVO_OUTPUT_RAW& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_HakoSERVO_OUTPUT_RAW(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_HakoSERVO_OUTPUT_RAW& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_HakoSERVO_OUTPUT_RAW(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_HakoSERVO_OUTPUT_RAW& cppData)
    {
        return hako_convert_cdr2cpp_HakoSERVO_OUTPUT_RAW(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_HakoSERVO_OUTPUT_RAW& cppData)
    {
        return hako_convert_cdr2cpp_HakoSERVO_OUTPUT_RAW(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_mavlink_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_mavlink_msgs_HakoSERVO_OUTPUT_RAW_HPP_ */
