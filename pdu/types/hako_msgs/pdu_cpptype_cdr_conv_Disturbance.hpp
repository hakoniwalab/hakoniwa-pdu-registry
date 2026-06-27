#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_Disturbance_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_Disturbance_HPP_

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
#include "hako_msgs/pdu_cpptype_Disturbance.hpp"

/*
 * Dependent CDR convertors
 */
#include "geometry_msgs/pdu_cpptype_cdr_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Vector3.hpp"
#include "hako_msgs/pdu_cpptype_cdr_conv_DisturbanceAtm.hpp"
#include "hako_msgs/pdu_cpptype_cdr_conv_DisturbanceBoundary.hpp"
#include "hako_msgs/pdu_cpptype_cdr_conv_DisturbanceTemperature.hpp"
#include "hako_msgs/pdu_cpptype_cdr_conv_DisturbanceUserCustom.hpp"
#include "hako_msgs/pdu_cpptype_cdr_conv_DisturbanceWind.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_Disturbance(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_Disturbance& src)
{
    // nested struct: d_temp
    cpp2cdr_DisturbanceTemperature(cdr, src.d_temp);
    // nested struct: d_wind
    cpp2cdr_DisturbanceWind(cdr, src.d_wind);
    // nested struct: d_atm
    cpp2cdr_DisturbanceAtm(cdr, src.d_atm);
    // nested struct: d_boundary
    cpp2cdr_DisturbanceBoundary(cdr, src.d_boundary);
    // struct sequence: d_user_custom
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.d_user_custom);
        for (const auto& elem : src.d_user_custom) {
            cpp2cdr_DisturbanceUserCustom(cdr, elem);
        }
    }
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_Disturbance(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_Disturbance& dst)
{
    // nested struct: d_temp
    cdr2cpp_DisturbanceTemperature(cdr, dst.d_temp);
    // nested struct: d_wind
    cdr2cpp_DisturbanceWind(cdr, dst.d_wind);
    // nested struct: d_atm
    cdr2cpp_DisturbanceAtm(cdr, dst.d_atm);
    // nested struct: d_boundary
    cdr2cpp_DisturbanceBoundary(cdr, dst.d_boundary);
    // struct sequence: d_user_custom
    {
        uint32_t length = 0;
        cdr >> length;
        dst.d_user_custom.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_DisturbanceUserCustom(cdr, dst.d_user_custom[i]);
        }
    }
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_Disturbance(
    const HakoCpp_Disturbance& src,
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
        cpp2cdr_Disturbance(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Disturbance] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_Disturbance(
    const HakoCpp_Disturbance& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_Disturbance(
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
static inline bool hako_convert_cdr2cpp_Disturbance(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_Disturbance& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_Disturbance(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Disturbance] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_Disturbance(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_Disturbance& dst)
{
    return hako_convert_cdr2cpp_Disturbance(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_msgs
{

class DisturbanceCdr
{
public:
    DisturbanceCdr() = default;
    ~DisturbanceCdr() = default;

    int cpp2cdr(
        const HakoCpp_Disturbance& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_Disturbance(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_Disturbance& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_Disturbance(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_Disturbance& cppData)
    {
        return hako_convert_cdr2cpp_Disturbance(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_Disturbance& cppData)
    {
        return hako_convert_cdr2cpp_Disturbance(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_Disturbance_HPP_ */
