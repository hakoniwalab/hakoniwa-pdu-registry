#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_geometry_msgs_Transform_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_geometry_msgs_Transform_HPP_

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
#include "geometry_msgs/pdu_cpptype_Transform.hpp"

/*
 * Dependent CDR convertors
 */
#include "geometry_msgs/pdu_cpptype_cdr_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Vector3.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_Transform(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_Transform& src)
{
    // nested struct: translation
    cpp2cdr_Vector3(cdr, src.translation);
    // nested struct: rotation
    cpp2cdr_Quaternion(cdr, src.rotation);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_Transform(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_Transform& dst)
{
    // nested struct: translation
    cdr2cpp_Vector3(cdr, dst.translation);
    // nested struct: rotation
    cdr2cpp_Quaternion(cdr, dst.rotation);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_Transform(
    const HakoCpp_Transform& src,
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
        cpp2cdr_Transform(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Transform] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_Transform(
    const HakoCpp_Transform& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_Transform(
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
static inline bool hako_convert_cdr2cpp_Transform(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_Transform& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_Transform(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Transform] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_Transform(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_Transform& dst)
{
    return hako_convert_cdr2cpp_Transform(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::geometry_msgs
{

class TransformCdr
{
public:
    TransformCdr() = default;
    ~TransformCdr() = default;

    int cpp2cdr(
        const HakoCpp_Transform& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_Transform(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_Transform& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_Transform(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_Transform& cppData)
    {
        return hako_convert_cdr2cpp_Transform(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_Transform& cppData)
    {
        return hako_convert_cdr2cpp_Transform(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::geometry_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_geometry_msgs_Transform_HPP_ */
