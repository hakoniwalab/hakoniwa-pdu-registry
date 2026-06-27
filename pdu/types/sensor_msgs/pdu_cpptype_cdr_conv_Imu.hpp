#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_Imu_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_Imu_HPP_

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
#include "sensor_msgs/pdu_cpptype_Imu.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Quaternion.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Vector3.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_Imu(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_Imu& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // nested struct: orientation
    cpp2cdr_Quaternion(cdr, src.orientation);
    // primitive fixed array: orientation_covariance[9]
    hako::pdu::cdr::serialize_fixed_array(cdr, src.orientation_covariance, 9);
    // nested struct: angular_velocity
    cpp2cdr_Vector3(cdr, src.angular_velocity);
    // primitive fixed array: angular_velocity_covariance[9]
    hako::pdu::cdr::serialize_fixed_array(cdr, src.angular_velocity_covariance, 9);
    // nested struct: linear_acceleration
    cpp2cdr_Vector3(cdr, src.linear_acceleration);
    // primitive fixed array: linear_acceleration_covariance[9]
    hako::pdu::cdr::serialize_fixed_array(cdr, src.linear_acceleration_covariance, 9);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_Imu(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_Imu& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // nested struct: orientation
    cdr2cpp_Quaternion(cdr, dst.orientation);
    // primitive fixed array: orientation_covariance[9]
    hako::pdu::cdr::deserialize_fixed_array(cdr, dst.orientation_covariance, 9);
    // nested struct: angular_velocity
    cdr2cpp_Vector3(cdr, dst.angular_velocity);
    // primitive fixed array: angular_velocity_covariance[9]
    hako::pdu::cdr::deserialize_fixed_array(cdr, dst.angular_velocity_covariance, 9);
    // nested struct: linear_acceleration
    cdr2cpp_Vector3(cdr, dst.linear_acceleration);
    // primitive fixed array: linear_acceleration_covariance[9]
    hako::pdu::cdr::deserialize_fixed_array(cdr, dst.linear_acceleration_covariance, 9);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_Imu(
    const HakoCpp_Imu& src,
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
        cpp2cdr_Imu(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Imu] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_Imu(
    const HakoCpp_Imu& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_Imu(
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
static inline bool hako_convert_cdr2cpp_Imu(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_Imu& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_Imu(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Imu] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_Imu(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_Imu& dst)
{
    return hako_convert_cdr2cpp_Imu(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::sensor_msgs
{

class ImuCdr
{
public:
    ImuCdr() = default;
    ~ImuCdr() = default;

    int cpp2cdr(
        const HakoCpp_Imu& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_Imu(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_Imu& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_Imu(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_Imu& cppData)
    {
        return hako_convert_cdr2cpp_Imu(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_Imu& cppData)
    {
        return hako_convert_cdr2cpp_Imu(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::sensor_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_Imu_HPP_ */
