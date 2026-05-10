#ifndef _pdu_cpptype_sensor_msgs_MultiEchoLaserScan_HPP_
#define _pdu_cpptype_sensor_msgs_MultiEchoLaserScan_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "sensor_msgs/pdu_cpptype_LaserEcho.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        Hako_float32 angle_min;
        Hako_float32 angle_max;
        Hako_float32 angle_increment;
        Hako_float32 time_increment;
        Hako_float32 scan_time;
        Hako_float32 range_min;
        Hako_float32 range_max;
        std::vector<HakoCpp_LaserEcho> ranges;
        std::vector<HakoCpp_LaserEcho> intensities;
} HakoCpp_MultiEchoLaserScan;

#endif /* _pdu_cpptype_sensor_msgs_MultiEchoLaserScan_HPP_ */
