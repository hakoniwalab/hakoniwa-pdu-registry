#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_ev3_msgs_Ev3PduSensor_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_ev3_msgs_Ev3PduSensor_HPP_

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
#include "ev3_msgs/pdu_cpptype_Ev3PduSensor.hpp"

/*
 * Dependent CDR convertors
 */
#include "ev3_msgs/pdu_cpptype_cdr_conv_Ev3PduColorSensor.hpp"
#include "ev3_msgs/pdu_cpptype_cdr_conv_Ev3PduSensorHeader.hpp"
#include "ev3_msgs/pdu_cpptype_cdr_conv_Ev3PduTouchSensor.hpp"

/***************************
 *
 * CPP PDU ==> CDR payload body
 *
 ***************************/
static inline void cpp2cdr_Ev3PduSensor(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_Ev3PduSensor& src)
{
    // nested struct: head
    cpp2cdr_Ev3PduSensorHeader(cdr, src.head);
    // primitive fixed array: buttons[1]
    hako::pdu::cdr::serialize_fixed_array(cdr, src.buttons, 1);
    // struct fixed array: color_sensors[2]
    for (size_t i = 0; i < 2; ++i) {
        cpp2cdr_Ev3PduColorSensor(cdr, src.color_sensors[i]);
    }
    // struct fixed array: touch_sensors[2]
    for (size_t i = 0; i < 2; ++i) {
        cpp2cdr_Ev3PduTouchSensor(cdr, src.touch_sensors[i]);
    }
    // primitive fixed array: motor_angle[3]
    hako::pdu::cdr::serialize_fixed_array(cdr, src.motor_angle, 3);
    // primitive: gyro_degree
    cdr << src.gyro_degree;
    // primitive: gyro_degree_rate
    cdr << src.gyro_degree_rate;
    // primitive: sensor_ultrasonic
    cdr << src.sensor_ultrasonic;
    // primitive: gps_lat
    cdr << src.gps_lat;
    // primitive: gps_lon
    cdr << src.gps_lon;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_Ev3PduSensor(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_Ev3PduSensor& dst)
{
    // nested struct: head
    cdr2cpp_Ev3PduSensorHeader(cdr, dst.head);
    // primitive fixed array: buttons[1]
    hako::pdu::cdr::deserialize_fixed_array(cdr, dst.buttons, 1);
    // struct fixed array: color_sensors[2]
    hako::pdu::cdr::resize_if_possible(dst.color_sensors, 2);
    for (size_t i = 0; i < 2; ++i) {
        cdr2cpp_Ev3PduColorSensor(cdr, dst.color_sensors[i]);
    }
    // struct fixed array: touch_sensors[2]
    hako::pdu::cdr::resize_if_possible(dst.touch_sensors, 2);
    for (size_t i = 0; i < 2; ++i) {
        cdr2cpp_Ev3PduTouchSensor(cdr, dst.touch_sensors[i]);
    }
    // primitive fixed array: motor_angle[3]
    hako::pdu::cdr::deserialize_fixed_array(cdr, dst.motor_angle, 3);
    // primitive: gyro_degree
    cdr >> dst.gyro_degree;
    // primitive: gyro_degree_rate
    cdr >> dst.gyro_degree_rate;
    // primitive: sensor_ultrasonic
    cdr >> dst.sensor_ultrasonic;
    // primitive: gps_lat
    cdr >> dst.gps_lat;
    // primitive: gps_lon
    cdr >> dst.gps_lon;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_Ev3PduSensor(
    const HakoCpp_Ev3PduSensor& src,
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
        cpp2cdr_Ev3PduSensor(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Ev3PduSensor] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_Ev3PduSensor(
    const HakoCpp_Ev3PduSensor& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_Ev3PduSensor(
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
static inline bool hako_convert_cdr2cpp_Ev3PduSensor(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_Ev3PduSensor& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_Ev3PduSensor(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][Ev3PduSensor] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_Ev3PduSensor(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_Ev3PduSensor& dst)
{
    return hako_convert_cdr2cpp_Ev3PduSensor(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::ev3_msgs
{

class Ev3PduSensorCdr
{
public:
    Ev3PduSensorCdr() = default;
    ~Ev3PduSensorCdr() = default;

    int cpp2cdr(
        const HakoCpp_Ev3PduSensor& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_Ev3PduSensor(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_Ev3PduSensor& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_Ev3PduSensor(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_Ev3PduSensor& cppData)
    {
        return hako_convert_cdr2cpp_Ev3PduSensor(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_Ev3PduSensor& cppData)
    {
        return hako_convert_cdr2cpp_Ev3PduSensor(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::ev3_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_ev3_msgs_Ev3PduSensor_HPP_ */
