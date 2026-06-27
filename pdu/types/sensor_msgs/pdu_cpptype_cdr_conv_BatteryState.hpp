#ifndef _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_BatteryState_HPP_
#define _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_BatteryState_HPP_

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
#include "sensor_msgs/pdu_cpptype_BatteryState.hpp"

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
static inline void cpp2cdr_BatteryState(
    eprosima::fastcdr::Cdr& cdr,
    const HakoCpp_BatteryState& src)
{
    // nested struct: header
    cpp2cdr_Header(cdr, src.header);
    // primitive: voltage
    cdr << src.voltage;
    // primitive: temperature
    cdr << src.temperature;
    // primitive: current
    cdr << src.current;
    // primitive: charge
    cdr << src.charge;
    // primitive: capacity
    cdr << src.capacity;
    // primitive: design_capacity
    cdr << src.design_capacity;
    // primitive: percentage
    cdr << src.percentage;
    // primitive: power_supply_status
    cdr << src.power_supply_status;
    // primitive: power_supply_health
    cdr << src.power_supply_health;
    // primitive: power_supply_technology
    cdr << src.power_supply_technology;
    // primitive: present
    cdr << static_cast<bool>(src.present != 0);
    // primitive sequence: cell_voltage
    hako::pdu::cdr::serialize_sequence(cdr, src.cell_voltage);
    // primitive sequence: cell_temperature
    hako::pdu::cdr::serialize_sequence(cdr, src.cell_temperature);
    // string: location
    cdr << src.location;
    // string: serial_number
    cdr << src.serial_number;
}

/***************************
 *
 * CDR payload body ==> CPP PDU
 *
 ***************************/
static inline void cdr2cpp_BatteryState(
    eprosima::fastcdr::Cdr& cdr,
    HakoCpp_BatteryState& dst)
{
    // nested struct: header
    cdr2cpp_Header(cdr, dst.header);
    // primitive: voltage
    cdr >> dst.voltage;
    // primitive: temperature
    cdr >> dst.temperature;
    // primitive: current
    cdr >> dst.current;
    // primitive: charge
    cdr >> dst.charge;
    // primitive: capacity
    cdr >> dst.capacity;
    // primitive: design_capacity
    cdr >> dst.design_capacity;
    // primitive: percentage
    cdr >> dst.percentage;
    // primitive: power_supply_status
    cdr >> dst.power_supply_status;
    // primitive: power_supply_health
    cdr >> dst.power_supply_health;
    // primitive: power_supply_technology
    cdr >> dst.power_supply_technology;
    // primitive: present
    {
        bool value = false;
        cdr >> value;
        dst.present = value ? 1 : 0;
    }
    // primitive sequence: cell_voltage
    hako::pdu::cdr::deserialize_sequence(cdr, dst.cell_voltage);
    // primitive sequence: cell_temperature
    hako::pdu::cdr::deserialize_sequence(cdr, dst.cell_temperature);
    // string: location
    cdr >> dst.location;
    // string: serial_number
    cdr >> dst.serial_number;
}

/***************************
 *
 * CPP PDU ==> full CDR payload
 *   full payload = CDR encapsulation + CDR payload body
 *
 ***************************/
static inline int hako_convert_cpp2cdr_BatteryState(
    const HakoCpp_BatteryState& src,
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
        cpp2cdr_BatteryState(cdr, src);
        return hako::pdu::cdr::get_serialized_data_length(cdr);
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][BatteryState] cpp2cdr: " << e.what() << std::endl;
        return -1;
    }
}

static inline int hako_convert_cpp2cdr_BatteryState(
    const HakoCpp_BatteryState& src,
    std::vector<uint8_t>& cdr_payload,
    size_t initial_capacity = 4096)
{
    size_t capacity = initial_capacity;
    if (capacity == 0) {
        capacity = 4096;
    }

    for (int retry = 0; retry < 8; ++retry) {
        cdr_payload.resize(capacity);
        int len = hako_convert_cpp2cdr_BatteryState(
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
static inline bool hako_convert_cdr2cpp_BatteryState(
    const char* cdr_buffer,
    int buffer_len,
    HakoCpp_BatteryState& dst)
{
    if (cdr_buffer == nullptr || buffer_len <= 0) {
        return false;
    }

    try {
        eprosima::fastcdr::FastBuffer fastbuffer(const_cast<char*>(cdr_buffer), static_cast<size_t>(buffer_len));
        auto cdr = hako::pdu::cdr::create_dds_cdr(fastbuffer);
        cdr.read_encapsulation();
        cdr2cpp_BatteryState(cdr, dst);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[CdrConvertorError][BatteryState] cdr2cpp: " << e.what() << std::endl;
        return false;
    }
}

static inline bool hako_convert_cdr2cpp_BatteryState(
    const std::vector<uint8_t>& cdr_payload,
    HakoCpp_BatteryState& dst)
{
    return hako_convert_cdr2cpp_BatteryState(
        reinterpret_cast<const char*>(cdr_payload.data()),
        static_cast<int>(cdr_payload.size()),
        dst);
}

namespace hako::pdu::msgs::sensor_msgs
{

class BatteryStateCdr
{
public:
    BatteryStateCdr() = default;
    ~BatteryStateCdr() = default;

    int cpp2cdr(
        const HakoCpp_BatteryState& cppData,
        char* cdr_buffer,
        int buffer_len)
    {
        return hako_convert_cpp2cdr_BatteryState(cppData, cdr_buffer, buffer_len);
    }

    int cpp2cdr(
        const HakoCpp_BatteryState& cppData,
        std::vector<uint8_t>& cdr_payload,
        size_t initial_capacity = 4096)
    {
        return hako_convert_cpp2cdr_BatteryState(cppData, cdr_payload, initial_capacity);
    }

    bool cdr2cpp(
        const char* cdr_buffer,
        int buffer_len,
        HakoCpp_BatteryState& cppData)
    {
        return hako_convert_cdr2cpp_BatteryState(cdr_buffer, buffer_len, cppData);
    }

    bool cdr2cpp(
        const std::vector<uint8_t>& cdr_payload,
        HakoCpp_BatteryState& cppData)
    {
        return hako_convert_cdr2cpp_BatteryState(cdr_payload, cppData);
    }
};

} // namespace hako::pdu::msgs::sensor_msgs

#endif /* _PDU_CPPTYPE_CDR_CONV_HAKO_sensor_msgs_BatteryState_HPP_ */
