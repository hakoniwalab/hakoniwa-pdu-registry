#ifndef _pdu_ctype_sensor_msgs_BatteryState_H_
#define _pdu_ctype_sensor_msgs_BatteryState_H_

#include "pdu_primitive_ctypes.h"
#include "builtin_interfaces/pdu_ctype_Time.h"
#include "std_msgs/pdu_ctype_Header.h"

typedef struct {
        Hako_Header header;
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
        // float32 cell_voltage[]
        int _cell_voltage_len;
        int _cell_voltage_off;
        // float32 cell_temperature[]
        int _cell_temperature_len;
        int _cell_temperature_off;
        char location[HAKO_STRING_SIZE];
        char serial_number[HAKO_STRING_SIZE];
} Hako_BatteryState;

#endif /* _pdu_ctype_sensor_msgs_BatteryState_H_ */
