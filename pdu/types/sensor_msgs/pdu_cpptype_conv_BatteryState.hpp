#ifndef _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_BatteryState_HPP_
#define _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_BatteryState_HPP_

#include "pdu_primitive_ctypes.h"
#include "pdu_primitive_ctypes_conv.hpp"
#include "pdu_dynamic_memory.hpp"
/*
 * Dependent pdu data
 */
#include "sensor_msgs/pdu_ctype_BatteryState.h"
/*
 * Dependent cpp pdu data
 */
#include "sensor_msgs/pdu_cpptype_BatteryState.hpp"

/*
 * Dependent Convertors
 */
#include "builtin_interfaces/pdu_cpptype_conv_Time.hpp"
#include "std_msgs/pdu_cpptype_conv_Header.hpp"

/***************************
 *
 * PDU ==> CPP PDU
 *
 ***************************/
static inline int cpp_pdu2cpp_primitive_array_BatteryState_cell_voltage(const char* heap_ptr, Hako_BatteryState &src, HakoCpp_BatteryState &dst)
{
    // Convert using len and off
    int offset = src._cell_voltage_off;
    int length = src._cell_voltage_len;
    if (length > 0) {
        dst.cell_voltage.resize(length);
        memcpy(dst.cell_voltage.data(), heap_ptr + offset, length * sizeof(Hako_float32));
    }
    return 0;
}
static inline int cpp_pdu2cpp_primitive_array_BatteryState_cell_temperature(const char* heap_ptr, Hako_BatteryState &src, HakoCpp_BatteryState &dst)
{
    // Convert using len and off
    int offset = src._cell_temperature_off;
    int length = src._cell_temperature_len;
    if (length > 0) {
        dst.cell_temperature.resize(length);
        memcpy(dst.cell_temperature.data(), heap_ptr + offset, length * sizeof(Hako_float32));
    }
    return 0;
}

static inline int cpp_pdu2cpp_BatteryState(const char* heap_ptr, Hako_BatteryState &src, HakoCpp_BatteryState &dst)
{
    // Struct convert
    cpp_pdu2cpp_Header(heap_ptr, src.header, dst.header);
    // primitive convert
    hako_convert_pdu2cpp(src.voltage, dst.voltage);
    // primitive convert
    hako_convert_pdu2cpp(src.temperature, dst.temperature);
    // primitive convert
    hako_convert_pdu2cpp(src.current, dst.current);
    // primitive convert
    hako_convert_pdu2cpp(src.charge, dst.charge);
    // primitive convert
    hako_convert_pdu2cpp(src.capacity, dst.capacity);
    // primitive convert
    hako_convert_pdu2cpp(src.design_capacity, dst.design_capacity);
    // primitive convert
    hako_convert_pdu2cpp(src.percentage, dst.percentage);
    // primitive convert
    hako_convert_pdu2cpp(src.power_supply_status, dst.power_supply_status);
    // primitive convert
    hako_convert_pdu2cpp(src.power_supply_health, dst.power_supply_health);
    // primitive convert
    hako_convert_pdu2cpp(src.power_supply_technology, dst.power_supply_technology);
    // primitive convert
    hako_convert_pdu2cpp(src.present, dst.present);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_BatteryState_cell_voltage(heap_ptr, src, dst);
    // primitive array convertor
    cpp_pdu2cpp_primitive_array_BatteryState_cell_temperature(heap_ptr, src, dst);
    // string convertor
    dst.location = (const char*)src.location;
    // string convertor
    dst.serial_number = (const char*)src.serial_number;
    (void)heap_ptr;
    return 0;
}

static inline int hako_convert_pdu2cpp_BatteryState(Hako_BatteryState &src, HakoCpp_BatteryState &dst)
{
    void* base_ptr = (void*)&src;
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    // Validate magic number and version
    if (heap_ptr == nullptr) {
        return -1; // Invalid PDU metadata
    }
    else {
        return cpp_pdu2cpp_BatteryState((char*)heap_ptr, src, dst);
    }
}

/***************************
 *
 * CPP PDU ==> PDU
 *
 ***************************/
static inline bool cpp_cpp2pdu_primitive_array_BatteryState_cell_voltage(HakoCpp_BatteryState &src, Hako_BatteryState &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray
    dst._cell_voltage_len = src.cell_voltage.size();
    if (dst._cell_voltage_len > 0) {
        void* temp_ptr = dynamic_memory.allocate(dst._cell_voltage_len, sizeof(Hako_float32));
        memcpy(temp_ptr, src.cell_voltage.data(), dst._cell_voltage_len * sizeof(Hako_float32));
        dst._cell_voltage_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._cell_voltage_off = dynamic_memory.get_total_size();
    }
    return true;
}
static inline bool cpp_cpp2pdu_primitive_array_BatteryState_cell_temperature(HakoCpp_BatteryState &src, Hako_BatteryState &dst, PduDynamicMemory &dynamic_memory)
{
    //Copy varray
    dst._cell_temperature_len = src.cell_temperature.size();
    if (dst._cell_temperature_len > 0) {
        void* temp_ptr = dynamic_memory.allocate(dst._cell_temperature_len, sizeof(Hako_float32));
        memcpy(temp_ptr, src.cell_temperature.data(), dst._cell_temperature_len * sizeof(Hako_float32));
        dst._cell_temperature_off = dynamic_memory.get_offset(temp_ptr);
    }
    else {
        dst._cell_temperature_off = dynamic_memory.get_total_size();
    }
    return true;
}

