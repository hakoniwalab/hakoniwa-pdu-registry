#ifndef _pdu_cpptype_sensor_msgs_Temperature_HPP_
#define _pdu_cpptype_sensor_msgs_Temperature_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        Hako_float64 temperature;
        Hako_float64 variance;
} HakoCpp_Temperature;

#endif /* _pdu_cpptype_sensor_msgs_Temperature_HPP_ */
