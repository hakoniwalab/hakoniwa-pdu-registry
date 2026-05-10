#ifndef _pdu_cpptype_sensor_msgs_MagneticField_HPP_
#define _pdu_cpptype_sensor_msgs_MagneticField_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        HakoCpp_Vector3 magnetic_field;
        std::array<Hako_float64, 9> magnetic_field_covariance;
} HakoCpp_MagneticField;

#endif /* _pdu_cpptype_sensor_msgs_MagneticField_HPP_ */