static inline bool cpp_cpp2pdu_BatteryState(HakoCpp_BatteryState &src, Hako_BatteryState &dst, PduDynamicMemory &dynamic_memory)
{
    try {
        // struct convert
        cpp_cpp2pdu_Header(src.header, dst.header, dynamic_memory);
        // primitive convert
        hako_convert_cpp2pdu(src.voltage, dst.voltage);
        // primitive convert
        hako_convert_cpp2pdu(src.temperature, dst.temperature);
        // primitive convert
        hako_convert_cpp2pdu(src.current, dst.current);
        // primitive convert
        hako_convert_cpp2pdu(src.charge, dst.charge);
        // primitive convert
        hako_convert_cpp2pdu(src.capacity, dst.capacity);
        // primitive convert
        hako_convert_cpp2pdu(src.design_capacity, dst.design_capacity);
        // primitive convert
        hako_convert_cpp2pdu(src.percentage, dst.percentage);
        // primitive convert
        hako_convert_cpp2pdu(src.power_supply_status, dst.power_supply_status);
        // primitive convert
        hako_convert_cpp2pdu(src.power_supply_health, dst.power_supply_health);
        // primitive convert
        hako_convert_cpp2pdu(src.power_supply_technology, dst.power_supply_technology);
        // primitive convert
        hako_convert_cpp2pdu(src.present, dst.present);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_BatteryState_cell_voltage(src, dst, dynamic_memory);
        //primitive array copy
        cpp_cpp2pdu_primitive_array_BatteryState_cell_temperature(src, dst, dynamic_memory);
        // string convertor
        (void)hako_convert_cpp2pdu_array(
            src.location, src.location.length(),
            dst.location, M_ARRAY_SIZE(Hako_BatteryState, char, location));
        dst.location[src.location.length()] = '\0';
        // string convertor
        (void)hako_convert_cpp2pdu_array(
            src.serial_number, src.serial_number.length(),
            dst.serial_number, M_ARRAY_SIZE(Hako_BatteryState, char, serial_number));
        dst.serial_number[src.serial_number.length()] = '\0';
    } catch (const std::runtime_error& e) {
        std::cerr << "convertor error: " << e.what() << std::endl;
        return false;
    }
    (void)dynamic_memory;
    return true;
}

static inline int hako_convert_cpp2pdu_BatteryState(HakoCpp_BatteryState &src, Hako_BatteryState** dst)
{
    PduDynamicMemory dynamic_memory;
    Hako_BatteryState out;
    if (!cpp_cpp2pdu_BatteryState(src, out, dynamic_memory)) {
        return -1;
    }
    int heap_size = dynamic_memory.get_total_size();
    void* base_ptr = hako_create_empty_pdu(sizeof(Hako_BatteryState), heap_size);
    if (base_ptr == nullptr) {
        return -1;
    }
    // Copy out on base data
    memcpy(base_ptr, (void*)&out, sizeof(Hako_BatteryState));

    // Copy dynamic part and set offsets
    void* heap_ptr = hako_get_heap_ptr_pdu(base_ptr);
    dynamic_memory.copy_to_pdu((char*)heap_ptr);

    *dst = (Hako_BatteryState*)base_ptr;
    return hako_get_pdu_meta_data(base_ptr)->total_size;
}

static inline Hako_BatteryState* hako_create_empty_pdu_BatteryState(int heap_size)
{
    // Allocate PDU memory
    char* base_ptr = (char*)hako_create_empty_pdu(sizeof(Hako_BatteryState), heap_size);
    if (base_ptr == nullptr) {
        return nullptr;
    }
    return (Hako_BatteryState*)base_ptr;
}
namespace hako::pdu::msgs::sensor_msgs
{
class BatteryState
{
public:
    BatteryState() = default;
    ~BatteryState() = default;

    bool pdu2cpp(char* top_ptr, HakoCpp_BatteryState& cppData)
    {
        char* base_ptr = (char*)hako_get_base_ptr_pdu((void*)top_ptr);
        if (base_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "BatteryState" << "] hako_get_base_ptr_pdu returned null" << std::endl;
            return false;
        } 
        int ret = hako_convert_pdu2cpp_BatteryState(*(Hako_BatteryState*)base_ptr, cppData);
        if (ret != 0) {
            std::cerr << "[ConvertorError][" << "BatteryState" << "] hako_convert_pdu2cpp returned " << ret << std::endl;
            return false;
        }
        return true;
    }

    int cpp2pdu(HakoCpp_BatteryState& cppData, char* pdu_buffer, int buffer_len)
    {
        char* base_ptr = nullptr;
        int pdu_size = hako_convert_cpp2pdu_BatteryState(cppData, (Hako_BatteryState**)&base_ptr);
        if (pdu_size < 0) {
            std::cerr << "[ConvertorError][" << "BatteryState" << "] hako_convert_cpp2pdu returned error code: " << pdu_size << std::endl;
            return -1;
        }
        if (pdu_size > buffer_len) {
            std::cerr << "[ConvertorError][" << "BatteryState" << "] buffer too small. pdu_size=" << pdu_size << " buffer_len=" << buffer_len << std::endl;
            return -1;
        }
        void* top_ptr = hako_get_top_ptr_pdu((void*)base_ptr);
        if (top_ptr == nullptr) {
            std::cerr << "[ConvertorError][" << "BatteryState" << "] hako_get_top_ptr_pdu returned null" << std::endl;
            return -1;
        }
        memcpy(pdu_buffer, top_ptr, pdu_size);
        hako_destroy_pdu((void*)base_ptr);
        return pdu_size;
    }

private:
};
}


#endif /* _PDU_CPPTYPE_CONV_HAKO_sensor_msgs_BatteryState_HPP_ */
