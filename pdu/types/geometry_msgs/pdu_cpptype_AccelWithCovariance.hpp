#ifndef _pdu_cpptype_geometry_msgs_AccelWithCovariance_HPP_
#define _pdu_cpptype_geometry_msgs_AccelWithCovariance_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "geometry_msgs/pdu_cpptype_Accel.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"

typedef struct {
        HakoCpp_Accel accel;
        std::array<Hako_float64, 36> covariance;
} HakoCpp_AccelWithCovariance;

#endif /* _pdu_cpptype_geometry_msgs_AccelWithCovariance_HPP_ */
