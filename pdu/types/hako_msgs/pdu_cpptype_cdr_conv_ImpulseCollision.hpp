#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_ImpulseCollision_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_ImpulseCollision_HPP_

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
#include "hako_msgs/pdu_cpptype_ImpulseCollision.hpp"

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
static inline void cpp2cdr_ImpulseCollision(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_ImpulseCollision& src)
{
    // primitive: collision
    cdr << static_cast<bool>(src.collision != 0);
    // primitive: is_target_static
    cdr << static_cast<bool>(src.is_target_static != 0);
    // primitive: restitution_coefficient
    cdr << src.restitution_coefficient;
    // nested struct: self_contact_vector
    cpp2cdr_Point(cdr, src.self_contact_vector);
    // nested struct: normal
    cpp2cdr_Vector3(cdr, src.normal);
    // nested struct: target_contact_vector
    cpp2cdr_Point(cdr, src.target_contact_vector);
    // nested struct: target_velocity
    cpp2cdr_Vector3(cdr, src.target_velocity);
    // nested struct: target_angular_velocity
    cpp2cdr_Vector3(cdr, src.target_angular_velocity);
    // nested struct: target_euler
    cpp2cdr_Vector3(cdr, src.target_euler);
    // nested struct: target_inertia
    cpp2cdr_Vector3(cdr, src.target_inertia);
    // primitive: target_mass
    cdr << src.target_mass;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_ImpulseCollision(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_ImpulseCollision& dst)
{
    // primitive: collision
    {
        bool value = false;
        cdr >> value;
        dst.collision = value ? 1 : 0;
    }
    // primitive: is_target_static
    {
        bool value = false;
        cdr >> value;
        dst.is_target_static = value ? 1 : 0;
    }
    // primitive: restitution_coefficient
    cdr >> dst.restitution_coefficient;
    // nested struct: self_contact_vector
    cdr2cpp_Point(cdr, dst.self_contact_vector);
    // nested struct: normal
    cdr2cpp_Vector3(cdr, dst.normal);
    // nested struct: target_contact_vector
    cdr2cpp_Point(cdr, dst.target_contact_vector);
    // nested struct: target_velocity
    cdr2cpp_Vector3(cdr, dst.target_velocity);
    // nested struct: target_angular_velocity
    cdr2cpp_Vector3(cdr, dst.target_angular_velocity);
    // nested struct: target_euler
    cdr2cpp_Vector3(cdr, dst.target_euler);
    // nested struct: target_inertia
    cdr2cpp_Vector3(cdr, dst.target_inertia);
    // primitive: target_mass
    cdr >> dst.target_mass;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_ImpulseCollision(
    const HakoCpp_ImpulseCollision& src,
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
        cpp2cdr_ImpulseCollision(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][ImpulseCollision] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_ImpulseCollision(
    const HakoCpp_ImpulseCollision& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_ImpulseCollision(
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
static inline bool hako_convert_cdr2cpp_ImpulseCollision(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_ImpulseCollision& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_ImpulseCollision(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][ImpulseCollision] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_ImpulseCollision(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_ImpulseCollision& dst)
{
    return hako_convert_cdr2cpp_ImpulseCollision(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::hako_msgs
{

class ImpulseCollisionCdr
{
public:
    ImpulseCollisionCdr() = default;
    ~ImpulseCollisionCdr() = default;

    int cpp2cdr(
        const HakoCpp_ImpulseCollision& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_ImpulseCollision(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_ImpulseCollision& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_ImpulseCollision(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_ImpulseCollision& cppData)
    {
        return hako_convert_cdr2cpp_ImpulseCollision(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_ImpulseCollision& cppData)
    {
        return hako_convert_cdr2cpp_ImpulseCollision(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::hako_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_hako_msgs_ImpulseCollision_HPP_ */
