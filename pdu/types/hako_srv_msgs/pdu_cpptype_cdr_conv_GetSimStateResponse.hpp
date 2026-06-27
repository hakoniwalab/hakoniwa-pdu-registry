#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_GetSimStateResponse_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_GetSimStateResponse_HPP_

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
#include "hako_srv_msgs/pdu_cpptype_GetSimStateResponse.hpp"

/*
 * Dependent CDR convertors
 */

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_GetSimStateResponse(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_GetSimStateResponse& src)
{
    // primitive: sim_state
    cdr << src.sim_state;
    // primitive: master_time
    cdr << src.master_time;
    // primitive: is_pdu_created
    cdr << static_cast<bool>(src.is_pdu_created != 0);
    // primitive: is_simulation_mode
    cdr << static_cast<bool>(src.is_simulation_mode != 0);
    // primitive: is_pdu_sync_mode
    cdr << static_cast<bool>(src.is_pdu_sync_mode != 0);
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_GetSimStateResponse(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_GetSimStateResponse& dst)
{
    // primitive: sim_state
    cdr >> dst.sim_state;
    // primitive: master_time
    cdr >> dst.master_time;
    // primitive: is_pdu_created
    {
        bool value = false;
        cdr >> value;
        dst.is_pdu_created = value ? 1 : 0;
    }
    // primitive: is_simulation_mode
    {
        bool value = false;
        cdr >> value;
        dst.is_simulation_mode = value ? 1 : 0;
    }
    // primitive: is_pdu_sync_mode
    {
        bool value = false;
        cdr >> value;
        dst.is_pdu_sync_mode = value ? 1 : 0;
    }
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_GetSimStateResponse(
    const HakoCpp_GetSimStateResponse& src,
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
        cpp2cdr_GetSimStateResponse(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][GetSimStateResponse] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_GetSimStateResponse(
    const HakoCpp_GetSimStateResponse& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_GetSimStateResponse(
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
static inline bool hako_convert_cdr2cpp_GetSimStateResponse(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_GetSimStateResponse& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_GetSimStateResponse(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][GetSimStateResponse] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_GetSimStateResponse(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_GetSimStateResponse& dst)
{
    return hako_convert_cdr2cpp_GetSimStateResponse(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_srv_msgs
{

class GetSimStateResponseCdr
{
public:
    GetSimStateResponseCdr() = default;
    ~GetSimStateResponseCdr() = default;

    int cpp2cdr(
        const HakoCpp_GetSimStateResponse& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_GetSimStateResponse(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_GetSimStateResponse& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_GetSimStateResponse(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_GetSimStateResponse& cppData)
    {
        return hako_convert_cdr2cpp_GetSimStateResponse(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_GetSimStateResponse& cppData)
    {
        return hako_convert_cdr2cpp_GetSimStateResponse(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_srv_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_srv_msgs_GetSimStateResponse_HPP_ */
