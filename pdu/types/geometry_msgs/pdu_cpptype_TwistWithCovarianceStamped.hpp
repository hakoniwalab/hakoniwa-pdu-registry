#ifndef _pdu_cpptype_geometry_msgs_TwistWithCovarianceStamped_HPP_
#define _pdu_cpptype_geometry_msgs_TwistWithCovarianceStamped_HPP_

#include "pdu_primitive_ctypes.h"
#include <vector>
#include <array>
#include "builtin_interfaces/pdu_cpptype_Time.hpp"
#include "geometry_msgs/pdu_cpptype_Twist.hpp"
#include "geometry_msgs/pdu_cpptype_TwistWithCovariance.hpp"
#include "geometry_msgs/pdu_cpptype_Vector3.hpp"
#include "std_msgs/pdu_cpptype_Header.hpp"

typedef struct {
        HakoCpp_Header header;
        HakoCpp_TwistWithCovariance twist;
} HakoCpp_TwistWithCovarianceStamped;

#endif /* _pdu_cpptype_geometry_msgs_TwistWithCovarianceStamped_HPP_ */
