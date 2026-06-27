#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_Collision_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_Collision_HPP_

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
#include "hako_msgs/pdu_cpptype_Collision.hpp"

/*
 * Dependent CDR convertors
 */
#include "geometry_msgs/pdu_cpptype_cdr_conv_Point.hpp"
#include "geometry_msgs/pdu_cpptype_cdr_conv_Vector3.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_Collision(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_Collision& src)
{
    // primitive: collision
    cdr << static_cast<bool>(src.collision != 0);
    // primitive: contact_num
    cdr << src.contact_num;
    // nested struct: relative_velocity
    cpp2cdr_Vector3(cdr, src.relative_velocity);
    // struct fixed array: contact_position[10]
    for (size_t i = 0; i < 10; ++i) {
        cpp2cdr_Point(cdr, src.contact_position[i]);
    }
    // primitive: restitution_coefficient
    cdr << src.restitution_coefficient;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_Collision(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_Collision& dst)
{
    // primitive: collision
    {
        bool value = false;
        cdr >> value;
        dst.collision = value ? 1 : 0;
    }
    // primitive: contact_num
    cdr >> dst.contact_num;
    // nested struct: relative_velocity
    cdr2cpp_Vector3(cdr, dst.relative_velocity);
    // struct fixed array: contact_position[10]
    hako::pdu::cdr::resize_if_possible(dst.contact_position, 10);
    for (size_t i = 0; i < 10; ++i) {
        cdr2cpp_Point(cdr, dst.contact_position[i]);
    }
    // primitive: restitution_coefficient
    cdr >> dst.restitution_coefficient;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_Collision(
    const HakoCpp_Collision& src,
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
        cpp2cdr_Collision(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Collision] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_Collision(
    const HakoCpp_Collision& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_Collision(
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
static inline bool hako_convert_cdr2cpp_Collision(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_Collision& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_Collision(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Collision] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_Collision(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_Collision& dst)
{
    return hako_convert_cdr2cpp_Collision(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_msgs
{

class CollisionCdr
{
public:
    CollisionCdr() = default;
    ~CollisionCdr() = default;

    int cpp2cdr(
        const HakoCpp_Collision& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_Collision(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_Collision& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_Collision(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_Collision& cppData)
    {
        return hako_convert_cdr2cpp_Collision(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_Collision& cppData)
    {
        return hako_convert_cdr2cpp_Collision(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_Collision_HPP_ */
