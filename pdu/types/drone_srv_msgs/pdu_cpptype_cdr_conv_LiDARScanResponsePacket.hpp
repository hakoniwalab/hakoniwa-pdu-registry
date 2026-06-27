#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_drone_srv_msgs_LiDARScanResponsePacket_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_drone_srv_msgs_LiDARScanResponsePacket_HPP_

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
#include "drone_srv_msgs/pdu_cpptype_LiDARScanResponsePacket.hpp"

/*
 * Dependent CDR convertors
 */
#include "builtin_interfaces/pdu_cpptype_cdr_conv_Time.hpp"
#include "drone_srv_msgs/pdu_cpptype_cdr_conv_LiDARScanResponse.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Pose.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Quaternion.hpp"
#include "hako_srv_msgs/pdu_cpptype_cdr_conv_ServiceResponseHeader.hpp"
#include "sensor_msgs/pdu_cpptype_cdr_conv_PointCloud2.hpp"
#include "sensor_msgs/pdu_cpptype_cdr_conv_PointField.hpp"
#include "std_msgs/pdu_cpptype_cdr_conv_Header.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_LiDARScanResponsePacket(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_LiDARScanResponsePacket& src)
{
    // nested struct: header
    cpp2cdr_ServiceResponseHeader(cdr, src.header);
    // nested struct: body
    cpp2cdr_LiDARScanResponse(cdr, src.body);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_LiDARScanResponsePacket(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_LiDARScanResponsePacket& dst)
{
    // nested struct: header
    cdr2cpp_ServiceResponseHeader(cdr, dst.header);
    // nested struct: body
    cdr2cpp_LiDARScanResponse(cdr, dst.body);
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_LiDARScanResponsePacket(
    const HakoCpp_LiDARScanResponsePacket& src,
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
        cpp2cdr_LiDARScanResponsePacket(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][LiDARScanResponsePacket] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_LiDARScanResponsePacket(
    const HakoCpp_LiDARScanResponsePacket& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_LiDARScanResponsePacket(
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
static inline bool hako_convert_cdr2cpp_LiDARScanResponsePacket(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_LiDARScanResponsePacket& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_LiDARScanResponsePacket(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][LiDARScanResponsePacket] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_LiDARScanResponsePacket(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_LiDARScanResponsePacket& dst)
{
    return hako_convert_cdr2cpp_LiDARScanResponsePacket(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::drone_srv_msgs
{

class LiDARScanResponsePacketCdr
{
public:
    LiDARScanResponsePacketCdr() = default;
    ~LiDARScanResponsePacketCdr() = default;

    int cpp2cdr(
        const HakoCpp_LiDARScanResponsePacket& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_LiDARScanResponsePacket(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_LiDARScanResponsePacket& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_LiDARScanResponsePacket(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_LiDARScanResponsePacket& cppData)
    {
        return hako_convert_cdr2cpp_LiDARScanResponsePacket(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_LiDARScanResponsePacket& cppData)
    {
        return hako_convert_cdr2cpp_LiDARScanResponsePacket(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::drone_srv_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_drone_srv_msgs_LiDARScanResponsePacket_HPP_ */
