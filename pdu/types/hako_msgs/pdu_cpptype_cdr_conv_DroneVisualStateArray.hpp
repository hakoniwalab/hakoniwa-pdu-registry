#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_DroneVisualStateArray_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_DroneVisualStateArray_HPP_

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
#include "hako_msgs/pdu_cpptype_DroneVisualStateArray.hpp"

/*
 * Dependent CDR convertors
 */
#include "hako_msgs/pdu_cpptype_cdr_conv_DroneVisualState.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_DroneVisualStateArray(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_DroneVisualStateArray& src)
{
    // primitive: sequence_id
    cdr << src.sequence_id;
    // primitive: chunk_index
    cdr << src.chunk_index;
    // primitive: chunk_count
    cdr << src.chunk_count;
    // primitive: start_index
    cdr << src.start_index;
    // primitive: valid_count
    cdr << src.valid_count;
    // struct sequence: drones
    {
        hako::pdu::cdr::serialize_sequence_length(cdr, src.drones);
        for (const auto& elem : src.drones) {
            cpp2cdr_DroneVisualState(cdr, elem);
        }
    }
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_DroneVisualStateArray(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_DroneVisualStateArray& dst)
{
    // primitive: sequence_id
    cdr >> dst.sequence_id;
    // primitive: chunk_index
    cdr >> dst.chunk_index;
    // primitive: chunk_count
    cdr >> dst.chunk_count;
    // primitive: start_index
    cdr >> dst.start_index;
    // primitive: valid_count
    cdr >> dst.valid_count;
    // struct sequence: drones
    {
        uint32_t length = 0;
        cdr >> length;
        dst.drones.resize(length);
        for (uint32_t i = 0; i < length; ++i) {
            cdr2cpp_DroneVisualState(cdr, dst.drones[i]);
        }
    }
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_DroneVisualStateArray(
    const HakoCpp_DroneVisualStateArray& src,
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
        cpp2cdr_DroneVisualStateArray(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][DroneVisualStateArray] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_DroneVisualStateArray(
    const HakoCpp_DroneVisualStateArray& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_DroneVisualStateArray(
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
static inline bool hako_convert_cdr2cpp_DroneVisualStateArray(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_DroneVisualStateArray& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_DroneVisualStateArray(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][DroneVisualStateArray] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_DroneVisualStateArray(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_DroneVisualStateArray& dst)
{
    return hako_convert_cdr2cpp_DroneVisualStateArray(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_msgs
{

class DroneVisualStateArrayCdr
{
public:
    DroneVisualStateArrayCdr() = default;
    ~DroneVisualStateArrayCdr() = default;

    int cpp2cdr(
        const HakoCpp_DroneVisualStateArray& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_DroneVisualStateArray(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_DroneVisualStateArray& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_DroneVisualStateArray(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_DroneVisualStateArray& cppData)
    {
        return hako_convert_cdr2cpp_DroneVisualStateArray(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_DroneVisualStateArray& cppData)
    {
        return hako_convert_cdr2cpp_DroneVisualStateArray(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_DroneVisualStateArray_HPP_ */
