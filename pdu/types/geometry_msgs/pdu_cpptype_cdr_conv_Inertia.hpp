#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_geometry_msgs_Inertia_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_geometry_msgs_Inertia_HPP_

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
#include "geometry_msgs/pdu_cpptype_Inertia.hpp"

/*
 * Dependent CDR convertors
 */
#include "geometry_msgs/pdu_cpptype_cdr_conv_Vector3.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_Inertia(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_Inertia& src)
{
    // primitive: m
    cdr << src.m;
    // nested struct: com
    cpp2cdr_Vector3(cdr, src.com);
    // primitive: ixx
    cdr << src.ixx;
    // primitive: ixy
    cdr << src.ixy;
    // primitive: ixz
    cdr << src.ixz;
    // primitive: iyy
    cdr << src.iyy;
    // primitive: iyz
    cdr << src.iyz;
    // primitive: izz
    cdr << src.izz;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_Inertia(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_Inertia& dst)
{
    // primitive: m
    cdr >> dst.m;
    // nested struct: com
    cdr2cpp_Vector3(cdr, dst.com);
    // primitive: ixx
    cdr >> dst.ixx;
    // primitive: ixy
    cdr >> dst.ixy;
    // primitive: ixz
    cdr >> dst.ixz;
    // primitive: iyy
    cdr >> dst.iyy;
    // primitive: iyz
    cdr >> dst.iyz;
    // primitive: izz
    cdr >> dst.izz;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_Inertia(
    const HakoCpp_Inertia& src,
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
        cpp2cdr_Inertia(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Inertia] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_Inertia(
    const HakoCpp_Inertia& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_Inertia(
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
static inline bool hako_convert_cdr2cpp_Inertia(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_Inertia& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_Inertia(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Inertia] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_Inertia(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_Inertia& dst)
{
    return hako_convert_cdr2cpp_Inertia(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::geometry_msgs
{

class InertiaCdr
{
public:
    InertiaCdr() = default;
    ~InertiaCdr() = default;

    int cpp2cdr(
        const HakoCpp_Inertia& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_Inertia(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_Inertia& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_Inertia(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_Inertia& cppData)
    {
        return hako_convert_cdr2cpp_Inertia(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_Inertia& cppData)
    {
        return hako_convert_cdr2cpp_Inertia(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::geometry_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_geometry_msgs_Inertia_HPP_ */
