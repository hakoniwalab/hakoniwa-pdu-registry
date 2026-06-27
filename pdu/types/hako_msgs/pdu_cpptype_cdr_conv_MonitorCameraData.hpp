#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_MonitorCameraData_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_MonitorCameraData_HPP_

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
#include "hako_msgs/pdu_cpptype_MonitorCameraData.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "sensor_msgs/pdu_cpptype_cdr_conv_CompressedImage.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_MonitorCameraData(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_MonitorCameraData& src)
{
    // primitive: request_id
    cdr << src.request_id;
    // primitive: image_data_length
    cdr << src.image_data_length;
    // nested struct: image
    cpp2cdr_CompressedImage(cdr, src.image);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_MonitorCameraData(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_MonitorCameraData& dst)
{
    // primitive: request_id
    cdr >> dst.request_id;
    // primitive: image_data_length
    cdr >> dst.image_data_length;
    // nested struct: image
    cdr2cpp_CompressedImage(cdr, dst.image);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_MonitorCameraData(
    const HakoCpp_MonitorCameraData& src,
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
        cpp2cdr_MonitorCameraData(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][MonitorCameraData] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_MonitorCameraData(
    const HakoCpp_MonitorCameraData& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_MonitorCameraData(
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
static inline bool hako_convert_cdr2cpp_MonitorCameraData(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_MonitorCameraData& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_MonitorCameraData(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][MonitorCameraData] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_MonitorCameraData(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_MonitorCameraData& dst)
{
    return hako_convert_cdr2cpp_MonitorCameraData(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_msgs
{

class MonitorCameraDataCdr
{
public:
    MonitorCameraDataCdr() = default;
    ~MonitorCameraDataCdr() = default;

    int cpp2cdr(
        const HakoCpp_MonitorCameraData& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_MonitorCameraData(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_MonitorCameraData& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_MonitorCameraData(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_MonitorCameraData& cppData)
    {
        return hako_convert_cdr2cpp_MonitorCameraData(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_MonitorCameraData& cppData)
    {
        return hako_convert_cdr2cpp_MonitorCameraData(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_MonitorCameraData_HPP_ */
