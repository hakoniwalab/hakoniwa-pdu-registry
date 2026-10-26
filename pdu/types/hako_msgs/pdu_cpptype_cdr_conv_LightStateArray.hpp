#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_LightStateArray_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_LightStateArray_HPP_

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
#include "hako_msgs/pdu_cpptype_LightStateArray.hpp"

/*
 * Dependent CDR convertors
 */
#include "hako_msgs/pdu_cpptype_cdr_conv_LightState.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_LightStateArray(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_LightStateArray& src)
{
    // primitive: stamp_usec
    cdr << src.stamp_usec;
    // string: carrier
    cdr << src.carrier;
    // struct sequence: lights
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.lights);
        for (const auto& elem : src.lights) {
            cpp2cdr_LightState(cdr, elem);
        }
    }
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_LightStateArray(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_LightStateArray& dst)
{
    // primitive: stamp_usec
    cdr >> dst.stamp_usec;
    // string: carrier
    cdr >> dst.carrier;
    // struct sequence: lights
    {
        uint32_t length = 0;
        cdr >> length;
        dst.lights.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_LightState(cdr, dst.lights[i]);
        }
    }
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_LightStateArray(
    const HakoCpp_LightStateArray& src,
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
        cpp2cdr_LightStateArray(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][LightStateArray] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_LightStateArray(
    const HakoCpp_LightStateArray& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_LightStateArray(
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
static inline bool hako_convert_cdr2cpp_LightStateArray(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_LightStateArray& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_LightStateArray(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][LightStateArray] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_LightStateArray(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_LightStateArray& dst)
{
    return hako_convert_cdr2cpp_LightStateArray(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_msgs
{

class LightStateArrayCdr
{
public:
    LightStateArrayCdr() = default;
    ~LightStateArrayCdr() = default;

    int cpp2cdr(
        const HakoCpp_LightStateArray& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_LightStateArray(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_LightStateArray& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_LightStateArray(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_LightStateArray& cppData)
    {
        return hako_convert_cdr2cpp_LightStateArray(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_LightStateArray& cppData)
    {
        return hako_convert_cdr2cpp_LightStateArray(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_LightStateArray_HPP_ */
