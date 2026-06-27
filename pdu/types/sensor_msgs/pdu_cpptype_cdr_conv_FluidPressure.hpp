#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_FluidPressure_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_FluidPressure_HPP_

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
#include "sensor_msgs/pdu_cpptype_FluidPressure.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_FluidPressure(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_FluidPressure& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // primitive: fluid_pressure
    cdr << src.fluid_pressure;
    // primitive: variance
    cdr << src.variance;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_FluidPressure(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_FluidPressure& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // primitive: fluid_pressure
    cdr >> dst.fluid_pressure;
    // primitive: variance
    cdr >> dst.variance;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_FluidPressure(
    const HakoCpp_FluidPressure& src,
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
        cpp2cdr_FluidPressure(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][FluidPressure] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_FluidPressure(
    const HakoCpp_FluidPressure& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_FluidPressure(
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
static inline bool hako_convert_cdr2cpp_FluidPressure(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_FluidPressure& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_FluidPressure(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][FluidPressure] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_FluidPressure(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_FluidPressure& dst)
{
    return hako_convert_cdr2cpp_FluidPressure(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::sensor_msgs
{

class FluidPressureCdr
{
public:
    FluidPressureCdr() = default;
    ~FluidPressureCdr() = default;

    int cpp2cdr(
        const HakoCpp_FluidPressure& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_FluidPressure(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_FluidPressure& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_FluidPressure(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_FluidPressure& cppData)
    {
        return hako_convert_cdr2cpp_FluidPressure(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_FluidPressure& cppData)
    {
        return hako_convert_cdr2cpp_FluidPressure(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::sensor_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_FluidPressure_HPP_ */
