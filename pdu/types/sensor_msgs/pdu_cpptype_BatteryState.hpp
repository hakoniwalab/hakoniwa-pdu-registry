#ifndef _pdu_cpptype_sensor_msgs_BatteryState_HPP_
#define _pdu_cpptype_sensor_msgs_BatteryState_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        Hako_float32 voltage;
        Hako_float32 temperature;
        Hako_float32 current;
        Hako_float32 charge;
        Hako_float32 capacity;
        Hako_float32 design_capacity;
        Hako_float32 percentage;
        Hako_uint8 power_supply_status;
        Hako_uint8 power_supply_health;
        Hako_uint8 power_supply_technology;
        Hako_bool present;
        std::vector<Hako_float32> cell_voltage;
        std::vector<Hako_float32> cell_temperature;
        std::string location;
        std::string serial_number;
} HakoCpp_BatteryState;

#endif /* _pdu_cpptype_sensor_msgs_BatteryState_HPP_ */
