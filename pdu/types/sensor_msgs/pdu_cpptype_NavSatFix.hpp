#ifndef _pdu_cpptype_sensor_msgs_NavSatFix_HPP_
#define _pdu_cpptype_sensor_msgs_NavSatFix_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "sensor_msgs/pdu_cpptype_NavSatStatus.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        HakoCpp_NavSatStatus status;
        Hako_float64 latitude;
        Hako_float64 longitude;
        Hako_float64 altitude;
        std::array<Hako_float64, 9> position_covariance;
        Hako_uint8 position_covariance_type;
} HakoCpp_NavSatFix;

#endif /* _pdu_cpptype_sensor_msgs_NavSatFix_HPP_ */
