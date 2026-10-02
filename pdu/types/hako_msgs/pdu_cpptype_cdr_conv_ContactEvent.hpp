#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_ContactEvent_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_ContactEvent_HPP_

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
#include "hako_msgs/pdu_cpptype_ContactEvent.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Point.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_ContactEvent(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_ContactEvent& src)
{
    // nested struct: stamp
    cpp2cdr_Time(cdr, src.stamp);
    // string: self_name
    cdr << src.self_name;
    // string: other_name
    cdr << src.other_name;
    // string: other_kind
    cdr << src.other_kind;
    // nested struct: position
    cpp2cdr_Point(cdr, src.position);
    // primitive: relative_speed
    cdr << src.relative_speed;
    // primitive: started
    cdr << static_cast<bool>(src.started != 0);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_ContactEvent(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_ContactEvent& dst)
{
    // nested struct: stamp
    cdr2cpp_Time(cdr, dst.stamp);
    // string: self_name
    cdr >> dst.self_name;
    // string: other_name
    cdr >> dst.other_name;
    // string: other_kind
    cdr >> dst.other_kind;
    // nested struct: position
    cdr2cpp_Point(cdr, dst.position);
    // primitive: relative_speed
    cdr >> dst.relative_speed;
    // primitive: started
    {
        bool value = false;
        cdr >> value;
        dst.started = value ? 1 : 0;
    }
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_ContactEvent(
    const HakoCpp_ContactEvent& src,
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
        cpp2cdr_ContactEvent(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][ContactEvent] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_ContactEvent(
    const HakoCpp_ContactEvent& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_ContactEvent(
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
static inline bool hako_convert_cdr2cpp_ContactEvent(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_ContactEvent& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_ContactEvent(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][ContactEvent] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_ContactEvent(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_ContactEvent& dst)
{
    return hako_convert_cdr2cpp_ContactEvent(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_msgs
{

class ContactEventCdr
{
public:
    ContactEventCdr() = default;
    ~ContactEventCdr() = default;

    int cpp2cdr(
        const HakoCpp_ContactEvent& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_ContactEvent(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_ContactEvent& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_ContactEvent(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_ContactEvent& cppData)
    {
        return hako_convert_cdr2cpp_ContactEvent(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_ContactEvent& cppData)
    {
        return hako_convert_cdr2cpp_ContactEvent(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_ContactEvent_HPP_ */
